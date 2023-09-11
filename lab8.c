#include <stdio.h>
#include <math.h>

// use log2() and COMPILE WITH -lm !!!
void printTSO(int blockSizeInBytes, int numSets, int archSizeInBits) {

	// how many things can we count with X bits?
	// how many addresses are possible with a 32b pointer?
	// 2^X
	// eg. for 2b pointer, we could only have mem locations 00, 01, 10, 11
	// if we have X things, how many bits do we need to count them?
	// log2(X)
	
	// need to count/keep track of: set, block, offset
	
	int setBits = log2(numSets);

	int offsetBits = log2(blockSizeInBytes);

	// tag/block is whatever is left over
	
	int tagBits = archSizeInBits - setBits - offsetBits;

	if (tagBits < 0) printf("Error: cache policy not possible with current architecture.\n");

        printf("%dB blocks, %d sets, %d-bit architecture: %d tag bits, %d set bits, %d offset bits.\n",
                        blockSizeInBytes, numSets, archSizeInBits, tagBits, setBits, offsetBits);
}

// what does a pointer point to?
// an address / location in memory (correct, but)
// what is a location in memory?
// RAM is a 1 dimensional array of bytes
// pointer is an index into this array
// a single byte

// int temp = 0;
// int *p = &temp;
// just say that p = 0x00000012
// p points to the start of temp
// C is type aware: knows how to read next 4 bytes starting at p
// think asm lea

// LAB 8: 256B block, 1 set, 32 bit arch
// <TAG><SET><OFFSET>
unsigned int getOffset(unsigned int address) {
        // 8 OFFSET BITS (lowest sig)
	return address & 0xFF;
}

unsigned int getTag(unsigned int address) {
	// 24 highest bits
        // return address & 0xFFFFFF00;
	return address >> 8;
}

int main() {
        printTSO(256, 1, 32);
        unsigned int testAddr1 = 0x12345678;
        unsigned int testAddr2 = 0x87654321;
        // uncomment after implementing
        printf("0x%08x: offset - %x, tag - %x.\n", testAddr1, getOffset(testAddr1), getTag(testAddr1));
        printf("0x%08x: offset - %x, tag - %x.\n", testAddr2, getOffset(testAddr2), getTag(testAddr2));
}

// access 0x12345678
// read in 0x12345600 through 0x123456FF
// offset is like a "mini pointer" into cache block

// now say we access 0x87654321
// check the tag against cache
// does cach have 0x876543? no, it has 0x123456
// implement some replacement policy (evict current block)
// replace with 0x87654300 through 0x876543FF (roughly)
