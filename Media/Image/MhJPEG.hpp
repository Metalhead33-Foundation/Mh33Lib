#ifndef MHJPEG_HPP
#define MHJPEG_HPP
#include <Io/MhIoDevice.hpp>
namespace MH33 {
namespace GFX {

namespace JPEG
{
bool decode(Buffer& sourceBuff, unsigned long jpegSize, Buffer& destinationBuffer,
			int& width, int& height, int& subsamp);
bool decode(IoDevice& input, Buffer& destinationBuffer,
			int& width, int& height, int& subsamp);
bool encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			Buffer& destinationBuffer, unsigned long &jpegSize, int jpegSubsamp, float jpegQual);
bool encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			IoDevice& destination, int jpegSubsamp, float jpegQual);
};

}
}
#endif // MHJPEG_HPP
