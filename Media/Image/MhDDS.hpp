#ifndef MHDDSHEADER_HPP
#define MHDDSHEADER_HPP
#include <Media/Image/MhImage.hpp>
#include <Io/MhDataStream.hpp>
#include <Media/Image/MhDecodeTarget.hpp>

namespace MH33 {
namespace GFX {
namespace DDS {

void MH_IMAGE_API decode(Io::Device& iodev, DecodeTarget &destination);
void MH_IMAGE_API decode(Io::System& iosys, const char* path, DecodeTarget &destination);
void MH_IMAGE_API decode(Io::System& iosys, const std::string& path, DecodeTarget &destination);

}
}
}
#endif // MHDDSHEADER_HPP
