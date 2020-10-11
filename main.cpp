#include <QCoreApplication>
#include <iostream>
#include "Media/Image/MhPng.hpp"
#include "Io/MhFileIO.hpp"

int main(int argc, char *argv[])
{
	MH33::Buffer buff;
	std::shared_ptr<MH33::FileIO> rfio = std::shared_ptr<MH33::FileIO>(
		new MH33::FileIO("/home/legacy/fonts/Anient/1/107702815_178546353636202_5419326507406443017_o.png",MH33::IoMode::READ)
		);
	std::shared_ptr<MH33::FileIO> wfio = std::shared_ptr<MH33::FileIO>(
		new MH33::FileIO("/tmp/107702815_178546353636202_5419326507406443017_o.png",MH33::IoMode::WRITE)
		);
	uint16_t width; uint16_t height; uint8_t color_type; uint8_t bit_depth;
	MH33::GFX::Png pngRead(rfio);
	MH33::GFX::Png pngWrite(wfio);
	pngRead.decode(width,height,color_type,bit_depth,buff);
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "Bit depth: " << bit_depth << std::endl;
	pngWrite.encode(width,height,color_type,bit_depth,buff,9);
	return 0;
}
