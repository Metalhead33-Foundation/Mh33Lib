#include "MhFileIO.hpp"
namespace MH33 {

FileIO::~FileIO()
{
	if(fdev) fclose(fdev);
}

FileIO::FileIO(FileIO &&mov)
	: fdev(mov.fdev)
{
	mov.fdev = nullptr;
}

FileIO &FileIO::operator=(FileIO &&mov)
{
	if(fdev) fclose(fdev);
	this->fdev = mov.fdev;
	mov.fdev = nullptr;
	return *this;
}

FileIO::FileIO()
	: fdev(nullptr)
{

}

FileIO::FileIO(const char *path, IoMode mode)
	: fdev(nullptr), mode(mode)
{
	switch (mode) {
	case IoMode::READ:
		fdev = fopen(path,"rb");
		break;
	case IoMode::WRITE:
		fdev = fopen(path,"wb");
		break;
	case IoMode::APPEND:
		fdev = fopen(path,"ab");
		break;
	case IoMode::READ_WRITE:
		if(!(fdev = fopen(path,"r+b"))) fdev = fopen(path,"w+b");
		break;
	case IoMode::READ_APPEND:
		fdev = fopen(path,"a+b");
		break;
	}
}

FileIO::FileIO(const std::string &path, IoMode mode)
{
	switch (mode) {
	case IoMode::READ:
		fdev = fopen(path.c_str(),"rb");
		break;
	case IoMode::WRITE:
		fdev = fopen(path.c_str(),"wb");
		break;
	case IoMode::APPEND:
		fdev = fopen(path.c_str(),"ab");
		break;
	case IoMode::READ_WRITE:
		if(!(fdev = fopen(path.c_str(),"r+b"))) fdev = fopen(path.c_str(),"w+b");
		break;
	case IoMode::READ_APPEND:
		fdev = fopen(path.c_str(),"a+b");
		break;
	}
}

bool FileIO::flush()
{
	return fflush(fdev) == 0;
}

bool FileIO::seek(SeekOrigin whence, intptr_t offset)
{
	switch (whence) {
		case SeekOrigin::CUR:
			return fseek(fdev,offset,SEEK_CUR) == 0;
		case SeekOrigin::SET:
			return fseek(fdev,offset,SEEK_SET) == 0;
		case SeekOrigin::END:
			return fseek(fdev,offset,SEEK_END) == 0;
	}
	return false;
}

intptr_t FileIO::tell()
{
	return ftell(fdev);
}

intptr_t FileIO::size()
{
	auto originalPos = ftell(fdev);
	fseek(fdev,0,SEEK_END);
	auto theEnd = ftell(fdev);
	fseek(fdev,originalPos,SEEK_SET);
	return theEnd;
}

size_t FileIO::write(const void *data, size_t dataSize)
{
	return fwrite(data,1,dataSize,fdev);
}

size_t FileIO::read(void *destination, size_t dataSize)
{
	return fread(destination,1,dataSize,fdev);
}

IoMode FileIO::getMode() const
{
	return mode;
}

}
