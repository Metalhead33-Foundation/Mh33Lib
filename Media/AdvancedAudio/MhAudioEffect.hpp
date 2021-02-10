#ifndef MHAUDIOEFFECT_HPP
#define MHAUDIOEFFECT_HPP
#include "MhAudioPacket.hpp"
namespace MH33 {
namespace Audio {

class Effect {
public:
	virtual ~Effect() = default;
	virtual void doEffect(const ModificationStream& modstream) = 0;
};

}
}
#endif // MHAUDIOEFFECT_HPP
