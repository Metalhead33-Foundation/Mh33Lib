#include "MhPng.hpp"
#include <png.h>
#include <algorithm>

void mh33_set_read_callbacks(png_structp read_ptr, MH33::IoDevice* dev);
void mh33_set_write_callbacks(png_structp write_ptr, MH33::IoDevice* dev);
void mh33_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
void mh33_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
void mh33_flush_data(png_structp png_ptr);

namespace MH33 {
namespace GFX {

Png::Png(Png &&mov)
	: pngPtr(mov.pngPtr), infoPtr(mov.infoPtr), endInfoPtr(mov.endInfoPtr), iodev(std::move(mov.iodev)), ro(mov.ro)
{
	mov.pngPtr = nullptr;
	mov.infoPtr = nullptr;
	mov.endInfoPtr = nullptr;
}

void Png::initialize()
{
	if(!iodev.get()) return;
	if(iodev->getMode() == IoMode::READ) {
		pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
		ro = true;
	} else { pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr); ro = false; }
	if(!pngPtr) return;
	infoPtr = png_create_info_struct(reinterpret_cast<png_structp>(pngPtr));
	if(!infoPtr) {
		if(ro) png_destroy_read_struct(reinterpret_cast<png_structp*>(&pngPtr),nullptr,nullptr);
		else png_destroy_write_struct(reinterpret_cast<png_structp*>(&pngPtr),nullptr);
		return;
	}
	if(ro) {
	endInfoPtr = png_create_info_struct(reinterpret_cast<png_structp>(pngPtr));
	if(!endInfoPtr) {
		png_destroy_read_struct(reinterpret_cast<png_structp*>(&pngPtr),reinterpret_cast<png_infop*>(&infoPtr),nullptr);
		return;
	}
	png_set_read_fn(reinterpret_cast<png_structp>(pngPtr),iodev.get(),mh33_read_data);
	if(iodev->tell()) png_set_sig_bytes(reinterpret_cast<png_structp>(pngPtr), iodev->tell());
	png_read_info(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	} else {
	png_set_write_fn(reinterpret_cast<png_structp>(pngPtr),iodev.get(),mh33_write_data,mh33_flush_data);
	}
}

Png &Png::operator=(Png &&mov)
{
	this->pngPtr = mov.pngPtr;
	mov.pngPtr = nullptr;
	this->infoPtr = mov.infoPtr;
	mov.infoPtr = nullptr;
	this->endInfoPtr = mov.endInfoPtr;
	mov.endInfoPtr = nullptr;
	this->iodev = std::move(mov.iodev);
	this->ro = mov.ro;
	return *this;
}

Png::Png()
	: pngPtr(nullptr), infoPtr(nullptr), endInfoPtr(nullptr), iodev(nullptr)
{

}

Png::Png(const std::shared_ptr<IoDevice> &dev)
	: pngPtr(nullptr), infoPtr(nullptr), endInfoPtr(nullptr), iodev(dev)
{
	initialize();
}

Png::Png(std::shared_ptr<IoDevice> &&dev)
	: pngPtr(nullptr), infoPtr(nullptr), endInfoPtr(nullptr), iodev(std::move(dev))
{
	initialize();
}

constexpr size_t type2bytes(uint8_t color_type, uint8_t bit_depth) {
	switch (color_type) {

	case PNG_COLOR_TYPE_RGB: return (bit_depth/8) * 3;
	case PNG_COLOR_TYPE_RGBA: return (bit_depth/8) * 4;
	case PNG_COLOR_TYPE_GRAY: return bit_depth/8;
	case PNG_COLOR_TYPE_PALETTE: return sizeof(uint8_t);
	default: return 0;
}
}

void Png::decode(uint16_t &width, uint16_t &height, uint8_t &color_type, uint8_t &bit_depth, Buffer& pixelData)
{
	if(!pngPtr) return;
	width = png_get_image_width(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	height = png_get_image_height(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	color_type = png_get_color_type(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	bit_depth = png_get_bit_depth(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	int number_of_passes;
	number_of_passes = png_set_interlace_handling(reinterpret_cast<png_structp>(pngPtr));
	png_read_update_info(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr));
	pixelData.resize(height*png_get_rowbytes(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr)));
	std::vector<png_bytep> rowPtrs(height);
	for (int y=0; y<height; y++) {
		rowPtrs[y] = reinterpret_cast<png_bytep>(&pixelData[y*png_get_rowbytes(reinterpret_cast<png_structp>(pngPtr), reinterpret_cast<png_infop>(infoPtr))]);
	}
	png_read_image(reinterpret_cast<png_structp>(pngPtr), rowPtrs.data());
}

void Png::encode(uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, int compressionLevel)
{
	if(!pngPtr) return;
	png_set_IHDR(reinterpret_cast<png_structp>(pngPtr),reinterpret_cast<png_infop>(infoPtr),width,height,bit_depth,color_type,PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);
	png_set_compression_level(reinterpret_cast<png_structp>(pngPtr), std::clamp(compressionLevel,0,9));
	std::vector<png_bytep> rowPtrs(height);
	for (int y=0; y<height; y++) {
		rowPtrs[y] = reinterpret_cast<png_bytep>(&pixelData[type2bytes(color_type,bit_depth)*width*y]);
	}
	png_write_info(reinterpret_cast<png_structp>(pngPtr),reinterpret_cast<png_infop>(infoPtr));
	png_write_rows(reinterpret_cast<png_structp>(pngPtr),rowPtrs.data(),rowPtrs.size());
	png_write_end(reinterpret_cast<png_structp>(pngPtr),reinterpret_cast<png_infop>(infoPtr));
}

}
}

void mh33_set_read_callbacks(png_structp read_ptr, MH33::IoDevice* dev) {
	png_set_read_fn(read_ptr, dev, mh33_read_data);
}
void mh33_set_write_callbacks(png_structp write_ptr, MH33::IoDevice* dev) {
	png_set_write_fn(write_ptr, dev, mh33_write_data, mh33_flush_data);
}
void mh33_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	reinterpret_cast<MH33::IoDevice*>(png_get_io_ptr(png_ptr))->read(data,length);
}
void mh33_write_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	reinterpret_cast<MH33::IoDevice*>(png_get_io_ptr(png_ptr))->write(data,length);
}
void mh33_flush_data(png_structp png_ptr) {
	reinterpret_cast<MH33::IoDevice*>(png_get_io_ptr(png_ptr))->flush();
}
