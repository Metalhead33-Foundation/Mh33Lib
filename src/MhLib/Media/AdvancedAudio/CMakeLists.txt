add_subdirectory(FX)
target_sources(${PROJECT_NAME} PRIVATE
MhModulePlayer.cpp
MhAudioStreamer.cpp
MhAudioBuffer.cpp
MhSoundSource.cpp
MhPositionalPanner.cpp
MhMatrixPanner.cpp
MhFramerateConverter.cpp
MhAudioMixer.cpp
MhAudioError.cpp
MhAudioEffectSlot.cpp
MhAmbisonicPanner.cpp
)
