#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 2

struct Set {
    unsigned char data[BLOCK_SIZE];
    unsigned int tag; // Assume tag is at most 32 bits 
    unsigned char valid; // valid bit (0 or 1)
};

struct Cache {
    struct Set *sets;
    int numSets;
};

unsigned int getOffset(unsigned int address) {
	// TODO – return unsigned-int value of offset bits from address
	return address & 0x1; // 1 offset bit for every 2B block, so 1 bit
} 

unsigned int getSet(unsigned int address) {
	// TODO – return unsigned-int value of set bits from address
	return (address >> 1) & 0x7; // 16B cache / 2B blocks = 8 sets
				     // 2^3 = 8, so 3 set bits
}

unsigned int getTag(unsigned int address) {
	// TODO – return unsigned-int value of tag bits from address
	return (address >> 4); // remainder of 8-bit address goes to tag
}

struct Cache* mallocCache(int numSets) {
	// TODO - malloc a pointer to a struct Cache, malloc a pointer to an array
	// of struct Set instances (array length is numSets). Also initialize
	// valid to 0 for each struct Set. Return the struct Cache pointer.
	struct Cache *cache = (struct Cache*)malloc(sizeof(struct Cache));
	cache->numSets = numSets;
	struct Set *sets = (struct Set*)malloc(sizeof(struct Set)*numSets);
	cache->sets = sets;
	for (int i = 0; i < numSets; i++)
		cache->sets[i].valid = 0;
	return cache;
}

void freeCache(struct Cache *cache) {
	free(cache->sets);
	free(cache);
}

void printSet(struct Set *set, int setIndex) {
	printf("set: %x - tag: %x - valid: %u - data:", setIndex, set->tag, set->valid);
	unsigned char *data = set->data;
	for (int i = 0; i < BLOCK_SIZE; ++i) {
		printf(" %.2x", data[i]);
	}
    	printf("\n");
}

void printCache(struct Cache *cache) {
	// TODO - print all valid sets in the cache.
	for (int i = 0; i < cache->numSets; i++) {
		struct Set *set = &cache->sets[i];
		if (set->valid)
			printSet(set, i);
	}
}

void readValue(struct Cache *cache, unsigned int address) {
	// TODO - check the cache for a cached byte at the specified address.
	// If found, indicate a hit and print the byte. If not found, indicate
	// a miss due to either an invalid line (cold miss) or a tag mismatch
	// (conflict miss).
	unsigned int s = getSet(address);
	unsigned int t = getTag(address);

	struct Set *set = &cache->sets[s];
	if(set->valid && set->tag == t) {
		unsigned char *data = set->data;
		printf("Set read: ");
		printSet(set, s);
		printf("Hit\n");
	} else
		printf("Cold miss - line not found\n");

}

void writeValue(struct Cache *cache, unsigned int address, unsigned char *newData) {
	unsigned int s = getSet(address);
	unsigned int t = getTag(address);

	struct Set *set = &cache->sets[s];
	if (set->valid && set->tag != t) {
		unsigned char *data = set->data;
		printf("evicting line - ");
		printSet(set, s);
	}

	unsigned char *data = set->data;
	for (int i = 0; i < BLOCK_SIZE; ++i) {
		data[i] = newData[i];
	}

	set->tag = t;
	set->valid = 1;

	printf("wrote set: ");
	printSet(set, s);
}

unsigned int readUnsignedIntFromHex() {
	char buffer[10];
	char *p = NULL;
	unsigned int n;
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		n = strtoul(buffer, &p, 16);
		if (buffer != p) {
			break;
		}
		printf("Invalid input - try again: ");
	}
	return n;
}

int main() {
	struct Cache *cache = mallocCache(8);

	char buffer[10];
	char c;
	do {
		printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: ");
		fgets(buffer, sizeof(buffer), stdin);

		c = buffer[0];
		if (c == 'r') {
			printf("Enter 32-bit unsigned hex address: ");
			unsigned int a = readUnsignedIntFromHex();
			readValue(cache, a);
		} else if (c == 'w') {
			printf("Enter 32-bit unsigned hex address: ");
			unsigned int a = readUnsignedIntFromHex();

			printf("Enter 32-bit unsigned hex value: ");
			unsigned int v = readUnsignedIntFromHex();
			unsigned char *data = (unsigned char *)&v;
			writeValue(cache, a, data);
		} else if (c == 'p') {
			printCache(cache);
        	}
	} while (c != 'q');

	freeCache(cache);
}
