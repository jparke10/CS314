#include <stdio.h>

void printBytes(unsigned char *start, int len) {
	for (int i = 0; i < len; ++i) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void printInt(int x) {
	printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
}

void printShort(short x) {
	printBytes((unsigned char *) &x, sizeof(short));
}

void printLong(long x) {
	printBytes((unsigned char *) &x, sizeof(long));
}

void printLongLong(long long x) {
	printBytes((unsigned char *) &x, sizeof(long long));
}

void printDouble(double x) {
	printBytes((unsigned char *) &x, sizeof(double));
}

int main() {
	// ival (12345) in hex = 0x3039
	int ival = 12345;
	printf("Testing printInt\n");
	// printInt prints ival as 39 30 00 00
	// as expected, little endian format
	// int is a 4-byte type, so prints 4 bytes 
	printInt(ival);
	printf("Testing printFloat\n");
	// 4 byte float ival in hex = 0x4640E400
	// printFloat prints ival as 00 e4 40 46
	// decimal form: 1.2345 * 10 ^ 4
	// binary: 0 10001100 1000000111001 ... (32bit)
	// in this case (signed pos), 46 represents the exponent
	// while the rest represent the mantissa
	printFloat((float) ival);
	printf("Testing printShort\n");
	// short is 2 bytes as expected
	// 3218 in hex = 0x0c92
	// prints short as 92 0c
	printShort(3218);
	long lval = 1021205356871490998;
	// lval in hex = 0xE2C0CDC8B0D1DB6
	printf("Testing printLong\n");
	// printLong prints as b6 1d 0d 8b dc 0c 2c 0e
	// on my 64-bit linux system, longs are 64-bit values
	printLong(lval);
	printf("Testing printLongLong\n");
	// unsurprisingly long long prints identical to long
	// they're both 64-bit values on my machine
	printLongLong((long long) lval);
	// example double: 0x413ECC2CC4B0BB9F
	// decimal value: 2.01834876832173 * 10 ^ 6
	// prints as 9f bb b0 c4 2c cc 3e 41
	// structured similar to float, but 8 bytes
	// 1 bit sign, 11 bit exponent, but mantissa gets 52 bits
	// 0 01010101011 010101010...
	printf("Testing printDouble\n");
	printDouble(2018348.76832173);
	return 0;
}
