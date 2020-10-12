#include <QCoreApplication>
#include <iostream>
#include "Media/Image/MhJPEG.hpp"
#include "Media/Image/MhWEBP.hpp"
#include "Io/MhFileIO.hpp"

static const char* INWEBP = "/home/legacy/fonts/1.webp";
static const char* INJTGA = "/tmp/107702815_178546353636202_5419326507406443017_o.tga";
static const char* INJPEG = "/home/legacy/fonts/Anient/1/2194094.jpg";
static const char* INPNG = "/home/legacy/fonts/Anient/1/107702815_178546353636202_5419326507406443017_o.png";
static const char* OUTWEBP = "/tmp/107702815_178546353636202_5419326507406443017_o.webp";
static const char* OUTJPEG = "/tmp/107702815_178546353636202_5419326507406443017_o.jpg";
static const char* OUTPNG = "/tmp/107702815_178546353636202_5419326507406443017_o.png";

// bool decode(IoDevice& iodev, int& width, int& height, unsigned& stride, WEBP_IMGFORMAT format, Buffer& pixelData);

int main(int argc, char *argv[])
{
	MH33::Buffer buff;
	MH33::FileIO rfio(INWEBP,MH33::IoMode::READ);
	MH33::FileIO wfio(OUTWEBP,MH33::IoMode::WRITE);
	int width; int height; int stride;
	MH33::GFX::WEBP::decode(rfio,width,height,stride,MH33::GFX::WEBP_IMGFORMAT::RGB,buff);
	MH33::GFX::WEBP::encode(buff,width,height,stride,MH33::GFX::WEBP_IMGFORMAT::RGB,0.5f,wfio);
	return 0;
}
