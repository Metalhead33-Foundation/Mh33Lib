#ifndef MODULEPLAYER_HPP
#define MODULEPLAYER_HPP
#include <Media/AdvancedAudio/MhAdvancedAudio.hpp>
#include <Media/AdvancedAudio/MhAudioPlayable.hpp>
#include <Media/AdvancedAudio/MhAudioStatus.hpp>
#include <Media/Audio/MhModuleRenderer.hpp>

namespace MH33 {
namespace Audio {

class MH_ADV_AUDIO_API ModulePlayer : public Playable
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
	FrameRate getFrameRate() const;
	ChannelCount getChannelCount() const;
	static FrameRate preferredSampleRate;
	static ChannelCount preferredChannelCount;
};

}
}
#endif // MODULEPLAYER_HPP
