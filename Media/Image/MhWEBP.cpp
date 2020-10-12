#include "MhWEBP.hpp"
#include <webp/decode.h>
#include <webp/encode.h>
#include <webp/demux.h>
#include <cmath>
#include <limits>
#include <cstring>
#include <memory>
#include <stdexcept>
namespace MH33 {
namespace GFX {
namespace WEBP {

size_t getPixelSize(ImageFormat format) {
	switch (format) {
	case ImageFormat::BGR: return 3;
	case ImageFormat::BGRA: return 4;
	case ImageFormat::RGB: return 3;
	case ImageFormat::RGBA: return 4;
	case ImageFormat::ARGB: return 4;
	case ImageFormat::RGB_565: return 2;
	case ImageFormat::RGBA_4444: return 2;
	}
}

bool decode(const Buffer &srcBuffer, int &width, int &height, int &stride, ImageFormat format, Buffer &pixelData)
{
	if(srcBuffer.empty()) return false;
	if(!WebPGetInfo(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),&width,&height)) return false;
	stride = width*getPixelSize(format);
	pixelData.resize(stride*height);
	switch (format) {
	case ImageFormat::BGR:
		return WebPDecodeBGRInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								 reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case ImageFormat::BGRA:
		return WebPDecodeBGRAInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case ImageFormat::RGB:
		return WebPDecodeRGBInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								 reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case ImageFormat::RGBA:
		return WebPDecodeRGBAInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	case ImageFormat::ARGB:
		return WebPDecodeARGBInto(reinterpret_cast<const uint8_t*>(srcBuffer.data()),srcBuffer.size(),
								  reinterpret_cast<uint8_t*>(pixelData.data()),pixelData.size(),stride) != nullptr;
	default:
		return false;
	}
}

bool decode(IoDevice &iodev, int &width, int &height, int &stride, ImageFormat format, Buffer &pixelData)
{
	auto buff = iodev.readAll();
	return decode(buff,width,height,stride,format,pixelData);
}
size_t encode(const uint8_t* pixdat, int width, int height, int stride, ImageFormat format, float compressionLevel, uint8_t** ptr)
{
	if(compressionLevel <= std::numeric_limits<float>::epsilon()) { // Lossless
		switch (format) {
		case ImageFormat::BGR:
			return WebPEncodeLosslessBGR(pixdat,width,height,stride,ptr);
		case ImageFormat::BGRA:
			return WebPEncodeLosslessBGRA(pixdat,width,height,stride,ptr);
		case ImageFormat::RGB:
			return WebPEncodeLosslessRGB(pixdat,width,height,stride,ptr);
		case ImageFormat::RGBA:
			return WebPEncodeLosslessRGBA(pixdat,width,height,stride,ptr);
		default:
			return 0;
		}
	} else {
		const float quality_factor = (1.0f-std::clamp(compressionLevel,0.0f,1.0f))*100.f;
		switch (format) {
		case ImageFormat::BGR:
			return WebPEncodeBGR(pixdat,width,height,stride,quality_factor,ptr);
		case ImageFormat::BGRA:
			return WebPEncodeBGRA(pixdat,width,height,stride,quality_factor,ptr);
		case ImageFormat::RGB:
			return WebPEncodeRGB(pixdat,width,height,stride,quality_factor,ptr);
		case ImageFormat::RGBA:
			return WebPEncodeRGBA(pixdat,width,height,stride,quality_factor,ptr);
		default:
			return 0;
		}
	}
}
bool encode(const Buffer &srcBuffer, int width, int height, int stride, ImageFormat format, float compressionLevel, Buffer &dstBuffer)
{
	if(srcBuffer.empty()) return false;
	uint8_t* out;
	auto encoded = encode(reinterpret_cast<const uint8_t*>(srcBuffer.data()),width,height,stride,format,compressionLevel,&out);
	if(!encoded) return false;
	dstBuffer.resize(encoded);
	std::memcpy(dstBuffer.data(),out,encoded);
	WebPFree(out);
	return true;
}

bool encode(const Buffer &srcBuffer, int width, int height, int stride, ImageFormat format, float compressionLevel, IoDevice &dst)
{
	if(srcBuffer.empty()) return false;
	uint8_t* out;
	auto encoded = encode(reinterpret_cast<const uint8_t*>(srcBuffer.data()),width,height,stride,format,compressionLevel,&out);
	if(!encoded) return false;
	dst.write(out,encoded);
	WebPFree(out);
	return true;
}

bool demux(const Buffer &srcBuffer, DemuxTarget &target)
{
	if(srcBuffer.empty()) return false;
	typedef std::unique_ptr<WebPDemuxer,decltype (&WebPDemuxDelete)> Configuration;
	WebPData riff;
	riff.bytes = reinterpret_cast<const uint8_t*>(srcBuffer.data());
	riff.size = srcBuffer.size();
	Configuration config = Configuration(WebPDemux(&riff),WebPDemuxDelete);
	if(!config) return false;
	target.width = WebPDemuxGetI(config.get(), WEBP_FF_CANVAS_WIDTH);
	target.height = WebPDemuxGetI(config.get(), WEBP_FF_CANVAS_HEIGHT);
	//uint32_t flags = WebPDemuxGetI(config.get(), WEBP_FF_FORMAT_FLAGS);
	//uint32_t frameCount = WebPDemuxGetI(config.get(), WEBP_FF_FRAME_COUNT);
	WebPIterator iter;
	if (WebPDemuxGetFrame(config.get(), 1, &iter)) {
		do {
			int timestamp = 0;
			const int targetSize = target.width*target.height*getPixelSize(target.format);
			target.frames.push_back(DemuxTarget::Frame());
			target.frames.back().timestamp = timestamp;
			target.frames.back().pixels.resize(targetSize);
			uint8_t* data = nullptr;
			switch (target.format) {
			case ImageFormat::BGR: data = WebPDecodeBGR(iter.fragment.bytes,iter.fragment.size,nullptr,nullptr); break;
			case ImageFormat::RGB: data = WebPDecodeRGB(iter.fragment.bytes,iter.fragment.size,nullptr,nullptr); break;
			case ImageFormat::BGRA: data = WebPDecodeBGRA(iter.fragment.bytes,iter.fragment.size,nullptr,nullptr); break;
			case ImageFormat::RGBA: data = WebPDecodeRGBA(iter.fragment.bytes,iter.fragment.size,nullptr,nullptr); break;
			case ImageFormat::ARGB: data = WebPDecodeARGB(iter.fragment.bytes,iter.fragment.size,nullptr,nullptr); break;
			default: break;
			}
			if(data) { std::memcpy(target.frames.back().pixels.data(),data,targetSize);
				WebPFree(data); }
		} while (WebPDemuxNextFrame(&iter));
		WebPDemuxReleaseIterator(&iter);
	}
	return true;
}

bool demux(IoDevice &iodev, DemuxTarget &target)
{
	auto buff = iodev.readAll();
	return demux(buff,target);
}


}
}
}
