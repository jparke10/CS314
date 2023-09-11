#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float f(float *a, int n) {
	float prod = 1.0f;
	for (int i = 0; i < n; ++i) {
		if (a[i] != 0.0f) {
			prod *= a[i];
		}
	}
	return prod;
}

float g(float *b, int n) {
	float prod = 1.0f;
	for (int i = 0; i < n; ++i) {
		prod *= b[i];
	}
	return prod;
}

float* createArray(int size) {
	float *a = (float *)malloc(size * sizeof(float));
	for (int i = 0; i < size; ++i) {
		// 50% chance that a[i] is 0.0f, random value on the range
		// [0.76, 1.26] otherwise.
		float r = rand() / (float)RAND_MAX;
		a[i] = r < 0.5f ? 0.0f : r + 0.26f;
	}
	return a;
}

int main() {
	float *a = createArray(10000);
	clock_t start = clock();
	float fa = f(a, 10000);
	clock_t end = clock();
	double fa_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("f(a): %lf, time: %lf\n", fa, fa_time); // timing around 0.000037
	// allocate new 10k array and copy across
	// replacing 0.0f with 1.0f where needed
	float *b = (float *)malloc(sizeof(float) * 10000);
	for (int i = 0; i < 10000; i++) {
		if (a[i] == 0.0f)
			b[i] = 1.0f;
		else
			b[i] = a[i];
	}
	start = clock();
	float gb = g(b, 10000);
	end = clock();
	double gb_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("g(b): %lf, time: %lf\n", gb, gb_time); // timing around 0.000024
	// faster since we don't need to do any conditionals or lookups
	// find count of nonzero elements in array a for c's declaration
	int length = 0;
	for (int i = 0; i < 10000; i++)
		if (a[i] != 0)
			length++;
	float *c = (float *)malloc(sizeof(float) * length);
	// index of nonzero elements
	int index = 0;
	// fill array c with a's nonzero elements
	for (int i = 0; i < 10000; i++)
		if (a[i] != 0) {
			c[index] = a[i];
			index++;
		}
	start = clock();
	float gc = g(c, length);
	end = clock();
	double gc_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("g(c): %lf, time: %lf\n", gc, gc_time); // timing around 0.000013
	// faster since we eliminate all checks if the value at the index is
	// equal to zero
	free(a);
	free(b);
	free(c);
}
