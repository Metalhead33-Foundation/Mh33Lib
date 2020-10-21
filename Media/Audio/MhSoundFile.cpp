#include "MhSoundFile.hpp"
#include <sndfile.h>
#include <cstring>

sf_count_t sfGetFilelen( void *user_data );
sf_count_t sfSeek( sf_count_t offset, int whence, void *user_data );
sf_count_t sfRead( void *ptr, sf_count_t count, void *user_data );
sf_count_t sfWrite( const void *ptr, sf_count_t count, void *user_data );
sf_count_t sfTell( void *user_data );
static SF_VIRTUAL_IO sndFileIO = { sfGetFilelen, sfSeek, sfRead, sfWrite,
								  sfTell };

#define SFHNDL_A reinterpret_cast<SNDFILE*>(handleA)
#define SFHNDL_B reinterpret_cast<SF_INFO*>(handleB)
namespace MH33 {
namespace Audio {

/*
	void *handleA,*handleB;
	sIoDevice iodev;
*/

SoundFile::SoundFile(SoundFile &&mov)
	: handleA(mov.handleA), handleB(mov.handleB), iodev(std::move(mov.iodev))
{
	mov.handleA = nullptr;
	mov.handleB = nullptr;
}

SoundFile &SoundFile::operator=(SoundFile &&mov)
{
	if(handleA) {
		sf_close(SFHNDL_A);
	}
	this->handleA = mov.handleA;
	mov.handleA = nullptr;
	if(handleB) {
		free(handleB);
	}
	this->handleB = mov.handleB;
	mov.handleB = nullptr;
	this->iodev = std::move(mov.iodev);
	return *this;
}


SoundFile::~SoundFile()
{
	if(handleA) {
		sf_close(SFHNDL_A);
	}
	if(handleB) {
		free(handleB);
	}
}

SoundFile::SoundFile(const Io::sDevice &iodev)
	: handleA(nullptr), handleB(nullptr), iodev(iodev)
{
	if(!this->iodev) return;
	handleB = malloc(sizeof(SF_INFO));
	memset( handleB, 0, sizeof( SF_INFO ) );
	switch (iodev->getMode()) {
	case MH33::Io::Mode::READ: handleA = sf_open_virtual(&sndFileIO,SFM_READ,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_WRITE,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::READ_WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_RDWR,SFHNDL_B,iodev.get()); break;
	default: break;
	}
}

SoundFile::SoundFile(Io::sDevice &&iodev)
	: handleA(nullptr), handleB(nullptr), iodev(std::move(iodev))
{
	if(!this->iodev) return;
	handleB = malloc(sizeof(SF_INFO));
	memset( handleB, 0, sizeof( SF_INFO ) );
	switch (iodev->getMode()) {
	case MH33::Io::Mode::READ: handleA = sf_open_virtual(&sndFileIO,SFM_READ,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_WRITE,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::READ_WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_RDWR,SFHNDL_B,iodev.get()); break;
	default: break;
	}
}

SoundFile::SoundFile(Io::DeviceCreator iodev_creator, Io::Mode mode)
	: handleA(nullptr), handleB(nullptr), iodev(iodev_creator(mode))
{
	if(!this->iodev) return;
	handleB = malloc(sizeof(SF_INFO));
	memset( handleB, 0, sizeof( SF_INFO ) );
	switch (iodev->getMode()) {
	case MH33::Io::Mode::READ: handleA = sf_open_virtual(&sndFileIO,SFM_READ,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_WRITE,SFHNDL_B,iodev.get()); break;
	case MH33::Io::Mode::READ_WRITE: handleA = sf_open_virtual(&sndFileIO,SFM_RDWR,SFHNDL_B,iodev.get()); break;
	default: break;
	}
}
// IO
FrameIndex SoundFile::seekSet( FrameCount frames ) const {
	return FrameIndex(sf_seek(SFHNDL_A,frames.var,SEEK_SET));
}
FrameIndex SoundFile::seekCur( FrameCount frames ) const {
	return FrameIndex(sf_seek(SFHNDL_A,frames.var,SEEK_CUR));
}
FrameIndex SoundFile::seekEnd( FrameCount frames ) const {
	return FrameIndex(sf_seek(SFHNDL_A,frames.var,SEEK_END));
}
SampleCount SoundFile::read( short *ptr, SampleCount samples ) const {
	return SampleCount(sf_read_short(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::read( int *ptr, SampleCount samples ) const {
	return SampleCount(sf_read_int(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::read( float *ptr, SampleCount samples ) const {
	return SampleCount(sf_read_float(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::read( double *ptr, SampleCount samples ) const {
	return SampleCount(sf_read_double(SFHNDL_A,ptr,samples.var));
}
FrameCount SoundFile::readf( short *ptr, FrameCount frames ) const {
	return FrameCount(sf_readf_short(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::readf( int *ptr, FrameCount frames ) const {
	return FrameCount(sf_readf_int(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::readf( float *ptr, FrameCount frames ) const {
	return FrameCount(sf_readf_float(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::readf( double *ptr, FrameCount frames ) const {
	return FrameCount(sf_readf_double(SFHNDL_A,ptr,frames.var));
}
SampleCount SoundFile::write( short *ptr, SampleCount samples ) const {
	return SampleCount(sf_write_short(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::write( int *ptr, SampleCount samples ) const {
	return SampleCount(sf_write_int(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::write( float *ptr, SampleCount samples ) const {
	return SampleCount(sf_write_float(SFHNDL_A,ptr,samples.var));
}
SampleCount SoundFile::write( double *ptr, SampleCount samples ) const {
	return SampleCount(sf_write_double(SFHNDL_A,ptr,samples.var));
}
FrameCount SoundFile::writef( short *ptr, FrameCount frames ) const {
	return FrameCount(sf_writef_short(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::writef( int *ptr, FrameCount frames ) const {
	return FrameCount(sf_writef_int(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::writef( float *ptr, FrameCount frames ) const {
	return FrameCount(sf_writef_float(SFHNDL_A,ptr,frames.var));
}
FrameCount SoundFile::writef( double *ptr, FrameCount frames ) const {
	return FrameCount(sf_writef_double(SFHNDL_A,ptr,frames.var));
}
long SoundFile::read_raw( void *ptr, long bytes ) const {
	return sf_read_raw(SFHNDL_A,ptr,bytes);
}
long SoundFile::write_raw( void *ptr, long bytes ) const {
	return sf_write_raw(SFHNDL_A,ptr,bytes);
}
void SoundFile::write_sync( ) const {
	sf_write_sync(SFHNDL_A);
}

// Getters of non-text data
FrameCount SoundFile::getFrameNum( ) const {
	return FrameCount(SFHNDL_B->frames);
}
FrameRate SoundFile::getFrameRate( ) const {
	return FrameRate(SFHNDL_B->samplerate);
}
ChannelCount SoundFile::getChannels( ) const {
	return ChannelCount(SFHNDL_B->channels);
}
int SoundFile::getFormat( ) const {
	return SFHNDL_B->format;
}
int SoundFile::getSections( ) const {
	return SFHNDL_B->sections;
}
int SoundFile::getSeekable( ) const {
	return SFHNDL_B->seekable;
}

// Text getters
const char *SoundFile::getTitle( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_TITLE);
}
const char *SoundFile::getCopyright( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_COPYRIGHT);
}
const char *SoundFile::getSoftware( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_SOFTWARE);
}
const char *SoundFile::getArtist( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_ARTIST);
}
const char *SoundFile::getComment( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_COMMENT);
}
const char *SoundFile::getDate( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_DATE);
}
const char *SoundFile::getAlbum( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_ALBUM);
}
const char *SoundFile::getLicense( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_LICENSE);
}
const char *SoundFile::getTrackNumber( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_TRACKNUMBER);
}
const char *SoundFile::getGenre( ) const {
	return sf_get_string(SFHNDL_A, SF_STR_GENRE);
}

// Text getters - C string
int SoundFile::setTitle( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_TITLE, str);
}
int SoundFile::setCopyright( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_COPYRIGHT, str);
}
int SoundFile::setSoftware( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_SOFTWARE, str);
}
int SoundFile::setArtist( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_ARTIST, str);
}
int SoundFile::setComment( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_COMMENT, str);
}
int SoundFile::setDate( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_DATE, str);
}
int SoundFile::getAlbum( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_ALBUM, str);
}
int SoundFile::setTrackNumber( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_TRACKNUMBER, str);
}
int SoundFile::setLicense( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_LICENSE, str);
}
int SoundFile::setGenre( const char *str ) const {
	return sf_set_string(SFHNDL_A, SF_STR_GENRE, str);
}

// Text getters - C++ string
int SoundFile::setTitle( const std::string &str ) const {
	return setTitle(str.c_str());
}
int SoundFile::setCopyright( const std::string &str ) const {
	return setCopyright(str.c_str());
}
int SoundFile::setSoftware( const std::string &str ) const {
	return setSoftware(str.c_str());
}
int SoundFile::setArtist( const std::string &str ) const {
	return setArtist(str.c_str());
}
int SoundFile::setComment( const std::string &str ) const {
	return setComment(str.c_str());
}
int SoundFile::setDate( const std::string &str ) const {
	return setDate(str.c_str());
}
int SoundFile::getAlbum( const std::string &str ) const {
	return getAlbum(str.c_str());
}
int SoundFile::setTrackNumber( const std::string &str ) const {
	return setTrackNumber(str.c_str());
}
int SoundFile::setLicense( const std::string &str ) const {
	return setLicense(str.c_str());
}
int SoundFile::setGenre( const std::string &str ) const {
	return setGenre(str.c_str());
}

}
}
sf_count_t sfGetFilelen( void *user_data ) {
	return sf_count_t(
		reinterpret_cast< MH33::Io::Device* >( user_data )->size( ) );
}
sf_count_t sfSeek( sf_count_t offset, int whence, void *user_data ) {
	auto chandle = reinterpret_cast< MH33::Io::Device* >( user_data );
	bool cunt = false;
	switch ( whence ) {
	case SEEK_SET:
		cunt =
			sf_count_t( chandle->seek( MH33::Io::SeekOrigin::SET, offset ) );
		break;
	case SEEK_CUR:
		cunt =
			sf_count_t( chandle->seek( MH33::Io::SeekOrigin::CUR, offset ) );
		break;
	case SEEK_END:
		cunt =
			sf_count_t( chandle->seek(  MH33::Io::SeekOrigin::END, offset ) );
		break;
	default:
		cunt = false;
	}
	if ( cunt )
		return chandle->tell( );
	else
		return -1;
}
sf_count_t sfRead( void *ptr, sf_count_t count, void *user_data ) {
	return sf_count_t(
		reinterpret_cast< MH33::Io::Device* >( user_data )->read( ptr, count ) );
}
sf_count_t sfWrite( const void *ptr, sf_count_t count, void *user_data ) {
	return sf_count_t(
		reinterpret_cast< MH33::Io::Device* >( user_data )->write( ptr, count ) );
}
sf_count_t sfTell( void *user_data ) {
	return sf_count_t(
		reinterpret_cast< MH33::Io::Device* >( user_data )->tell( ) );
}
