#ifndef MHSERIALIZABLE_HPP
#define MHSERIALIZABLE_HPP
#include "MhIoDevice.hpp"
namespace MH33 {

class Serializable {
public:
	virtual ~Serializable() = default;
	virtual void serialize(IoDevice& destination) const = 0;
};

}
#endif // MHSERIALIZABLE_HPP
