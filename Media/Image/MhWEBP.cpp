#include "MhWEBP.hpp"
#include <webp/decode.h>
#include <webp/demux.h>
namespace MH33 {
namespace GFX {

size_t getPixelSize(WEBP_IMGFORMAT format) {
	switch (format) {
	case WEBP_IMGFORMAT::BGR: return 3;
	case WEBP_IMGFORMAT::BGRA: return 4;
	case WEBP_IMGFORMAT::RGB: return 3;
	case WEBP_IMGFORMAT::RGBA: return 4;
	case WEBP_IMGFORMAT::ARGB: return 4;
	case WEBP_IMGFORMAT::RGB_565: return 2;
	case WEBP_IMGFORMAT::RGBA_4444: return 2;
	}
}

bool WEBP::decode(IoDevice &iodev, int &width, int &height, int &stride, WEBP_IMGFORMAT format, Buffer &pixelData)
{
	auto buff = iodev.readAll();
	if(!WebPGetInfo(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),&width,&height)) return false;
	stride = width*getPixelSize(format);
	pixelData.resize(stride*height);
	switch (format) {
	case WEBP_IMGFORMAT::BGR:
		return WebPDecodeBGRInto(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::BGRA:
		return WebPDecodeBGRAInto(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::RGB:
		return WebPDecodeRGBInto(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::RGBA:
		return WebPDecodeRGBAInto(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::ARGB:
		return WebPDecodeARGBInto(reinterpret_cast<uint8_t*>(buff.data()),buff.size(),reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	default:
		return false;
	}
}

}
}
