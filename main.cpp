#include <iostream>
#include "Media/Image/MhJPEG.hpp"
#include "Media/Image/MhWEBP.hpp"
#include "Media/Image/MhTgaHeader.hpp"
#include "Io/MhFileIO.hpp"
#include "Media/Image/MhWEBP.hpp"
#include <sstream>

static const char* inWebp = "/home/legacy/fonts/Anient/1/ezgif.com-webp-maker.webp";

int main(int argc, char *argv[])
{
	MH33::FileIO rfio(inWebp,MH33::IoMode::READ);
	MH33::GFX::WEBP::DemuxTarget target;
	target.format = MH33::GFX::WEBP::ImageFormat::RGBA;
	MH33::GFX::WEBP::demux(rfio,target);
	std::cout << "Width: " << target.width << std::endl;
	std::cout << "Height: " << target.height << std::endl;
	std::cout << "Frame count: " << target.frames.size() << std::endl;
	for(size_t i = 0; i < target.frames.size();++i) {
		std::stringstream str;
		str << "/tmp/frame_" << i << ".webp";
		MH33::FileIO wfio(str.str(),MH33::IoMode::WRITE);
		MH33::GFX::WEBP::encode(target.frames[i].pixels,target.width,target.height,target.width*3,target.format,0.7f,wfio);
	}
	return 0;
}
