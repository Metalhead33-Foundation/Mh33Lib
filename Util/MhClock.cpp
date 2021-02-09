#include "MhClock.hpp"

namespace MH33 {
namespace Util {
Clock::Clock()
{
	lastClock = clock();
}

Time Clock::elapsed() const
{
	return Time(clock() - lastClock);
}

void Clock::restart()
{
	this->lastClock = clock();
}

void Clock::restartAndReturn(Time &dst)
{
	clock_t cache = this->lastClock;
	this->lastClock = clock();
	dst.setTicks(this->lastClock - cache);
}

Time Clock::restartAndReturn()
{
	clock_t cache = this->lastClock;
	this->lastClock = clock();
	return Time(this->lastClock - cache);
}

}
}
