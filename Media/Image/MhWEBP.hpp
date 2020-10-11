#ifndef MHWEBP_HPP
#define MHWEBP_HPP
#include <Io/MhIoDevice.hpp>

namespace MH33 {
namespace GFX {

enum class WEBP_IMGFORMAT {
	RGBA,
	ARGB,
	BGRA,
	RGB,
	BGR,
	// ANIMATION ONLY
	RGB_565,
	RGBA_4444
};

namespace WEBP
{
bool decode(IoDevice& iodev, int& width, int& height, int &stride, WEBP_IMGFORMAT format, Buffer& pixelData);
//void encode(IoDevice& iodev, uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, int compressionLevel);
struct Demuxer;
};

}
}
#endif // MHWEBP_HPP
