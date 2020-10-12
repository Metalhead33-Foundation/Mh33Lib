#include "MhDecompressor.hpp"
#include <zstd.h>

#define MHDHANDLE reinterpret_cast<ZSTD_DCtx*>(handle)

namespace MH33 {

Decompressor::Decompressor(Decompressor &&mov)
	: handle(mov.handle), input(mov.input), output(mov.output), inBuff(std::move(mov.inBuff)), outBuff(std::move(mov.outBuff))
{
	mov.handle = nullptr;
}

IoDevice *Decompressor::getInput() const
{
	return input;
}

void Decompressor::setInput(IoDevice *value)
{
	input = value;
}

IoDevice *Decompressor::getOutput() const
{
	return output;
}

void Decompressor::setOutput(IoDevice *value)
{
	output = value;
}

Decompressor &Decompressor::operator=(Decompressor &&mov)
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

Decompressor::Decompressor() : handle(ZSTD_createDCtx()), inBuff(ZSTD_DStreamInSize()), outBuff(ZSTD_DStreamOutSize())
{

}

Decompressor::Decompressor(IoDevice *input, IoDevice *output) : handle(ZSTD_createDCtx()), input(input), output(output),
	  inBuff(ZSTD_DStreamInSize()), outBuff(ZSTD_DStreamOutSize())
{

}

Decompressor::~Decompressor()
{
	if(handle) ZSTD_freeDCtx(MHDHANDLE);
}

void Decompressor::decompress()
{
	if(!input || !output) return;
	size_t read = 0;
	size_t lastRet = 0;
	while( (read = input->read(inBuff.data(),inBuff.size() )) ) {
		ZSTD_inBuffer znput = { inBuff.data(), read, 0 };
		while (znput.pos < znput.size) {
			ZSTD_outBuffer zutput = { outBuff.data(), outBuff.size(), 0 };
			const size_t ret = ZSTD_decompressStream(MHDHANDLE, &zutput , &znput);
			output->write(outBuff.data(),zutput.pos);
			lastRet = ret;
		}
	}
}

}
