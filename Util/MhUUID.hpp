#ifndef MHUUID_HPP
#define MHUUID_HPP
#include <Io/MhBuffer.hpp>
#include <Io/MhDataStream.hpp>
#include <cstring>
namespace MH33 {
struct UUID
{
	static constexpr const size_t size = 16;
	uint8_t __uuid[size];
/*
#ifdef __SIZEOF_INT128__
#define NATIVE_128BIT_SUPPORT
	__int128 __uuid;
#else
	std::pair<uint64_t,uint64_t> __uuid;
#endif
*/
	UUID();
	UUID(const UUID& cpy);
	UUID& operator=(const UUID& cpy);
	UUID(const Buffer& cpy);
	UUID& operator=(const Buffer& cpy);
	// String stuff
	std::string toString(bool curlyBraces=true) const;
	UUID& operator=(const std::string& string);
	UUID(const std::string& string);
};

template <Endian io_endianness> DataStream<io_endianness>& operator<<(DataStream<io_endianness>& stream, const UUID& uuid) {
	stream.write(uuid.__uuid,uuid.size);
	return stream;
}
template <Endian io_endianness> DataStream<io_endianness>& operator>>(DataStream<io_endianness>& stream, UUID& uuid) {
	stream.read(uuid.__uuid,uuid.size);
	return stream;
}

struct UUIDComparer
{
	bool operator()(const UUID & Left, const UUID & Right) const
	{
		return memcmp(Left.__uuid , Right.__uuid,UUID::size) == -1;
	}
};

template<class T, class Allocator = std::allocator<std::pair<const UUID, T>>> using UuidMap = std::map<UUID,T,UUIDComparer,Allocator>;

}
#endif // MHUUID_HPP
