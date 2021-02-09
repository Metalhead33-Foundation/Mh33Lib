#ifndef MHAUDIOPLAYABLE_HPP
#define MHAUDIOPLAYABLE_HPP
#include "MhAudioPacket.hpp"
#include <memory>
namespace MH33 {
namespace Audio {

class Playable;
typedef std::shared_ptr<Playable> sPlayable;
class Playable {
public:
	virtual ~Playable() = default;
	virtual FrameCount outputTo(const Output& dst) = 0;
};

}
}
#endif // MHAUDIOPLAYABLE_HPP
