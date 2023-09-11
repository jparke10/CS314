#include <stdio.h>

void inner(float *u, float *v, int length, float *dest) {
	float sum = 0.0f;
	for (int i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
}

void inner2(float *u, float *v, int length, float *dest) {
	// i is used across both loops, declare outside
	int i;
	float sum = 0.0f;
	// stop being length - 3 gives us 4 metaphorical lanes
	// to work with, [i] [i+1] [i+2] [i+3]
	int stop = length - 3;
	for (i = 0; i < stop; i += 4) {
		// utilize all 4 lanes to add to sum 4x in 1 loop iteration
		sum += u[i] * v[i];
		sum += u[i+1] * v[i+1];
		sum += u[i+2] * v[i+2];
		sum += u[i+3] * v[i+3];
	}
	// mop up remaining indexes between the initial limit
	// and the actual length, we can only do these individually
	// gcc seems to think i isn't being declared (warning) but
	// it compiles and runs fine soooo???
	for (i; i < length; i++)
		sum += u[i] * v[i];
	// send to destination int
	*dest = sum;
}

int main() {
	float arr1[5] = {1, 2, 3, 4, 5};
	float arr2[5] = {6, 7, 8, 9, 10};
	float d1, d2;
	int length = 5;
	inner(arr1, arr2, length, &d1);
	inner2(arr1, arr2, length, &d2);
	printf("Rolled loop: %f\n", d1);
	printf("Unrolled loop: %f\n", d2);
}

