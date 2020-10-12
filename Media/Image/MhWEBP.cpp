#include "MhWEBP.hpp"
#include <webp/decode.h>
#include <webp/encode.h>
#include <webp/demux.h>
#include <cmath>
#include <limits>
#include <cstring>
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

bool WEBP::decode(const Buffer &srcBuffer, int &width, int &height, int &stride, WEBP_IMGFORMAT format, Buffer &pixelData)
{
	if(!WebPGetInfo(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),&width,&height)) return false;
	stride = width*getPixelSize(format);
	pixelData.resize(stride*height);
	switch (format) {
	case WEBP_IMGFORMAT::BGR:
		return WebPDecodeBGRInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								 reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::BGRA:
		return WebPDecodeBGRAInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::RGB:
		return WebPDecodeRGBInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								 reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::RGBA:
		return WebPDecodeRGBAInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case WEBP_IMGFORMAT::ARGB:
		return WebPDecodeARGBInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	default:
		return false;
	}
}

bool WEBP::decode(IoDevice &iodev, int &width, int &height, int &stride, WEBP_IMGFORMAT format, Buffer &pixelData)
{
	auto buff = iodev.readAll();
	return decode(buff,width,height,stride,format,pixelData);
}
size_t encode(const uint8_t* pixdat, int width, int height, int stride, WEBP_IMGFORMAT format, float compressionLevel, uint8_t** ptr)
{
	if(compressionLevel <= std::numeric_limits<float>::epsilon()) { // Lossless
		switch (format) {
		case WEBP_IMGFORMAT::BGR:
			return WebPEncodeLosslessBGR(pixdat,width,height,stride,ptr);
		case WEBP_IMGFORMAT::BGRA:
			return WebPEncodeLosslessBGRA(pixdat,width,height,stride,ptr);
		case WEBP_IMGFORMAT::RGB:
			return WebPEncodeLosslessRGB(pixdat,width,height,stride,ptr);
		case WEBP_IMGFORMAT::RGBA:
			return WebPEncodeLosslessRGBA(pixdat,width,height,stride,ptr);
		default:
			return 0;
		}
	} else {
		const float quality_factor = (1.0f-std::clamp(compressionLevel,0.0f,1.0f))*100.f;
		switch (format) {
		case WEBP_IMGFORMAT::BGR:
			return WebPEncodeBGR(pixdat,width,height,stride,quality_factor,ptr);
		case WEBP_IMGFORMAT::BGRA:
			return WebPEncodeBGRA(pixdat,width,height,stride,quality_factor,ptr);
		case WEBP_IMGFORMAT::RGB:
			return WebPEncodeRGB(pixdat,width,height,stride,quality_factor,ptr);
		case WEBP_IMGFORMAT::RGBA:
			return WebPEncodeRGBA(pixdat,width,height,stride,quality_factor,ptr);
		default:
			return 0;
		}
	}
}
bool WEBP::encode(const Buffer &srcBuffer, int width, int height, int stride, WEBP_IMGFORMAT format, float compressionLevel, Buffer &dstBuffer)
{
	uint8_t* out;
	auto encoded = encode(reinterpret_cast<const uint8_t*>(srcBuffer.data()),width,height,stride,format,compressionLevel,&out);
	if(!encoded) return false;
	dstBuffer.resize(encoded);
	std::memcpy(dstBuffer.data(),out,encoded);
	WebPFree(out);
	return true;
}

bool WEBP::encode(const Buffer &srcBuffer, int width, int height, int stride, WEBP_IMGFORMAT format, float compressionLevel, IoDevice &dst)
{
	uint8_t* out;
	auto encoded = encode(reinterpret_cast<const uint8_t*>(srcBuffer.data()),width,height,stride,format,compressionLevel,&out);
	if(!encoded) return false;
	dst.write(out,encoded);
	WebPFree(out);
	return true;
}

}
}
