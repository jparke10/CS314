#include <stdio.h>

int ge(float x, float y) {
	unsigned int ux = *((unsigned int*) &x); // convert x raw bits
	unsigned int uy = *((unsigned int*) &y); // convert y raw bits
	unsigned int sx = ux >> 31; // extract sign bit of ux
	unsigned int sy = uy >> 31; // extract sign bit of uy
	ux <<= 1; // drop sign bit of ux
	uy <<= 1; // drop sign bit of uy
	// TODO: return using sx, sy, ux, uy
	       // if x and y are both positive, and unsigned x >= y
	return (sx == 0 && sy == 0 && ux >= uy) ||
	       // if x and y are both negative, and unsigned y >= x
	       // (backwards because a smaller unsigned value is bigger on negative plane)
	       (sx == 1 && sy == 1 && ux <= uy) ||
	       // if x is positive and y is negative, always >= so all we gotta check
	       (sx == 0 && sy == 1) ||
	       // if x is negative and y is positive, only possible case is 0
	       (sx == 1 && sy == 0 && ux == 0 && uy == 0);
}

int main() {
	// test cases from assignment paper
	printf(" 0.0f,  0.0f: %d\n", ge(0.0f, 0.0f));
	printf("-0.0f,  0.0f: %d\n", ge(-0.0f, 0.0f));
	printf(" 0.0f, -0.0f: %d\n", ge(0.0f, -0.0f));
	printf("-0.0f, -0.0f: %d\n", ge(-0.0f, -0.0f));
	printf(" 1.0f,  1.0f: %d\n", ge(1.0f, 1.0f));
	printf("-1.0f,  1.0f: %d\n", ge(-1.0f, 1.0f));
	printf(" 1.0f, -1.0f: %d\n", ge(1.0f, -1.0f));
	printf("-1.0f, -1.0f: %d\n", ge(-1.0f, -1.0f));
	printf("-1.0f,  0.0f: %d\n", ge(-1.0f, 0.0f));
	printf(" 0.0f, -1.0f: %d\n", ge(0.0f, -1.0f));
	printf(" 1.0f,  0.0f: %d\n", ge(1.0f, 0.0f));
	printf(" 0.0f,  1.0f: %d\n", ge(0.0f, 1.0f));
	printf(" 1.0f,  2.0f: %d\n", ge(1.0f, 2.0f));
	printf(" 2.0f,  1.0f: %d\n", ge(2.0f, 1.0f));
	printf("-1.0f, -2.0f: %d\n", ge(-1.0f, -2.0f));
	printf("-2.0f, -1.0f: %d\n", ge(-2.0f, -1.0f));
	return 0;
}
