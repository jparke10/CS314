#include <stdio.h>
#define UI unsigned int

UI extract (UI x, int i) {
	// mask out desired bit and bring to front (least significant)
	x = x >> 8*i & 0xFF;
	// convert unsigned x to signed, preparing for arithmetic shift
	// also bring x to most significant
	signed int ext = x << 24;
	// arithmetic shift right on signed var will sign extend
	return ext >> 24;
}

int main() {
	// test cases from 2-2
	printf("Test cases:\n");
	printf("0x12345678, 0 = %#X\n", extract(0x12345678, 0));
	printf("0xABCDEF00, 2 = %#X\n", extract(0xABCDEF00, 2));
	return 0;
}
