#ifndef MHWEBP_HPP
#define MHWEBP_HPP
#include <Io/MhIoDevice.hpp>
#include "MhDecodeTarget.hpp"

namespace MH33 {
namespace GFX {
namespace WEBP
{
bool decode(const Buffer& srcBuffer, DecodeTarget& target);
bool decode(IoDevice& iodev, DecodeTarget& target);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, Buffer& dstBuffer);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, IoDevice& dst);

bool demux(const Buffer& srcBuffer, DecodeTarget& target);
bool demux(IoDevice& iodev, DecodeTarget& target);

}
}
}
#endif // MHWEBP_HPP
