#include <stdio.h>

unsigned int getOffset(unsigned int address) {
	// least significant digit
	return address & 0xF;
}

unsigned int getSet(unsigned int address) {
	// 2nd and 3rd least significant digits
	return (address >> 4) & 0xFF;
}

unsigned int getTag(unsigned int address) {
	// 5 most significant digits
	return (address >> 12) & 0xFFFFF;
}

int main() {
	printf("0x12345678: offset: %x - tag: %x - set: %x\n", getOffset(0x12345678), getTag(0x12345678), getSet(0x12345678));
	printf("0x87654321: offset: %x - tag: %x - set: %x\n", getOffset(0x87654321), getTag(0x87654321), getSet(0x87654321));
}
