#include <stdio.h>
#define UI unsigned int

// replace takes unsigned int to partially replace, byte index to replace
// and byte to replace with
UI replace(UI x, int i, unsigned char b) {
	// declare mask of 1 byte, and empty int for writing byte b
	UI mask = 0xff;
	UI write = 0x0;
	// write byte b to unsigned int, for writing to x
	write |= b;
	// shift mask and write by i number of bytes (8 bits * i)
	mask <<= 8*i, write <<= 8*i;
	// use negation of mask to delete exclusively byte we are replacing
	// without negation, it would replace everything else
	x &= ~mask;
	// write byte b (as shifted unsigned int) to x
	x |= write;
	// return new value of x
	return x;
}

int main() {
	// test values from assignment paper
	UI x = 0x12345678; int i = 3; unsigned char b = 0xAB;
	// call replace function with test values
	UI val = replace(x, i, b);
	// print returned value in a nice looking form
	printf("First test case: %X\n", val);
	i = 0;
	val = replace(x, i, b);
	printf("Second test case: %X\n", val);
	return 0;
}
