#include "MhJPEG.hpp"
#include <turbojpeg.h>
#include <memory>

namespace MH33 {
namespace GFX {

void JPEG::encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
	Buffer& destinationBuffer, unsigned long &jpegSize, int jpegSubsamp, int jpegQual)
{
	auto handle = std::unique_ptr<void,decltype(&tjDestroy) >(tjInitCompress(),tjDestroy);
	if(!handle) return;
	destinationBuffer.resize(tjBufSize(width,height,jpegSubsamp));
	unsigned char* dstptr = reinterpret_cast<unsigned char*>(destinationBuffer.data());
	tjCompress2(handle.get(),reinterpret_cast<const unsigned char*>(sourceBuff.data()),width,width*tjPixelSize[pixelFormat],height,
				pixelFormat,&dstptr,&jpegSize,jpegSubsamp,std::clamp(jpegQual,1,100),TJFLAG_NOREALLOC | TJFLAG_FASTDCT);
}

void JPEG::decode(Buffer& sourceBuff, unsigned long jpegSize, Buffer& destinationBuffer,
				  int &width, int &height)
{
	auto handle = std::unique_ptr<void,decltype(&tjDestroy) >(tjInitDecompress(),tjDestroy);
	int scalingFactors;
	auto factorList = tjGetScalingFactors(&scalingFactors);
	if(!scalingFactors || !factorList) return;
	int subsamp;
	tjDecompressHeader2(handle.get(), reinterpret_cast<unsigned char*>(sourceBuff.data()), jpegSize, &width, &height, &subsamp);
	destinationBuffer.resize(width*height*3);
	tjDecompress2(handle.get(),reinterpret_cast<unsigned char*>(sourceBuff.data()),jpegSize,
				  reinterpret_cast<unsigned char*>(destinationBuffer.data()),width,height,width*3,TJPF_RGB,TJFLAG_FASTDCT);
}


}
}
