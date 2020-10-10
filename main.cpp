#include <QCoreApplication>
#include <iostream>
#include "Io/MhDataStream.hpp"
#include "Io/MhStderr.hpp"
#include "Io/MhBufferWrapper.hpp"

typedef std::map<std::string,std::string> StringMap;
static MH33::BufferWrapper buff;
void testRead();
void testWrite();
void saveMap(MH33::IoDevice& iodev);
void loadAndPrintMap(MH33::IoDevice& iodev);

int main(int argc, char *argv[])
{
	testWrite();
	testRead();
	return 0;
}

void testRead() {
	buff.seek(MH33::SeekOrigin::SET,0);
	loadAndPrintMap(buff);
}
void testWrite() {
	buff.seek(MH33::SeekOrigin::SET,0);
	saveMap(buff);
}

void saveMap(MH33::IoDevice& iodev) {
	StringMap map;
	map.emplace("Random key 1", "Random value 1");
	map.emplace("Random key 2", "Random value 2");
	map.emplace("Random key 3", "Random value 3");
	MH33::DataStreamBE stream(iodev);
	stream << map;
}

void loadAndPrintMap(MH33::IoDevice& iodev) {
	StringMap map;
	MH33::DataStreamBE stream(iodev);
	stream >> map;
	for(auto it = std::begin(map); it != std::end(map); ++it) {
		std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
	}
}
