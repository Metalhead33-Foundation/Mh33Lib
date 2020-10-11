#ifndef MHPNG_HPP
#define MHPNG_HPP
#include <Io/MhIoDevice.hpp>
#include <memory>

namespace MH33 {
namespace GFX {

namespace PNG
{
	void decode(IoDevice& iodev, uint16_t& width, uint16_t& height, uint8_t& color_type, uint8_t& bit_depth, Buffer& pixelData);
	void encode(IoDevice& iodev, uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, int compressionLevel);
};

}
}

#endif // MHPNG_HPP
