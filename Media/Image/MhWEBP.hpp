#ifndef MHWEBP_HPP
#define MHWEBP_HPP
#include <Media/Image/MhImage.hpp>
#include <Io/MhIoDevice.hpp>
#include <Media/Image/MhDecodeTarget.hpp>

namespace MH33 {
namespace GFX {
namespace WEBP
{
bool MH_IMAGE_API decode(const Util::Buffer& srcBuffer, DecodeTarget& target);
bool MH_IMAGE_API decode(Io::Device& iodev, DecodeTarget& target);
void MH_IMAGE_API decode(Io::System& iosys, const char* path, DecodeTarget &destination);
void MH_IMAGE_API decode(Io::System& iosys, const std::string& path, DecodeTarget &destination);
bool MH_IMAGE_API encode(const Util::Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, Util::Buffer& dstBuffer);
bool MH_IMAGE_API encode(const Util::Buffer& srcBuffer, int width, int height, int stride, Format format, float compressionLevel, Io::Device& dst);

bool MH_IMAGE_API demux(const Util::Buffer& srcBuffer, DecodeTarget& target);
bool MH_IMAGE_API demux(Io::Device& iodev, DecodeTarget& target);
void MH_IMAGE_API demux(Io::System& iosys, const char* path, DecodeTarget &destination);
void MH_IMAGE_API demux(Io::System& iosys, const std::string& path, DecodeTarget &destination);

}
}
}
#endif // MHWEBP_HPP
