#include <stdio.h>
#define UI unsigned int

int evenBit(unsigned int x) {
	// 0x55555555 is the mask of 0101 0101 .... 0101
	// aka all the even numbered bits of a 32-bit word
	// !! operator essentially will return 1 if,
	// after being masked, x does not contain all 0's
	// if x does contain all 0's, it returns 0
	return !!(x &= 0x55555555);
	
}

int main() {
	// print all the test cases, pretty ugly tbh
	printf("Test case of 0x1: %d\n", evenBit(0x1));
	printf("Test case of 0x2: %d\n", evenBit(0x2));
	printf("Test case of 0x3: %d\n", evenBit(0x3));
	printf("Test case of 0x4: %d\n", evenBit(0x4));
	printf("Test case of 0xffffffff: %d\n", evenBit(0xffffffff));
	printf("Test case of 0xaaaaaaaa: %d\n", evenBit(0xaaaaaaaa));
	printf("Test case of 0x55555555: %d\n", evenBit(0x55555555));
}
