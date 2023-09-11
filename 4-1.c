#include <stdio.h>

/* PART A: goto implementation of "long sum" function
long sum(long from, long to) {
	long result = 0;
// writing true label before conditional forms the "do" part of "do while"
true:
{
	result += from;
	++from;
}
// conditional will re-run code while from <= to, as specified
	if (from <= to) goto true;
	return result;
}
*/

// disclaimer: I have an M2 Mac so I can't compile these with gcc, used gdbonline
long sum(long from, long to) {
	// Declare and initialize result var – *do not modify*.
	long result = 0;

	// Ensure that argument *from* is in %rdi,
	// argument *to* is in %rsi, *result* is in %rax - *do not
	// modify*.
	__asm__ ("movq %0, %%rdi # from in rdi;" :: "r" ( from ));
	__asm__ ("movq %0, %%rsi # to in rsi;" :: "r" ( to ));
	__asm__ ("movq %0, %%rax # result in rax;" :: "r" ( result ));

	// Your x86-64 code goes below - comment each instruction...
	__asm__(
		// TODO - Replace the instruction below with add, compare,
		// jump instructions, labels, etc as necessary to implement
		// the loop.
		".LOOP:" // beginning of loop label, occurs before jle so will "do" before "while"
		"addq %rdi, %rax;" // add "from" to "result"
		"addq $1, %rdi;" // add 1 to "from"
		"cmpq %rsi, %rdi;" // compare "to - from", result will be 0 or positive to jump
		"jle .LOOP;" // in combo with cmpq, "from <= to" (signed)
	
	);
	// Ensure that *result* is in %rax for return - *do not modify*.
	__asm__ ("movq %%rax, %0 #result in rax;" : "=r" ( result ));
	return result;
}

int main() {
     printf("sum(1, 6): %ld\n", sum(1, 6));
     printf("sum(3, 5): %ld\n", sum(3, 5));
     printf("sum(5, 3): %ld\n", sum(5, 3));
}
