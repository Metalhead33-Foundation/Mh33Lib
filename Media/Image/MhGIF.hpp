#ifndef GIF_HPP
#define GIF_HPP
#include <Io/MhIoDevice.hpp>
#include "MhDecodeTarget.hpp"

namespace MH33 {
namespace GFX {
namespace GIF {

void decode(Io::Device& iodev, DecodeTarget& target);

}
}
}
#endif // GIF_HPP
