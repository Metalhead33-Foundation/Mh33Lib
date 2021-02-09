#ifndef MODULEPLAYER_HPP
#define MODULEPLAYER_HPP
#include "MhAudioPlayable.hpp"
#include "MhAudioStatus.hpp"
#include "../Audio/MhModuleRenderer.hpp"

namespace MH33 {
namespace Audio {

class ModulePlayer : public Playable
{
private:
	ModuleRenderer renderer;
	Status state;
public:
	ModulePlayer(const Io::sDevice& iodev);
	ModulePlayer(Io::sDevice&& iodev);
	ModulePlayer(Io::DeviceCreator iodev_creator, Io::Mode mode);
	ModulePlayer(Io::System& iosys, const char* path, Io::Mode mode);
	ModulePlayer(Io::System& iosys, const std::string& path, Io::Mode mode);
	FrameCount outputTo(const Output& dst);
	ModuleRenderer& getRenderer();
	const ModuleRenderer& getRenderer() const;
	Status getState() const;
	void setState(const Status &value);
};

}
}
#endif // MODULEPLAYER_HPP
