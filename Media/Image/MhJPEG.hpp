#ifndef MHJPEG_HPP
#define MHJPEG_HPP
#include <Media/Image/MhImage.hpp>
#include <Io/MhIoDevice.hpp>
#include <Media/Image/MhDecodeTarget.hpp>
namespace MH33 {
namespace GFX {

namespace JPEG
{
bool MH_IMAGE_API decode(Util::Buffer& sourceBuff, DecodeTarget& destination);
bool MH_IMAGE_API decode(Io::Device& input, DecodeTarget& destination);
void MH_IMAGE_API decode(Io::System& iosys, const char* path, DecodeTarget &destination);
void MH_IMAGE_API decode(Io::System& iosys, const std::string& path, DecodeTarget &destination);
bool MH_IMAGE_API encode(const Util::Buffer& sourceBuff, int width, int height, int pixelFormat,
			Util::Buffer& destinationBuffer, unsigned long &jpegSize, int jpegSubsamp, float jpegQual);
bool MH_IMAGE_API encode(const Util::Buffer& sourceBuff, int width, int height, int pixelFormat,
			Io::Device& destination, int jpegSubsamp, float jpegQual);
};

}
}
#endif // MHJPEG_HPP
