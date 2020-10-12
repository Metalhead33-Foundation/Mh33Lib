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
	if(!config) throw std::runtime_error("Failed to initialize demux config!");
	target.width = WebPDemuxGetI(config.get(), WEBP_FF_CANVAS_WIDTH);
	target.height = WebPDemuxGetI(config.get(), WEBP_FF_CANVAS_HEIGHT);
	//uint32_t flags = WebPDemuxGetI(config.get(), WEBP_FF_FORMAT_FLAGS);
	//uint32_t frameCount = WebPDemuxGetI(config.get(), WEBP_FF_FRAME_COUNT);
	int bytesPerPixel = 0;
	WebPAnimDecoderOptions dec_options;
	if(!WebPAnimDecoderOptionsInit(&dec_options)) throw std::runtime_error("Failed to initialize demux codec options!");
	switch(target.format)
	{
	case ImageFormat::RGBA:
	{
		dec_options.color_mode = MODE_RGBA;
		bytesPerPixel = 4;
		break;
	}
	case ImageFormat::ARGB:
	{
		dec_options.color_mode = MODE_ARGB;
		bytesPerPixel = 4;
		break;
	}
	case ImageFormat::BGRA:
	{
		dec_options.color_mode = MODE_BGRA;
		bytesPerPixel = 4;
		break;
	}
	case ImageFormat::RGB:
	{
		dec_options.color_mode = MODE_RGB;
		bytesPerPixel = 3;
		break;
	}
	case ImageFormat::BGR:
	{
		dec_options.color_mode = MODE_BGR;
		bytesPerPixel = 3;
		break;
	}
	case ImageFormat::RGB_565:
	{
		dec_options.color_mode = MODE_RGB_565;
		bytesPerPixel = 2;
		break;
	}
	case ImageFormat::RGBA_4444:
	{
		dec_options.color_mode = MODE_RGBA_4444;
		bytesPerPixel = 2;
		break;
	}
	}
	dec_options.use_threads = 1;
	//target.frames.resize(frameCount);
	std::unique_ptr<WebPAnimDecoder,decltype (&WebPAnimDecoderDelete)> decoder(WebPAnimDecoderNew(&riff,&dec_options),WebPAnimDecoderDelete);
	if(!decoder) throw std::runtime_error("Failed to initialize WebP animation decoder!");
	WebPAnimInfo anim_info;
	//WebPAnimDecoderGetInfo(decoder.get(), &anim_info);
	if(!WebPAnimDecoderGetInfo(decoder.get(), &anim_info)) throw std::runtime_error("Failed to fetch animation information!");
	target.width = anim_info.canvas_width;
	target.height = anim_info.canvas_height;
	//target.frames.resize(frameCount);
	// WebPAnimDecoderReset(decoder.get());
	while (WebPAnimDecoderHasMoreFrames(decoder.get())) {
		uint8_t* buf;
		int timestamp;
		const int targetSize = target.width*target.height*bytesPerPixel;
		WebPAnimDecoderGetNext(decoder.get(), &buf, &timestamp);
		target.frames.push_back(DemuxTarget::Frame());
		target.frames.back().timestamp = timestamp;
		target.frames.back().pixels.resize(targetSize);
		memcpy(target.frames.back().pixels.data(),buf,targetSize);
	}
		WebPAnimDecoderReset(decoder.get());
	/*for (uint32_t i = 0; i < frameCount; ++i) {
		if(!WebPAnimDecoderHasMoreFrames(decoder.get())) break;
			uint8_t* buf;
			int timestamp;
			WebPAnimDecoderGetNext(decoder.get(), &buf, &timestamp);
			target.frames[i].timestamp = timestamp;
			target.frames[i].pixels.resize(target.width*target.height*bytesPerPixel);
			memcpy(target.frames[i].pixels.data(),buf,target.width*target.height*bytesPerPixel);
	}*/
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
