#include <MhLib/Io/MhZstdDecompressor.hpp>
#include <zstd.h>
#include <cassert>

#define MHDHANDLE reinterpret_cast<ZSTD_DCtx*>(handle)

namespace MH33 {
namespace Io {

ZstdDecompressor::ZstdDecompressor(ZstdDecompressor &&mov)
	: handle(mov.handle), input(mov.input), output(mov.output), inBuff(std::move(mov.inBuff)), outBuff(std::move(mov.outBuff))
{
	mov.handle = nullptr;
}

Device *ZstdDecompressor::getInput() const
{
	return input;
}

void ZstdDecompressor::setInput(Device *value)
{
	input = value;
}

Device *ZstdDecompressor::getOutput() const
{
	return output;
}

void ZstdDecompressor::setOutput(Device *value)
{
	output = value;
}

void ZstdDecompressor::qucikDecompress(Device &input, Device &output)
{
	ZstdDecompressor tmp(&input,&output);
	tmp.decompress();
}

ZstdDecompressor &ZstdDecompressor::operator=(ZstdDecompressor &&mov)
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

ZstdDecompressor::ZstdDecompressor() : handle(ZSTD_createDCtx()), inBuff(ZSTD_DStreamInSize()), outBuff(ZSTD_DStreamOutSize())
{

}

ZstdDecompressor::ZstdDecompressor(Device *input, Device *output) : handle(ZSTD_createDCtx()), input(input), output(output),
	  inBuff(ZSTD_DStreamInSize()), outBuff(ZSTD_DStreamOutSize())
{

}

ZstdDecompressor::~ZstdDecompressor()
{
	if(handle) ZSTD_freeDCtx(MHDHANDLE);
}

void ZstdDecompressor::decompress()
{
	assert(handle);
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
}
