#ifndef MHDATASTREAM_HPP
#define MHDATASTREAM_HPP

#include "../Util/MhEndianness.hpp"
#include "MhIoDevice.hpp"
#include "MhSerializable.hpp"
#include "MhLoadable.hpp"
#include <string>

namespace MH33 {

template <Endian io_endianness> struct DataStream : public IoDevice {
	IoDevice& device;
	DataStream(IoDevice& ndevice) : device(ndevice) {

	}
	// Proxy around the IoDevice
	bool flush() { return device.flush(); }
	bool seek(SeekOrigin whence, intptr_t offset) { return device.seek(whence,offset); }
	intptr_t tell() { return device.tell(); }
	size_t size() { return device.size(); }
	size_t write(const void* data, size_t dataSize) { return device.write(data,dataSize); }
	size_t read(void* destination, size_t dataSize) { return device.read(destination,dataSize); }
	IoMode getMode() const { return device.getMode(); }
	// Now come the convenience functions
	DataStream& operator<<(const Serializable& data) {
		data.serialize(device);
		return *this;
	}
	DataStream& operator>>(Loadable& data) {
		data.load(device);
		return *this;
	}
	DataStream& operator<<(uint8_t data) {
		device.write(&data,sizeof(uint8_t));
		return *this;
	}
	DataStream& operator>>(uint8_t& data) {
		device.read(&data,sizeof(uint8_t));
		return *this;
	}
	DataStream& operator<<(int8_t data) {
		device.write(&data,sizeof(int8_t));
		return *this;
	}
	DataStream& operator>>(int8_t& data) {
		device.read(&data,sizeof(int8_t));
		return *this;
	}
	DataStream& operator<<(bool data) {
		device.write(&data,sizeof(bool));
		return *this;
	}
	DataStream& operator>>(bool& data) {
		device.read(&data,sizeof(bool));
		return *this;
	}
	DataStream& operator<<(uint16_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(uint16_t));
		return *this;
	}
	DataStream& operator>>(uint16_t& data) {
		device.read(&data,sizeof(uint16_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(int16_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(int16_t));
		return *this;
	}
	DataStream& operator>>(int16_t& data) {
		device.read(&data,sizeof(int16_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(half_float::half data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(half_float::half));
		return *this;
	}
	DataStream& operator>>(half_float::half& data) {
		device.read(&data,sizeof(half_float::half));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(uint32_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(uint32_t));
		return *this;
	}
	DataStream& operator>>(uint32_t& data) {
		device.read(&data,sizeof(uint32_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(int32_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(int32_t));
		return *this;
	}
	DataStream& operator>>(int32_t& data) {
		device.read(&data,sizeof(int32_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(float data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(float));
		return *this;
	}
	DataStream& operator>>(float& data) {
		device.read(&data,sizeof(float));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(uint64_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(uint64_t));
		return *this;
	}
	DataStream& operator>>(uint64_t& data) {
		device.read(&data,sizeof(uint64_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(int64_t data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(int64_t));
		return *this;
	}
	DataStream& operator>>(int64_t& data) {
		device.read(&data,sizeof(int64_t));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(double data) {
		convert_endian<Endian::Native,io_endianness>(data);
		device.write(&data,sizeof(double));
		return *this;
	}
	DataStream& operator>>(double& data) {
		device.read(&data,sizeof(double));
		convert_endian<io_endianness,Endian::Native>(data);
		return *this;
	}
	DataStream& operator<<(const std::string& data) {
		*this << uint32_t(data.size());
		device.write(data.data(),data.size());
		return *this;
	}
	DataStream& operator>>(std::string& data) {
		uint32_t len;
		*this >> len;
		data.resize(len,0);
		device.read(data.data(),len);
		return *this;
	}
};

typedef DataStream<Endian::Little> DataStreamLE;
typedef DataStream<Endian::Big> DataStreamBE;
typedef DataStream<Endian::Native> DataStreamNE;

}

#endif // MHDATASTREAM_HPP
