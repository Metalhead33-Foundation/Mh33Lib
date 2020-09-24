#ifndef MHLOADABLE_HPP
#define MHLOADABLE_HPP
#include "MhIoDevice.hpp"
namespace MH33 {

class Loadable {
public:
	virtual ~Loadable() = default;
	virtual void load(IoDevice& source) = 0;
};

}
#endif // MHLOADABLE_HPP
