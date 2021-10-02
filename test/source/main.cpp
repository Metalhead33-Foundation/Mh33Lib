#include <iostream>
#include <MhLib/Util/MhUUID.hpp>
#include <ctime>   // localtime
#include <iomanip> // put_time
#include <MhLib/Io/MhDataStream.hpp>
#include <MhLib/Io/MhBufferWrapper.hpp>
#include <MhLib/Io/MhZstdCompressor.hpp>
#include <MhLib/Io/MhZstdDecompressor.hpp>

using namespace std;

/*
	fromTimeAndRandom(std::chrono::duration_cast< std::chrono::milliseconds >(
						  std::chrono::system_clock::now().time_since_epoch()
						  ),rng.generate(),rng.generate());
*/

int main()
{
	const std::string str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n"
"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n"
"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.\n"
"Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium,\n"
"totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo.\n"
"Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit,\n"
"sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.\n"
"Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit,\n"
"sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.\n"
"Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur?\n"
"Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";
	std::cout << "Original data size: " << str.size() + sizeof(uint32_t) << std::endl;
	MH33::Io::BufferWrapper buff;
	MH33::Io::ZstdCompressor compressor(&buff);
	MH33::Io::DataStreamBE inStream(compressor);
	compressor.setCompressionLevel(0.9f);
	inStream << str;
	inStream << str;
	if(!compressor.flush()) {
		std::cout << "Flush failed!" << std::endl;
		return 0;
	}
	std::cout << "Compressed data size: " << buff.size() << std::endl;
	buff.seek(MH33::Io::SeekOrigin::SET,0);
	MH33::Io::ZstdDecompressor decompressor(&buff);
	/*std::string outStr(256,0);
	decompressor.read(&outStr[0],255);
	std::cout << outStr << std::endl;*/
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
		} else std::cout << "The two strings differ at the position " << i << "." << std::endl;
	}
	/*MH33::Util::RNG rng;
	MH33::Util::UUID uuid(rng,true);
	uint32_t rand1,rand2;
	std::chrono::milliseconds milisec;
	uuid.toTimeAndRandom(milisec,rand1,rand2);
	auto chron = std::chrono::duration_cast<std::chrono::system_clock::duration>(milisec);
	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::time_point<std::chrono::system_clock>(chron) );
	cout << "Hello World! This is an UUID: " << uuid.toString() << endl;
	cout << "Date: " << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << endl;
	cout << "Random 1: " << rand1 << endl;
	cout << "Random 2: " << rand2 << endl;*/
	return 0;
}
