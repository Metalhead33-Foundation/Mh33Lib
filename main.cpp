#include <QCoreApplication>
#include <iostream>
#include "Util/MhEndianness.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	int integers[4];
	for(auto& i : integers) {
		i = 6722624;
	}
	MH33::convert_endian<MH33::Endian::Native,MH33::Endian::Little>(integers[0]);
	MH33::convert_endian<MH33::Endian::Native,MH33::Endian::Big>(integers[1]);
	MH33::convert_endian<MH33::Endian::Little,MH33::Endian::Native>(integers[2]);
	MH33::convert_endian<MH33::Endian::Big,MH33::Endian::Native>(integers[3]);
	for(const auto& i : integers) {
		std::cout << i << std::endl;
	}
	return a.exec();
}
