#ifndef CLOCK_HPP
#define CLOCK_HPP
#include "MhTime.hpp"

namespace MH33 {
namespace Util {

class Clock
{
private:
	clock_t lastClock;
public:
	Clock();
	Time elapsed() const;
	void restart();
	void restartAndReturn(Time& dst);
	Time restartAndReturn();
};

}
}

#endif // CLOCK_HPP
