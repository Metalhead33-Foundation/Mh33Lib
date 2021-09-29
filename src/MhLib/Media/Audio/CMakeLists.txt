add_subdirectory(FFTConvolver)
target_sources(${PROJECT_NAME} PRIVATE
MhResampler.cpp
MhSoundFile.cpp
MhModuleRenderer.cpp
)
