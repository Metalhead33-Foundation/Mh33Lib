#ifndef MHDDSHEADER_HPP
#define MHDDSHEADER_HPP
#include <Io/MhDataStream.hpp>
#include "MhDecodeTarget.hpp"

namespace MH33 {
namespace GFX {
namespace DDS {

void decode(Io::Device& iodev, DecodeTarget &destination);

}
}
}
#endif // MHDDSHEADER_HPP
