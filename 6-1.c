#include <stdio.h>

/*
int f(int a, int b, int c, int d, int n) {
	int result = 0;
	for (int i = 0; i < n; i += 2) {
		for (int j = 0; j < n; j += 2) {
			result += a * b + i * c * d + j;
		}
	}
	return result;
}
*/

int foptimized(int a, int b, int c, int d, int n) {
	int result = 0;
	// pre multiply constant parameters a,b,c,d 
	int ab = a*b;
	int cd = c*d;
	// set up for factoring in index
	int imul = 0;
	for (int i = 0; i < n; i += 2) {
		// add ab, imul, j, works bc i = 0 on first iteration
		// (so imul will be 0 as well, it's i*c*d)
		for (int j = 0; j < n; j += 2) {
			result += ab + imul + j;
		}
		// run this twice to create same effect as
		// 2*cd without multiplication
		// this will account for 2*i, 4*i, ..., n-1*i or whatever
		imul += cd;
		imul += cd;
	}
	return result;
}

int main() {
	printf("%d\n", foptimized(1, 2, 3, 4, 5));
	printf("%d\n", foptimized(2, 3, 4, 5, 6));
	printf("%d\n", foptimized(6, 5, 4, 3, 2));
	printf("%d\n", foptimized(5, 4, 3, 2, 1));
}
