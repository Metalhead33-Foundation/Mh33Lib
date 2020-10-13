#include <iostream>
#include "Io/MhFileIO.hpp"
#include "Media/Image/MhGIF.hpp"
#include "Media/Image/MhWEBP.hpp"
#include "Media/Image/MhTGA.hpp"
#include "Media/Image/MhPNG.hpp"
#include "Media/Image/MhJPEG.hpp"
#include <sstream>

static const char* inGif = "/home/legacy/fonts/Anient/1/anime/aoi_ren/1/2/25.gif";
static const char* inWebp = "/tmp/coolie.webp";
static const char* inTga = "/home/legacy/fonts/Anient/1/2194094_b.tga";
static const char* inPng = "/home/legacy/fonts/Anient/1/109925325_178548090302695_9174570104564186065_o.png";
static const char* inJpeg = "/home/legacy/fonts/Anient/1/2194094.jpg";

static int imgNum = 0;
void testGif();
void testWebp();
void testTga();
void testPng();
void testJpeg();

int main(int argc, char *argv[])
{
	//testGif();
	//testWebp();
	//testTga();
	//testPng();
	//testJpeg();
	return 0;
}
void testGif() {
	MH33::FileIO rio(inGif,MH33::IoMode::READ);
	MH33::GFX::DecodeTarget target;
	MH33::GFX::GIF::decode(rio,target);
	if(target.format == MH33::GFX::Format::INVALID) {
		std::cout << "Reading GIF failed!" << std::endl;
		return;
	}
	for(auto& it : target.frames) {
		std::cout << "GIF frame\nWidth: " << it.width << "\nHeight: " << it.height << std::endl;
		std::stringstream stringstream;
		stringstream << "/tmp/gif_frame_" << imgNum++ << ".webp";
		MH33::FileIO wio(stringstream.str(),MH33::IoMode::WRITE);
		MH33::Buffer buff(it.height*it.stride*sizeof(MH33::GFX::RGB<uint8_t>));
		MH33::GFX::RGB<uint8_t>* pixels = reinterpret_cast<MH33::GFX::RGB<uint8_t>*>(buff.data());
		MH33::GFX::RGB<uint8_t>* palette = reinterpret_cast<MH33::GFX::RGB<uint8_t>*>(target.palette->palette.data());
		for(size_t i = 0; i < it.imageData.size(); ++i) {
			pixels[i] = palette[*reinterpret_cast<uint8_t*>(&it.imageData[i])];
		}
		MH33::GFX::WEBP::encode(buff,it.width,it.height,it.stride*3,MH33::GFX::Format::RGB8U,0.0f,wio);
	}
}
void testWebp() {
	MH33::FileIO rio(inWebp,MH33::IoMode::READ);
	MH33::GFX::DecodeTarget target;
	target.format = MH33::GFX::Format::RGB8U;
	MH33::GFX::WEBP::demux(rio,target);
	if(target.format == MH33::GFX::Format::INVALID) {
		std::cout << "Reading WEBP failed!" << std::endl;
		return;
	}
	for(auto& it : target.frames) {
		std::cout << "WEBP frame\nWidth: " << it.width << "\nHeight: " << it.height << std::endl;
		std::stringstream stringstream;
		stringstream << "/tmp/webp_frame_" << imgNum++ << ".webp";
		MH33::FileIO wio(stringstream.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(it.imageData,it.width,it.height,it.stride,target.format,0.0f,wio);
	}
}
void testTga() {
	MH33::FileIO rio(inTga,MH33::IoMode::READ);
	MH33::GFX::DecodeTarget target;
	MH33::GFX::TGA::decode(rio,target);
	if(target.format == MH33::GFX::Format::INVALID) {
		std::cout << "Reading TGA failed!" << std::endl;
		return;
	}
	for(auto& it : target.frames) {
		std::cout << "TGA frame\nWidth: " << it.width << "\nHeight: " << it.height << std::endl;
		std::stringstream stringstream;
		stringstream << "/tmp/tga_frame_" << imgNum++ << ".webp";
		MH33::FileIO wio(stringstream.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(it.imageData,it.width,it.height,it.stride,target.format,0.0f,wio);
	}
}
void testPng() {
	MH33::FileIO rio(inPng,MH33::IoMode::READ);
	MH33::GFX::DecodeTarget target;
	MH33::GFX::PNG::decode(rio,target);
	if(target.format == MH33::GFX::Format::INVALID) {
		std::cout << "Reading PNG failed!" << std::endl;
		return;
	}
	for(auto& it : target.frames) {
		std::cout << "PNG frame\nWidth: " << it.width << "\nHeight: " << it.height << std::endl;
		std::stringstream stringstream;
		stringstream << "/tmp/png_frame_" << imgNum++ << ".webp";
		MH33::FileIO wio(stringstream.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(it.imageData,it.width,it.height,it.stride,target.format,0.0f,wio);
	}
}
void testJpeg() {
	MH33::FileIO rio(inJpeg,MH33::IoMode::READ);
	MH33::GFX::DecodeTarget target;
	MH33::GFX::JPEG::decode(rio,target);
	if(target.format == MH33::GFX::Format::INVALID) {
		std::cout << "Reading JPEG failed!" << std::endl;
		return;
	}
	for(auto& it : target.frames) {
		std::cout << "JPEG frame\nWidth: " << it.width << "\nHeight: " << it.height << std::endl;
		std::stringstream stringstream;
		stringstream << "/tmp/jpeg_frame_" << imgNum++ << ".webp";
		MH33::FileIO wio(stringstream.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(it.imageData,it.width,it.height,it.stride,target.format,0.0f,wio);
	}
}
