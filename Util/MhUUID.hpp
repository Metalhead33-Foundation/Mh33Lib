#ifndef MHUUID_HPP
#define MHUUID_HPP
#include <Io/MhBuffer.hpp>
#include <Io/MhDataStream.hpp>
#include "MhRNG.hpp"
#include <cstring>
#include <chrono>

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
	UUID(const std::chrono::milliseconds& time, uint32_t randomnumA, uint32_t randomnumB);
	UUID(RNG& rng, bool encodeTime=true);
	UUID(const std::chrono::milliseconds &time, uint64_t randomnumA);

	void fromRandom(RNG& rng);
	void fromTimeAndRandom(const std::chrono::milliseconds& time, uint32_t randomnumA, uint32_t randomnumB);
	void fromTimeAndRandom(RNG& rng);
	void fromTimeAndRandom(const std::chrono::milliseconds& time, uint64_t randomnum);

	void toTimeAndRandom(std::chrono::milliseconds& time, uint32_t& randomNumA, uint32_t& randomNumB);
	void toTimeAndRandom(std::chrono::milliseconds& time, uint64_t& randomNum);
	void toRandom(uint32_t& randomNum1, uint32_t& randomNum2, uint32_t& randomNum3, uint32_t& randomNum4);

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
