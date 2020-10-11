#ifndef MHJPEG_HPP
#define MHJPEG_HPP
#include <Io/MhIoDevice.hpp>
namespace MH33 {
namespace GFX {

namespace JPEG
{
void decode(Buffer& sourceBuff, unsigned long jpegSize, Buffer& destinationBuffer,
			int& width, int& height, int& subsamp);
void decode(IoDevice& input, Buffer& destinationBuffer,
			int& width, int& height, int& subsamp);
void encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			Buffer& destinationBuffer, unsigned long &jpegSize, int jpegSubsamp, int jpegQual);
void encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			IoDevice& destination, unsigned long &jpegSize, int jpegSubsamp, int jpegQual);
};

}
}
#endif // MHJPEG_HPP
