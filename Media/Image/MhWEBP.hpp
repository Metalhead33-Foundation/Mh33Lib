#ifndef MHWEBP_HPP
#define MHWEBP_HPP
#include <Io/MhIoDevice.hpp>
#include "MhDecodeTarget.hpp"

namespace MH33 {
namespace GFX {
namespace WEBP
{
bool decode(const Util::Buffer& srcBuffer, DecodeTarget& target);
bool decode(Io::Device& iodev, DecodeTarget& target);
bool encode(const Util::Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, Util::Buffer& dstBuffer);
bool encode(const Util::Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, Io::Device& dst);

bool demux(const Util::Buffer& srcBuffer, DecodeTarget& target);
bool demux(Io::Device& iodev, DecodeTarget& target);

}
}
}
#endif // MHWEBP_HPP
