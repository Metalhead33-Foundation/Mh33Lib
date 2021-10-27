#include <iostream>
#include <MhLib/Util/MhUUID.hpp>
#include <ctime>   // localtime
#include <iomanip> // put_time
#include <MhLib/Io/MhDataStream.hpp>
#include <MhLib/Io/MhBufferWrapper.hpp>
#include <MhLib/Io/MhZstdCompressor.hpp>
#include <MhLib/Io/MhZstdDecompressor.hpp>
#include <MhLib/Io/MhSnappyCompressor.hpp>
#include <MhLib/Io/MhSnappyDecompressor.hpp>
#include <MhLib/Io/MhFile.hpp>
#include <MhLib/Gimmick/MhWordGenerator.hpp>
#include <sstream>
#include <fstream>

using namespace std;

/*
	fromTimeAndRandom(std::chrono::duration_cast< std::chrono::milliseconds >(
						  std::chrono::system_clock::now().time_since_epoch()
						  ),rng.generate(),rng.generate());
*/

//#define USE_ZSTD
#ifdef USE_ZSTD
typedef MH33::Io::ZstdCompressor Compressor;
typedef MH33::Io::ZstdDecompressor Decompressor;
#else
typedef MH33::Io::SnappyCompressor Compressor;
typedef MH33::Io::SnappyDecompressor Decompressor;
#endif

int main()
{
	MH33::Io::BufferWrapper buff;
	std::map<std::string,uint32_t> elementmap;
	MH33::Gimmick::WordGenerator wordGen;
	MH33::Util::RNG rng(0x555);
	for(int i = 0; i < 0xF; ++i) {
		elementmap.emplace(wordGen.generate(10,10),rng.generate());
	}
	MH33::Io::DataStreamBE(buff) << elementmap;
	buff.seek(MH33::Io::SeekOrigin::SET,0);
	std::map<std::string,uint32_t> elementmap2;
	MH33::Io::DataStreamBE(buff) >> elementmap2;
	for(auto it = std::begin(elementmap); it != std::end(elementmap) ; ++it ) {
		std::cout << it->first << ':' << it->second << std::endl;
	}
	std::cout << '\n';
	for(auto it = std::begin(elementmap2); it != std::end(elementmap2) ; ++it ) {
		std::cout << it->first << ':' << it->second << std::endl;
	}

	/*std::stringstream stringStream;
	MH33::Gimmick::WordGenerator wordGen;
	for(int i = 0; i < 0x2FFF; ++i) {
		stringStream << wordGen.generate(10,10) << "\n";
	}
	const std::string str = stringStream.str();
	std::cout << "Original data size: " << str.size() + sizeof(uint32_t) << std::endl;
	MH33::Io::BufferWrapper buff;
	Compressor compressor(&buff);
	MH33::Io::DataStreamBE inStream(compressor);
	inStream << str;
	if(!compressor.flush()) {
		std::cout << "Flush failed!" << std::endl;
		return 0;
	}
	std::cout << "Compressed data size: " << buff.size() << std::endl;
	buff.seek(MH33::Io::SeekOrigin::SET,0);
	Decompressor decompressor(&buff);
	MH33::Io::DataStreamBE outStream(decompressor);
	std::string outputString = "";
	outStream >> outputString;
	if(str.size() != outputString.size()) {
		std::cout << "The two strings are of a different size! Decompression failed!" << std::endl;
		std::cout << "Original string size: " << str.size() << std::endl;
		std::cout << "Decompressed string size: " << outputString.size() << std::endl;
	} else {
		bool identical = true;
		size_t i = 0;
		for(; i < str.size(); ++i) {
			identical = str[i] == outputString[i];
			if(!identical) break;
		}
		if(identical) {
			std::cout << "The two strings are identical. Decompression succesful." << std::endl;
		} else {
			std::cout << "The two strings differ at the position " << i << "." << std::endl;
			std::cout << "Original: " << std::string( &str[std::max(i-2,size_t(0))], std::min(size_t(72),str.size()-i) ) << std::endl;
			std::cout << "Decompressed: " << std::string( &outputString[std::max(i-2,size_t(0))], std::min(size_t(72),outputString.size()-i) ) << std::endl;
		}
	}*/
	return 0;
}
