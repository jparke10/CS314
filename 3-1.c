// stdlib required for malloc
#include <stdio.h>
#include <stdlib.h>

// standard datatypes specified for 3-1
struct IntArray {
	int length;
	int *dataPtr;
};

struct IntArray* mallocIntArray(int length) {
	// declare intarray pointer for return
	struct IntArray *arr;
	// dynamically allocate intarray size
	arr = malloc(sizeof(struct IntArray));
	// fill length with input length
	arr->length = length;
	// fill dataptr with dynamically allocated length amount of int's
	arr->dataPtr = malloc(sizeof(int) * length);
	// return intarray pointer, newly allocated
	return arr;
}

void freeIntArray(struct IntArray *arrayPtr) {
	// fairly unambiguous
	free(arrayPtr->dataPtr);
	free(arrayPtr);
}

void readIntArray(struct IntArray *array) {
	// readint routine sourced from Lab 4 demonstration / starter code
	// written by Brad Bailey
	char lineBuf[10];
	char *p = NULL;
	int n;
	// have to fill the dynamically allocated array so we use for loop
	for (int i = 0; i < array->length; i++) {
		printf("Enter int: ");
		while (1) {
			fgets(lineBuf, sizeof(lineBuf), stdin);
			n = strtol(lineBuf, &p, 10);
			// if linebuf is not a string AND strtol finds positive #
			// then we append to dataPtr
			if (lineBuf != p && n >= 0) {
				array->dataPtr[i] = n;
				break;
			}
			printf("Invalid input\n");
		}
	}
}

// bubble sort routine sourced from
// https://www.programiz.com/dsa/bubble-sort
// swap routine written based on bubble sort algorithm

void swap(int *xp, int *yp) {
	int scratch = *xp;
	*xp = *yp;
	*yp = scratch;
}

// sortIntArray sourced routine from above linked site

void sortIntArray(struct IntArray *array) {
	for (int i = 0; i < array->length - 1; i++)
		for (int j = 0; j < array->length - i - 1; j++)
			if (array->dataPtr[j] > array->dataPtr[j + 1])
				swap(&array->dataPtr[j], &array->dataPtr[j + 1]);
}

// print opening bracket, print all indexes of dataPtr in order
// special case for last one, since we need the closing bracket
// and it can just be hardcoded since length is determined from stdin

void printIntArray(struct IntArray *array) {
	printf("[ ");
	for (int i = 0; i < array->length - 1; i++)
		printf("%d, ", array->dataPtr[i]);
	printf("%d ]\n", array->dataPtr[array->length - 1]);
}

int main() {
	// uses same getint routine as above
	// probably could have written a function for this
	char lineBuf[10];
	char *p = NULL;
	int n;
	printf("Enter length: ");
	while (1) {
		fgets(lineBuf, sizeof(lineBuf), stdin);
		n = strtol(lineBuf, &p, 10);
		if (lineBuf != p && n >= 0)
			break;
		printf("Invalid input\n");
	}
	// based on rubric, call all these functions in order
	struct IntArray *array = mallocIntArray(n);
	readIntArray(array);
	sortIntArray(array);
	printIntArray(array);
	freeIntArray(array);
	return 0;
}
