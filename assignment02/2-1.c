#include <stdio.h>
#define UI unsigned int

UI mask(int n) {
	// shifting by n, from 1, to start 1 bit up from the # of bits we want
	// e.g. 1 << 7 = 10000000
	// then, subtracting 1 will give us all binary 1's of the # of bits we want
	// e.g. 10000000 - 1 = 01111111
	// thus forms our mask
	return (1 << n) - 1;
}

int main() {
	// test cases from assignment sheet
	printf("Test cases:\n");
	printf(" 1: %#X\n", mask(1));
	printf(" 2: %#X\n", mask(2));
	printf(" 3: %#X\n", mask(3));
	printf(" 5: %#X\n", mask(5));
	printf(" 8: %#X\n", mask(8));
	printf("16: %#X\n", mask(16));
	printf("31: %#X\n", mask(31));
	return 0;
}
