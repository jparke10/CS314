#include <stdio.h>
#define N 4
typedef long array_t[N][N];

/*
.L3:
	movq    (%rax), %rcx // set t1 equal to the memory address of a[i], or a[i][0]
	movq    (%rdx), %rsi // set t2 equal to the memory address of a[j], or a[j][0]
	movq    %rsi, (%rax) // set the a[i][0] address equal to t2
	movq    %rcx, (%rdx) // set a[j][0] address equal to t1
			     // a[i][0] is now equal to what a[j][0] was and vice versa
			     // after each iteration of the loop, these will be adjusted by 1 byte and 4 bytes respectively
	addq    $8, %rax // add 8 to the memory address representing a[i][j], shifting it up by 1 byte (lower index)
			 // e.g. a[i][0] becomes a[i][1]
	addq    $32, %rdx // add 32 to the memory address representing a[j][i], shifting it up by 4 bytes (1 upper index)
			  // e.g. a[0][j] becomes a[1][j]
	cmpq    %r9, %rax // if j is not equal to i
	jne     .L3	  // jump back to L3
*/

void transpose(array_t a) {
	for (long i = 0; i < N; ++i) {
		for (long j = 0; j < i; ++j) {
			long t1 = a[i][j];
			long t2 = a[j][i];
			a[i][j] = t2;
			a[j][i] = t1;
		}
	}
}

void transposeOpt(array_t a) {
	for (long i = 0; i < N; ++i) {
		long *rp = &a[i][0];
		long *cp = &a[0][i];
		for (long j = 0; j < i; ++j) {
			// perform swap, essentially movq commands of .L3
			long temp = *rp;
			*rp = *cp;
			*cp = temp;
			// add to pointers, essentially addq commands of .L3
			rp += 1;
			cp += 4;
		}
	}
}

// helper print command for testing, it's ugly but it works
void printArrays(array_t a) {
	printf("{");
	for (int i = 0; i < N; i++) {
		printf("{");
		for (int j = 0; j < N; j++) {
			printf("%li, ", a[i][j]);
		}
		printf("}, ");
	}
	printf("}\n");
}

int main() {
	array_t a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	printArrays(a);
	// transpose(a);
	transposeOpt(a);
	printArrays(a);
}
