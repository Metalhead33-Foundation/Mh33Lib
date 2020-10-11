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
	MH33::FileIO rfio(INJPEG,MH33::IoMode::READ);
	MH33::FileIO wfio(OUTJPEG,MH33::IoMode::WRITE);
	MH33::Buffer outBuff;
	int width,height,subsamp;
	unsigned long jpegSize;
	MH33::GFX::JPEG::decode(rfio,outBuff,width,height,subsamp);
	MH33::GFX::JPEG::encode(outBuff,width,height,0,wfio,jpegSize,subsamp,50);
	return 0;
}
