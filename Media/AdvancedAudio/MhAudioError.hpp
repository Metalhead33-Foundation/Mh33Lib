#ifndef MHAUDIOERROR_HPP
#define MHAUDIOERROR_HPP
#include <exception>
#include <string>
#include "MhAudioPacket.hpp"

namespace MH33 {
namespace Audio {

class ChannelCountMismatchError : public std::exception {
private:
	const ChannelCount excepted,received;
	std::string str;
public:
	ChannelCountMismatchError(ChannelCount excepted, ChannelCount received);
	const char* what() const noexcept;
	ChannelCount getExcepted() const;
	ChannelCount getReceived() const;
};
class FrameratetMismatchError : public std::exception {
private:
	const FrameRate excepted,received;
	std::string str;
public:
	FrameratetMismatchError(FrameRate excepted, FrameRate received);
	const char* what() const noexcept;
	FrameRate getExcepted() const;
	FrameRate getReceived() const;
};
class InterleavingMismatchError : public std::exception {
private:
	const InterleavingType excepted,received;
	std::string str;
public:
	InterleavingMismatchError(InterleavingType excepted, InterleavingType received);
	const char* what() const noexcept;
	InterleavingType getExcepted() const;
	InterleavingType getReceived() const;
};

}
}

#endif // MHAUDIOERROR_HPP