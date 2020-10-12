#ifndef MHWEBP_HPP
#define MHWEBP_HPP
#include <Io/MhIoDevice.hpp>

namespace MH33 {
namespace GFX {
namespace WEBP
{
enum class ImageFormat {
	RGBA,
	ARGB,
	BGRA,
	RGB,
	BGR,
	// ANIMATION ONLY
	RGB_565,
	RGBA_4444
};
struct DemuxTarget {
	struct Frame {
		Buffer pixels;
		int timestamp;
	};
	unsigned width,height;
	std::vector<Frame> frames;
	ImageFormat format; // Acts as a hint, has to be set before demuxing.
};
bool decode(const Buffer& srcBuffer, int& width, int& height, int &stride, ImageFormat format, Buffer& pixelData);
bool decode(IoDevice& iodev, int& width, int& height, int &stride, ImageFormat format, Buffer& pixelData);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, ImageFormat format, float compressionLevel, Buffer& dstBuffer);
bool encode(const Buffer& srcBuffer, int width, int height, int stride, ImageFormat format, float compressionLevel, IoDevice& dst);

bool demux(const Buffer& srcBuffer, DemuxTarget& target);
bool demux(IoDevice& iodev, DemuxTarget& target);

}
}
}
#endif // MHWEBP_HPP
