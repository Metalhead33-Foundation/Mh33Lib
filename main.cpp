#include <QCoreApplication>
#include <iostream>
#include "Io/MhDataStream.hpp"
#include "Io/MhStderr.hpp"
#include "Io/MhFileIO.hpp"

typedef std::map<std::string,std::string> StringMap;
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
	MH33::FileIO file("/tmp/testfile.raw",MH33::IoMode::READ);
	loadAndPrintMap(file);
}
void testWrite() {
	MH33::FileIO file("/tmp/testfile.raw",MH33::IoMode::WRITE);
	saveMap(file);
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
