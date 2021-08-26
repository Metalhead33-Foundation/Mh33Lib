#include <MhLib/Io/MhZstdCompressor.hpp>
#include <zstd.h>
#include <cassert>

#define MCHANDLE reinterpret_cast<ZSTD_CCtx*>(handle)

namespace MH33 {
namespace Io {

ZstdCompressor::ZstdCompressor(ZstdCompressor &&mov)
	: handle(mov.handle), input(mov.input), output(mov.output), inBuff(std::move(mov.inBuff)), outBuff(std::move(mov.outBuff))
{
	mov.handle = nullptr;
}

Device *ZstdCompressor::getInput() const
{
	return input;
}

void ZstdCompressor::setInput(Device *value)
{
	input = value;
}

Device *ZstdCompressor::getOutput() const
{
	return output;
}

void ZstdCompressor::setOutput(Device *value)
{
	output = value;
}

void ZstdCompressor::quickCompress(Device &input, Device &output, float compressionLevel, bool checksum)
{
	ZstdCompressor tmp(&input,&output);
	tmp.setCompressionLevel(compressionLevel);
	tmp.setChecksum(checksum);
	tmp.compress();
}

ZstdCompressor &ZstdCompressor::operator=(ZstdCompressor &&mov)
{
	this->handle = mov.handle;
	mov.handle = nullptr;
	this->input = mov.input;
	mov.input = nullptr;
	this->output = mov.output;
	mov.output = nullptr;
	this->inBuff = std::move(mov.inBuff);
	this->outBuff = std::move(mov.outBuff);
	return *this;
}

ZstdCompressor::ZstdCompressor() : handle(ZSTD_createCCtx()), inBuff(ZSTD_CStreamInSize()), outBuff(ZSTD_CStreamOutSize())
{

}

ZstdCompressor::ZstdCompressor(Device *input, Device *output) : handle(ZSTD_createCCtx()), input(input), output(output),
	  inBuff(ZSTD_CStreamInSize()), outBuff(ZSTD_CStreamOutSize())
{

}

ZstdCompressor::~ZstdCompressor()
{
	if(handle) MCHANDLE;
}

void ZstdCompressor::compress()
{
	assert(handle);
	for (;;) {
		const size_t read = input->read(inBuff.data(),inBuff.size());
		const bool lastChunk = read < inBuff.size();
		const ZSTD_EndDirective mode = lastChunk ? ZSTD_e_end : ZSTD_e_continue;
		ZSTD_inBuffer znput = { inBuff.data(), read, 0 };
		bool finished;
		do {
			ZSTD_outBuffer zutput = { outBuff.data(), outBuff.size(), 0 };
			const size_t remaining = ZSTD_compressStream2(MCHANDLE, &zutput , &znput, mode);
			output->write(outBuff.data(),zutput.pos);
			finished = lastChunk ? (remaining == 0) : (znput.pos == znput.size);
		} while(!finished);
		if (lastChunk) {
			break;
		}
	}
}

void ZstdCompressor::setCompressionLevel(float value)
{
	assert(handle);
	auto bounds = ZSTD_cParam_getBounds(ZSTD_c_compressionLevel);
	const float range = float(bounds.upperBound) - float(bounds.lowerBound);
	int nval = int( (value*range)+float(bounds.lowerBound) );
	ZSTD_CCtx_setParameter(MCHANDLE,ZSTD_c_compressionLevel,nval);
}

void ZstdCompressor::setChecksum(bool value)
{
	assert(handle);
	ZSTD_CCtx_setParameter(MCHANDLE,ZSTD_c_checksumFlag,value);
}

}
}
