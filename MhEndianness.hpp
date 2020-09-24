#ifndef MHENDIANNESS_HPP
#define MHENDIANNESS_HPP
#include <cstdint>
#include <array>
#include <algorithm>
#include "half.hpp"

#ifdef _WIN32
#define MH_LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MH_LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MH_BIG_ENDIAN
#else
#error "Failed to determine system endianness!"
#endif

template <typename T> struct _endianness_swp {
	inline static void do_swp(T &val) {
		union U {
			T val;
			std::array<std::uint8_t, sizeof(T)> raw;
		} src, dst;

		src.val = val;
		std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
		val = dst.val;
	}
};
template <> struct _endianness_swp<uint8_t> {
	typedef uint8_t T;
	inline static void do_swp(T &val) {
		(void)val;
	}
};
// Fallbacks for processors that don't have bswap
template <> struct _endianness_swp<uint16_t> {
	typedef uint16_t T;
	inline static void do_swp(T &val) {
		val = (val >> 8) | (val << 8);
	}
};
template <> struct _endianness_swp<uint32_t> {
	typedef uint32_t T;
	inline static void do_swp(T &val) {
		uint32_t tmp = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
		val = (tmp << 16) | (tmp >> 16);
	}
};
template <> struct _endianness_swp<uint64_t> {
	typedef uint64_t T;
	inline static void do_swp(T &val) {
		val = ((val & 0x00000000FFFFFFFFull) << 32) | ((val & 0xFFFFFFFF00000000ull) >> 32);
		val = ((val & 0x0000FFFF0000FFFFull) << 16) | ((val & 0xFFFF0000FFFF0000ull) >> 16);
		val = ((val & 0x00FF00FF00FF00FFull) << 8)  | ((val & 0xFF00FF00FF00FF00ull) >> 8);
	}
};
// Aliases for signed types and others.
template <> struct _endianness_swp<int8_t> {
	typedef int8_t T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint8_t>::do_swp(*reinterpret_cast<uint8_t*>(&val));
	}
};
template <> struct _endianness_swp<int16_t> {
	typedef int16_t T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint16_t>::do_swp(*reinterpret_cast<uint16_t*>(&val));
	}
};
template <> struct _endianness_swp<int32_t> {
	typedef int32_t T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint32_t>::do_swp(*reinterpret_cast<uint32_t*>(&val));
	}
};
template <> struct _endianness_swp<int64_t> {
	typedef int64_t T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint64_t>::do_swp(*reinterpret_cast<uint64_t*>(&val));
	}
};
template <> struct _endianness_swp<half_float::half> {
	typedef half_float::half T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint16_t>::do_swp(*reinterpret_cast<uint16_t*>(&val));
	}
};
template <> struct _endianness_swp<float> {
	typedef float T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint32_t>::do_swp(*reinterpret_cast<uint32_t*>(&val));
	}
};
template <> struct _endianness_swp<double> {
	typedef double T;
	inline static void do_swp(T &val) {
		_endianness_swp<uint64_t>::do_swp(*reinterpret_cast<uint64_t*>(&val));
	}
};

// Swaps endianness no matter what. Dangerous and not recommended.
template <typename T> void swap_endian(T& val) {
	_endianness_swp<T>::do_swp(val);
}

// Converts native data to big-endian data and vice versa. No-op if system is big-endian.
template <typename T> void big_endian(T& val) {
#ifdef MH_BIG_ENDIAN
	(void)val;
#else
	_endianness_swp<T>::do_swp(val);
#endif
}

// Converts native data to little-endian data and vice versa. No-op if system is little-endian.
template <typename T> void little_endian(T& val) {
#ifdef MH_LITTLE_ENDIAN
	(void)val;
#else
	_endianness_swp<T>::do_swp(val);
#endif
}

#endif // MHENDIANNESS_HPP
