#include <stdio.h>
#define UI unsigned int

// combine takes 2 unsigned ints as params
UI combine(UI x, UI y) {
	// first bit mask isolates byte 3 of x
	// example: 0xABCDEF00 -> 0xAB000000
	x &= 0xff000000;
	// second bit mask isolates bytes 0-2 of y
	// example: 0x12345678 -> 0x00345678
	y &= 0x00ffffff;
	// bitwise or writes y to x, appending bytes 0-2
	// to byte 3
	x |= y;
	// returns unsigned int
	return x;
}

int main() {
	// test values from assignment 1 worksheet
	UI x = 0x12345678;
	UI y = 0xABCDEF00;
	// call helper function
	UI test = combine(x, y);
	// prints explanation
	printf("Value returned by combine function: %X\n", test);
	x = 0xABCDEF00;
	y = 0x12345678;
	test = combine(x, y);
	printf("Value returned by combine function: %X\n", test);
	return 0;
}
