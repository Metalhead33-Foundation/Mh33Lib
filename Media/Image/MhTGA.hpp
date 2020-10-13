#ifndef MHTGAHEADER_HPP
#define MHTGAHEADER_HPP
#include <Io/MhDataStream.hpp>
#include "MhDecodeTarget.hpp"

namespace MH33 {
namespace GFX {
namespace TGA {

void decode(IoDevice& iodev, DecodeTarget &destination);

}
}
}
#endif // MHTGAHEADER_HPP
