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
bool decode(const Buffer& srcBuffer, int& width, int& height, int &stride, WEBP_IMGFORMAT format, Buffer& pixelData);
bool decode(IoDevice& iodev, int& width, int& height, int &stride, WEBP_IMGFORMAT format, Buffer& pixelData);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, WEBP_IMGFORMAT format, float compressionLevel, Buffer& dstBuffer);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, WEBP_IMGFORMAT format, float compressionLevel, IoDevice& dst);
struct Demuxer;
};

}
}
#endif // MHWEBP_HPP
