#ifndef MHPNG_HPP
#define MHPNG_HPP
#include <Io/MhIoDevice.hpp>
#include "MhDecodeTarget.hpp"
#include <memory>

namespace MH33 {
namespace GFX {
namespace PNG
{
	void decode(IoDevice& iodev, DecodeTarget &destination);
	void encode(IoDevice& iodev, uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, float compressionLevel);
};

}
}

#endif // MHPNG_HPP
