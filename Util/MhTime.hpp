#ifndef MHTIME_HPP
#define MHTIME_HPP
#include <ctime>
#include "../Interface/MhComparable.hpp"

namespace MH33 {
namespace Util {
class Time : public Interface::Comparable<Time>
{
private:
	clock_t ticks;
	double seconds;
	void syncFromTicks();
	void syncFromSeconds();
public:
	Time();
	Time(clock_t ticks);
	Time(double seconds);
	Time(const Time& cpy);
	Time& operator=(const Time& cpy);
	~Time() = default;
	clock_t getTicks() const;
	void setTicks(clock_t value);
	double getSeconds() const;
	void setSeconds(double value);
	Interface::ComparisonResult compare(const Time& b) const;


	// Addition
	Time& operator+=(const Time& b);
	Time& operator+=(clock_t ticks);
	Time& operator+=(double seconds);
	Time operator+(const Time& b) const;
	Time operator+(clock_t ticks) const;
	Time operator+(double seconds) const;

	// Negation
	Time& operator-=(const Time& b);
	Time& operator-=(clock_t ticks);
	Time& operator-=(double seconds);
	Time operator-(const Time& b) const;
	Time operator-(clock_t ticks) const;
	Time operator-(double seconds) const;

	// Multiplication
	Time& operator*=(clock_t scalar);
	Time& operator*=(double scalar);
	Time operator*(clock_t scalar) const;
	Time operator*(double scalar) const;

	// Division
	Time& operator/=(clock_t scalar);
	Time& operator/=(double scalar);
	Time operator/(clock_t scalar) const;
	Time operator/(double scalar) const;

	// Modulo
	Time& operator%=(clock_t scalar);
	Time& operator%=(double scalar);
	Time operator%(clock_t scalar) const;
	Time operator%(double scalar) const;
};
}
}

#endif // MHTIME_HPP
