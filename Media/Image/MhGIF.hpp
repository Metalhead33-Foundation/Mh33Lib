#ifndef GIF_HPP
#define GIF_HPP
#include <Media/Image/MhImage.hpp>
#include <Io/MhIoDevice.hpp>
#include <Media/Image/MhDecodeTarget.hpp>

namespace MH33 {
namespace GFX {
namespace GIF {

void MH_IMAGE_API decode(Io::Device& iodev, DecodeTarget& target);
void MH_IMAGE_API decode(Io::System& iosys, const char* path, DecodeTarget &destination);
void MH_IMAGE_API decode(Io::System& iosys, const std::string& path, DecodeTarget &destination);

}
}
}
#endif // GIF_HPP
