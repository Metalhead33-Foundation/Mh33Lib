#include <QCoreApplication>
#include <iostream>
#include "Media/Image/MhJPEG.hpp"
#include "Media/Image/MhWEBP.hpp"
#include "Media/Image/MhTgaHeader.hpp"
#include "Io/MhFileIO.hpp"
#include "Io/MhCompressor.hpp"
#include "Io/MhDecompressor.hpp"

static const char* INWEBP = "/home/legacy/fonts/1.webp";
static const char* OUTZSTD = "/tmp/1.webp.zst";
static const char* OUTWEBP = "/tmp/1.webp";

// bool decode(IoDevice& iodev, int& width, int& height, unsigned& stride, WEBP_IMGFORMAT format, Buffer& pixelData);

int main(int argc, char *argv[])
{
	//MH33::Buffer buff;
	MH33::FileIO rfio(OUTZSTD,MH33::IoMode::READ);
	MH33::FileIO wfio(OUTWEBP,MH33::IoMode::WRITE);
	/*MH33::Compressor compress(&rfio,&wfio);
	compress.setCompressionLevel(0.8f);
	compress.compress();*/
	MH33::Decompressor decompress(&rfio,&wfio);
	decompress.decompress();
	//MH33::GFX::WEBP::encode(buff,width,height,stride,MH33::GFX::WEBP_IMGFORMAT::RGB,0.5f,wfio);
	return 0;
}
