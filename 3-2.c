// c file written on m2 processor (ARM assembler) 
// i don't expect anything to be different but just a disclaimer
#include <stdio.h>

/*
subq    %rsi, %rdx # z (dest) -= y (src);
imulq   %rdx, %rdi # x *= z;
salq    $63, %rdx  # z <<= 63;
sarq    $63, %rdx  # z >>= 63 (arithmetic right on signed num);
movq    %rdi, %rax # long result = x (declaration);
orq     %rdx, %rax # x |= z;
ret		   # return result;
*/

// implementation of "translated" lines above
long f(long x, long y, long z) {
	z -= y;
	x *= z;
	z <<= 63;
	z >>= 63;
	long result = x;
	x |= z;
	return result;
}

int main() {
	// test cases from 3-2 rubric
	printf("f(1, 2, 4): %li\n", f(1, 2, 4));
	printf("f(3, 5, 7): %li\n", f(3, 5, 7));
	printf("f(10, 20, 40): %li\n", f(10, 20, 40));
	printf("f(30, 50, 70): %li\n", f(30, 50, 70));
}
