QT -= gui

CONFIG += c++2a console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH ''= $$top_srcdir/include

# PNG
LIBS += -lpng
# GIF
LIBS += -lgif
# JPEG
LIBS += -lturbojpeg
# WEBP
LIBS += -lwebpdemux -lwebpmux -lwebp -lwebpdecoder
# OpenMPT
LIBS += -lopenmpt
# SNDFILE
LIBS += -lsndfile
# LibSamplerate
LIBS += -lsamplerate
# PHYSFS
LIBS += -lphysfs
# ZSTD for compressing and decompressing
LIBS += -lzstd

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Io/MhBufferWrapper.cpp \
        Io/MhCompressor.cpp \
        Io/MhDecompressor.cpp \
        Io/MhFileIO.cpp \
        Io/MhSocket.cpp \
        Io/MhStderr.cpp \
        Io/MhStdin.cpp \
        Io/MhStdout.cpp \
        Io/PhysFSIO.cpp \
        Io/private/MhSocketUnix.cpp \
        Media/Audio/MhModuleRenderer.cpp \
        Media/Audio/MhResampler.cpp \
        Media/Audio/MhSoundFile.cpp \
        Media/Image/MhDDS.cpp \
        Media/Image/MhGIF.cpp \
        Media/Image/MhJPEG.cpp \
        Media/Image/MhPNG.cpp \
        Media/Image/MhTGA.cpp \
        Media/Image/MhWEBP.cpp \
        Util/MhRNG.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	Io/MhBuffer.hpp \
	Io/MhBufferWrapper.hpp \
	Io/MhCompressor.hpp \
	Io/MhDataStream.hpp \
	Io/MhDecompressor.hpp \
	Io/MhFileIO.hpp \
	Io/MhIoDevice.hpp \
	Io/MhSocket.hpp \
	Io/MhStderr.hpp \
	Io/MhStdin.hpp \
	Io/MhStdout.hpp \
	Io/PhysFSIO.hpp \
	Io/private/MhSocketUnix.hpp \
	Media/Audio/MhAudioIterator.hpp \
	Media/Audio/MhModuleRenderer.hpp \
	Media/Audio/MhResampler.hpp \
	Media/Audio/MhSoundFile.hpp \
	Media/Image/MhDDS.hpp \
	Media/Image/MhDecodeTarget.hpp \
	Media/Image/MhGIF.hpp \
	Media/Image/MhJPEG.hpp \
	Media/Image/MhPNG.hpp \
	Media/Image/MhStandardColourFormat.hpp \
	Media/Image/MhTGA.hpp \
	Media/Image/MhWEBP.hpp \
	Util/MhEndianness.hpp \
	Util/MhIntegralIterator.hpp \
	Util/MhNormDenorm.hpp \
	Util/MhRNG.hpp \
	Util/half.hpp

DISTFILES += \
	LICENSE \
	README.md
