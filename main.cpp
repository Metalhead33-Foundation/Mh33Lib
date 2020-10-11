#include <QCoreApplication>
#include <iostream>
#include "Media/Image/MhJPEG.hpp"
#include "Media/Image/MhPNG.hpp"
#include "Media/Image/MhTgaHeader.hpp"
#include "Io/MhFileIO.hpp"

static const char* INJTGA = "/tmp/107702815_178546353636202_5419326507406443017_o.tga";
static const char* INJPEG = "/home/legacy/fonts/Anient/1/2194094.jpg";
static const char* INPNG = "/home/legacy/fonts/Anient/1/107702815_178546353636202_5419326507406443017_o.png";
static const char* OUTJPEG = "/tmp/107702815_178546353636202_5419326507406443017_o.jpg";
static const char* OUTPNG = "/tmp/107702815_178546353636202_5419326507406443017_o.png";

int main(int argc, char *argv[])
{
	MH33::Buffer buff;
	MH33::FileIO rfio(INJTGA,MH33::IoMode::READ);
	MH33::FileIO wfio(OUTJPEG,MH33::IoMode::WRITE);
	MH33::GFX::TgaHeader targa;
	targa.load(rfio);
	std::cout << targa.imageSpecification.width << "x" << targa.imageSpecification.height << std::endl;
	MH33::GFX::JPEG::encode(targa.imageData,targa.imageSpecification.width,targa.imageSpecification.height,1,wfio,0,50);
	return 0;
}
