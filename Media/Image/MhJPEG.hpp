#ifndef MHJPEG_HPP
#define MHJPEG_HPP
#include <Io/MhIoDevice.hpp>
#include "MhDecodeTarget.hpp"
namespace MH33 {
namespace GFX {

namespace JPEG
{
bool decode(Buffer& sourceBuff, DecodeTarget& destination);
bool decode(IoDevice& input, DecodeTarget& destination);
bool encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			Buffer& destinationBuffer, unsigned long &jpegSize, int jpegSubsamp, float jpegQual);
bool encode(const Buffer& sourceBuff, int width, int height, int pixelFormat,
			IoDevice& destination, int jpegSubsamp, float jpegQual);
};

}
}
#endif // MHJPEG_HPP
