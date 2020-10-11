#include <QCoreApplication>
#include <iostream>
#include "Media/Image/MhJPEG.hpp"
#include "Media/Image/MhPNG.hpp"
#include "Io/MhFileIO.hpp"

static const char* INJPEG = "/home/legacy/fonts/Anient/1/2194094.jpg";
static const char* INPNG = "/home/legacy/fonts/Anient/1/107702815_178546353636202_5419326507406443017_o.png";
static const char* OUTJPEG = "/tmp/107702815_178546353636202_5419326507406443017_o.jpg";
static const char* OUTPNG = "/tmp/107702815_178546353636202_5419326507406443017_o.png";

int main(int argc, char *argv[])
{
	MH33::Buffer buff;
	MH33::FileIO rfio(INPNG,MH33::IoMode::READ);
	MH33::FileIO wfio(OUTJPEG,MH33::IoMode::WRITE);
	//auto inBuff = rfio.readAll();
	MH33::Buffer inBuff;
	MH33::Buffer outBuff;
	uint16_t height,width;
	uint8_t cltype;
	uint8_t bitdepth;
	MH33::GFX::PNG::decode(rfio,width,height,cltype,bitdepth,inBuff);
	/*int width; int height;
	MH33::GFX::JPEG::decode(inBuff,inBuff.size(),outBuff,width,height);
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
	MH33::GFX::PNG::encode(wfio,width,height,2,8,outBuff,4);*/
	unsigned long jpegSize;
	MH33::GFX::JPEG::encode(inBuff,width,height,0,outBuff,jpegSize,2,50);
	wfio.write(outBuff.data(),jpegSize);
	return 0;
}
