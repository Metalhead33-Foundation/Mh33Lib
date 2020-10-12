#include "MhPNG.hpp"
#include <png.h>
#include <algorithm>

void mh33_set_read_callbacks(png_structp read_ptr, MH33::IoDevice* dev);
void mh33_set_write_callbacks(png_structp write_ptr, MH33::IoDevice* dev);
void mh33_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
void mh33_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
void mh33_flush_data(png_structp png_ptr);

namespace MH33 {
namespace GFX {
namespace PNG {

constexpr size_t type2bytes(uint8_t color_type, uint8_t bit_depth) {
	switch (color_type) {

	case PNG_COLOR_TYPE_RGB: return (bit_depth/8) * 3;
	case PNG_COLOR_TYPE_RGBA: return (bit_depth/8) * 4;
	case PNG_COLOR_TYPE_GRAY: return bit_depth/8;
	case PNG_COLOR_TYPE_PALETTE: return sizeof(uint8_t);
	default: return 0;
}
}

void decode(IoDevice& iodev, uint16_t &width, uint16_t &height, uint8_t &color_type, uint8_t &bit_depth, Buffer& pixelData)
{
	auto pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
	if(!pngPtr) return;
	auto infoPtr = png_create_info_struct(pngPtr);
	if(!infoPtr) {
		png_destroy_read_struct(&pngPtr,nullptr,nullptr);
		return;
	}
	auto endInfoPtr = png_create_info_struct(pngPtr);
	if(!endInfoPtr) {
		png_destroy_read_struct(&pngPtr,&infoPtr,nullptr);
		return;
	}
	png_set_read_fn(pngPtr,&iodev,mh33_read_data);
	if(iodev.tell()) png_set_sig_bytes(pngPtr, iodev.tell());
	png_read_info(pngPtr, infoPtr);

	width = png_get_image_width(pngPtr,infoPtr);
	height = png_get_image_height(pngPtr,infoPtr);
	color_type = png_get_color_type(pngPtr,infoPtr);
	bit_depth = png_get_bit_depth(pngPtr,infoPtr);
	int number_of_passes;
	number_of_passes = png_set_interlace_handling(pngPtr);
	png_read_update_info(pngPtr, infoPtr);
	pixelData.resize(height*png_get_rowbytes(pngPtr, infoPtr));
	std::vector<png_bytep> rowPtrs(height);
	for (int y=0; y<height; y++) {
		rowPtrs[y] = reinterpret_cast<png_bytep>(&pixelData[y*png_get_rowbytes(pngPtr, infoPtr)]);
	}
	png_read_image(pngPtr, rowPtrs.data());
	png_destroy_read_struct(&pngPtr,&infoPtr,&endInfoPtr);
}

void encode(IoDevice& iodev, uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, float compressionLevel)
{
	auto pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
	if(!pngPtr) return;
	auto infoPtr = png_create_info_struct(pngPtr);
	if(!infoPtr) {
		png_destroy_write_struct(&pngPtr,nullptr);
		return;
	}
	png_set_write_fn(pngPtr,&iodev,mh33_write_data,mh33_flush_data);
	png_set_IHDR(pngPtr,infoPtr,width,height,bit_depth,color_type,PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);
	png_set_compression_level(pngPtr,int(std::clamp(compressionLevel,0.0f,1.0f)*9.0f));
	std::vector<png_bytep> rowPtrs(height);
	for (int y=0; y<height; y++) {
		rowPtrs[y] = reinterpret_cast<png_bytep>(&pixelData[type2bytes(color_type,bit_depth)*width*y]);
	}
	png_write_info(pngPtr,infoPtr);
	png_write_rows(pngPtr,rowPtrs.data(),rowPtrs.size());
	png_write_end(pngPtr,infoPtr);
	png_destroy_write_struct(&pngPtr,&infoPtr);
}

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
