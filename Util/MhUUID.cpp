#include "MhUUID.hpp"
#include <cstring>
#include <sstream>
namespace MH33 {


constexpr uint8_t charToHex(char upper, char lower) {
	uint8_t num = 0;
	switch (upper) {
	case '0': num |= 0x00; break;
	case '1': num |= 0x10; break;
	case '2': num |= 0x20; break;
	case '3': num |= 0x30; break;
	case '4': num |= 0x40; break;
	case '5': num |= 0x50; break;
	case '6': num |= 0x60; break;
	case '7': num |= 0x70; break;
	case '8': num |= 0x80; break;
	case '9': num |= 0x90; break;
	case 'a': num |= 0xA0; break;
	case 'b': num |= 0xB0; break;
	case 'c': num |= 0xC0; break;
	case 'd': num |= 0xD0; break;
	case 'e': num |= 0xE0; break;
	case 'f': num |= 0xF0; break;
	case 'A': num |= 0xA0; break;
	case 'B': num |= 0xB0; break;
	case 'C': num |= 0xC0; break;
	case 'D': num |= 0xD0; break;
	case 'E': num |= 0xE0; break;
	case 'F': num |= 0xF0; break;
	default: break;
	}
	switch (lower) {
	case '0': num |= 0x00; break;
	case '1': num |= 0x01; break;
	case '2': num |= 0x02; break;
	case '3': num |= 0x03; break;
	case '4': num |= 0x04; break;
	case '5': num |= 0x05; break;
	case '6': num |= 0x06; break;
	case '7': num |= 0x07; break;
	case '8': num |= 0x08; break;
	case '9': num |= 0x09; break;
	case 'a': num |= 0x0A; break;
	case 'b': num |= 0x0B; break;
	case 'c': num |= 0x0C; break;
	case 'd': num |= 0x0D; break;
	case 'e': num |= 0x0E; break;
	case 'f': num |= 0x0F; break;
	case 'A': num |= 0x0A; break;
	case 'B': num |= 0x0B; break;
	case 'C': num |= 0x0C; break;
	case 'D': num |= 0x0D; break;
	case 'E': num |= 0x0E; break;
	case 'F': num |= 0x0F; break;
	default: break;
	}
	return num;
}
constexpr char hexToStr(uint8_t num) {
	switch (num & 0x0F) {
	case 0x00: return '0';
	case 0x01: return '1';
	case 0x02: return '2';
	case 0x03: return '3';
	case 0x04: return '4';
	case 0x05: return '5';
	case 0x06: return '6';
	case 0x07: return '7';
	case 0x08: return '8';
	case 0x09: return '9';
	case 0x0A: return 'a';
	case 0x0B: return 'b';
	case 0x0C: return 'c';
	case 0x0D: return 'd';
	case 0x0E: return 'e';
	case 0x0F: return 'f';
	default: return '0';
	}
}
void numToHex(std::stringstream& stream, uint8_t num) {
	stream << hexToStr( (num & 0xF0) >> 4);
	stream << hexToStr(num & 0x0F);
}

UUID::UUID()
{
	memset(__uuid,0,size);
}

UUID::UUID(const UUID &cpy)
{
	memcpy(this->__uuid,cpy.__uuid,size);
}

UUID &UUID::operator=(const UUID &cpy)
{
	memcpy(this->__uuid,cpy.__uuid,size);
	return *this;
}

UUID::UUID(const Buffer &cpy)
{
	memcpy(this->__uuid,cpy.data(),std::min(size,cpy.size()));
}

UUID &UUID::operator=(const Buffer &cpy)
{
	memcpy(this->__uuid,cpy.data(),std::min(size,cpy.size()));
	return *this;
}

std::string UUID::toString(bool curlyBraces) const
{
	std::stringstream stream;
	uint8_t ctr=0;
	if(curlyBraces) stream << '{';
	for(uint8_t a = 0; a < 4; ++a) {
		numToHex(stream,__uuid[ctr++]);
	}
	stream << '-';
	for(uint8_t a = 0; a < 2; ++a) {
		numToHex(stream,__uuid[ctr++]);
	}
	stream << '-';
	for(uint8_t a = 0; a < 2; ++a) {
		numToHex(stream,__uuid[ctr++]);
	}
	stream << '-';
	for(uint8_t a = 0; a < 2; ++a) {
		numToHex(stream,__uuid[ctr++]);
	}
	stream << '-';
	for(uint8_t a = 0; a < 6; ++a) {
		numToHex(stream,__uuid[ctr++]);
	}
	if(curlyBraces) stream << '}';
	return stream.str();
}

UUID &UUID::operator=(const std::string &string)
{
	if(string.empty()) return *this;
	const bool curlyBraces = string[0] == '{';
	if(string.size() < (36+curlyBraces)) return *this;
	uint8_t offset = curlyBraces;
	__uuid[0] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[1] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[2] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[3] = charToHex(string[offset],string[offset+1]); offset += 2;
	++offset; // Skip one character
	__uuid[4] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[5] = charToHex(string[offset],string[offset+1]); offset += 2;
	++offset; // Skip one character
	__uuid[6] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[7] = charToHex(string[offset],string[offset+1]); offset += 2;
	++offset; // Skip one character
	__uuid[8] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[9] = charToHex(string[offset],string[offset+1]); offset += 2;
	++offset; // Skip one character
	__uuid[10] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[11] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[12] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[13] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[14] = charToHex(string[offset],string[offset+1]); offset += 2;
	__uuid[15] = charToHex(string[offset],string[offset+1]);
	// xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx
	return *this;
}

UUID::UUID(const std::string &string)
{
	memset(__uuid,0,size);
	*this = string;
}


}
