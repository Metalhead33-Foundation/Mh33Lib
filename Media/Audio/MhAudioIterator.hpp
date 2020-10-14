#ifndef MHAUDIOITERATOR_HPP
#define MHAUDIOITERATOR_HPP
#include <Util/MhIntegralIterator.hpp>
#include <cstdint>
#include <cmath>
#include <type_traits>
namespace MH33 {
namespace Audio {

typedef IntegralIterator<uint_fast8_t> ChannelIndex;
typedef IntegralIterable<uint_fast8_t> ChannelCount;
typedef IntegralIterator<uintptr_t> SampleIndex;
struct SampleCount : public IntegralIterable<uintptr_t> {
	typedef IntegralIterable<uintptr_t> BaseType;
	SampleCount(const BaseType& other) : BaseType(other) {

	}
	explicit SampleCount(uintptr_t num=0) : BaseType(num) {

	}
	inline uintptr_t toBytes() const { return var * sizeof(float); }
};
typedef IntegralIterator<uintptr_t> FrameIndex;
struct FrameRate : public IntegralIterable<uintptr_t> {
	typedef IntegralIterable<uintptr_t> BaseType;
	FrameRate(const BaseType& other) : BaseType(other) {

	}
	explicit FrameRate(uintptr_t num=0) : BaseType(num) {

	}
};
struct FrameCount : public IntegralIterable<uintptr_t> {
	typedef IntegralIterable<uintptr_t> BaseType;
	FrameCount(const BaseType& other) : BaseType(other) {

	}
	explicit FrameCount(uintptr_t num=0) : BaseType(num) {

	}
	static inline FrameCount fromSamples(const SampleCount& samples, const ChannelCount& channels) {
		return FrameCount(samples.var / uintptr_t(channels.var));
	}
	inline SampleCount toSamples(ChannelCount channels) const { return SampleCount(var * uintptr_t(channels.var) ); }
	inline uintptr_t toBytes(ChannelCount channels) const { return SampleCount(var * uintptr_t(channels.var) ).toBytes(); }
	template<typename SecondType = double> inline SecondType toSeconds(const FrameRate& framerate) const {
		static_assert (std::is_floating_point<SecondType>(),"Must use floating point types when calculating seconds!");
		return SecondType(var) / SecondType(framerate.var);
	}
	template<typename SecondType = double> static inline FrameCount fromSeconds(SecondType seconds, const FrameRate& framerate) {
		static_assert (std::is_floating_point<SecondType>(),"Must use floating point types when calculating seconds!");
		return FrameCount(uintptr_t(std::ceil(seconds * SecondType(framerate.var)) ) );
	}
};

}
}
#endif // MHAUDIOITERATOR_HPP
