#include <QCoreApplication>
#include <iostream>
#include "Io/MhDataStream.hpp"
#include "Io/MhStderr.hpp"

int main(int argc, char *argv[])
{
	const std::string errStr("This is just a small error string.\n");
	MH33::Stderr errorStream;
	MH33::DataStreamBE dataStream(errorStream);
	dataStream << errStr;
	return 0;
}
