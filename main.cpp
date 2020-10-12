#include <iostream>
#include "Media/Image/MhGIF.hpp"
#include "Io/MhFileIO.hpp"
#include "Media/Image/MhWEBP.hpp"
#include <sstream>

static const char* inGif = "/home/legacy/fonts/Anient/1/anime/aoi_ren/1/2/25.gif";

int main(int argc, char *argv[])
{
	MH33::FileIO rfio(inGif,MH33::IoMode::READ);
	MH33::GFX::GIF::DecodeTarget target;
	MH33::GFX::GIF::decode(rfio,target);
	std::cout << "Width: " << target.width << std::endl;
	std::cout << "Height: " << target.height << std::endl;
	std::cout << "Frame count: " << target.frames.size() << std::endl;
	std::cout << "Palette size: " << target.palette.size() << std::endl;
	for(size_t i = 0; i < target.frames.size(); ++i) {
		std::stringstream sstream;
		sstream << "/tmp/frame_" << i << ".webp";
		MH33::Buffer tmpBuff(sizeof(MH33::GFX::RGB<uint8_t>)*target.width*target.height);
		MH33::GFX::RGB<uint8_t>* pixels = reinterpret_cast<MH33::GFX::RGB<uint8_t>*>(tmpBuff.data());
		for(int y = 0; y < target.height; ++y) {
			const uint8_t* base = &target.frames[i][target.width*y];
			MH33::GFX::RGB<uint8_t>* currentRow = &pixels[target.width*y];
			for(int x = 0; x < target.width; ++x) {
				currentRow[x].r = target.palette[base[x]].r;
				currentRow[x].g = target.palette[base[x]].g;
				currentRow[x].b = target.palette[base[x]].b;
			}
		}
		MH33::FileIO wfio(sstream.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(tmpBuff,target.width,target.height,target.width*3,MH33::GFX::WEBP::ImageFormat::RGB,0.8f,wfio);
	}
	return 0;
}
