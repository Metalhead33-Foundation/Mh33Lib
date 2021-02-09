#include "MhTime.hpp"
#include <cmath>

namespace MH33 {
namespace Util {

constexpr const double clocks_per_sec = double(CLOCKS_PER_SEC);

clock_t Time::getTicks() const
{
	return ticks;
}

void Time::setTicks(clock_t value)
{
	ticks = value;
	syncFromTicks();
}

double Time::getSeconds() const
{
	return seconds;
}

void Time::setSeconds(double value)
{
	seconds = value;
	syncFromSeconds();
}

Interface::ComparisonResult Time::compare(const Time &b) const
{
	if(this->ticks == b.ticks) return Interface::EQUAL;
	else if(this->ticks > b.ticks) return Interface::GREATER;
	else return Interface::LESSER;
}

void Time::syncFromTicks()
{
	this->seconds = double(ticks) / clocks_per_sec;
}

void Time::syncFromSeconds()
{
	this->ticks = clock_t(round(this->seconds * clocks_per_sec));
}

Time::Time()
{
	this->ticks = clock();
	syncFromTicks();
}

Time::Time(clock_t ticks)
{
	this->ticks = ticks;
	syncFromTicks();
}

Time::Time(double seconds)
{
	this->seconds = seconds;
	syncFromSeconds();
}

Time::Time(const Time &cpy)
{
	this->ticks = cpy.ticks;
	this->seconds = cpy.seconds;
}

Time &Time::operator=(const Time &cpy)
{
	this->ticks = cpy.ticks;
	this->seconds = cpy.seconds;
	return *this;
}

// Addition
Time& Time::operator+=(const Time& b)
{
	this->ticks += b.ticks;
	syncFromTicks();
	return *this;
}

Time& Time::operator+=(clock_t ticks)
{
	this->ticks += ticks;
	syncFromTicks();
	return *this;
}

Time& Time::operator+=(double seconds)
{
	this->seconds += seconds;
	syncFromSeconds();
	return *this;
}

Time Time::operator+(const Time& b) const
{
	return Time(this->ticks + b.ticks);
}

Time Time::operator+(clock_t ticks) const
{
	return Time(this->ticks + ticks);
}

Time Time::operator+(double seconds) const
{
	return Time(this->seconds + seconds);
}


// Negation
Time& Time::operator-=(const Time& b)
{
	this->ticks -= b.ticks;
	syncFromTicks();
	return *this;
}

Time& Time::operator-=(clock_t ticks)
{
	this->ticks -= ticks;
	syncFromTicks();
	return *this;
}

Time& Time::operator-=(double seconds)
{
	this->seconds -= seconds;
	syncFromSeconds();
	return *this;
}

Time Time::operator-(const Time& b) const
{
	return Time(this->ticks - b.ticks);
}

Time Time::operator-(clock_t ticks) const
{
	return Time(this->ticks - ticks);
}

Time Time::operator-(double seconds) const
{
	return Time(this->seconds - seconds);
}


// Multiplication
Time& Time::operator*=(clock_t scalar)
{
	this->ticks *= scalar;
	syncFromTicks();
	return *this;
}

Time& Time::operator*=(double scalar)
{
	this->seconds *= scalar;
	syncFromSeconds();
	return *this;
}

Time Time::operator*(clock_t scalar) const
{
	return Time(this->ticks * scalar);
}

Time Time::operator*(double scalar) const
{
	return Time(this->seconds * scalar);
}


// Division
Time& Time::operator/=(clock_t scalar)
{
	this->ticks /= scalar;
	syncFromTicks();
	return *this;
}

Time& Time::operator/=(double scalar)
{
	this->seconds /= scalar;
	syncFromSeconds();
	return *this;
}

Time Time::operator/(clock_t scalar) const
{
	return Time(this->ticks / scalar);
}

Time Time::operator/(double scalar) const
{
	return Time(this->seconds / scalar);
}


// Modulo
Time& Time::operator%=(clock_t scalar)
{
	this->ticks %= scalar;
	syncFromTicks();
	return *this;
}

Time& Time::operator%=(double scalar)
{
	this->seconds = fmod(this->seconds,scalar);
	syncFromSeconds();
	return *this;
}

Time Time::operator%(clock_t scalar) const
{
	return Time(this->ticks % scalar);
}

Time Time::operator%(double scalar) const
{
	return Time(fmod(this->seconds,scalar));
}


}
}
