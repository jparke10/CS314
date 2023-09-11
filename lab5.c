#include <stdio.h>

// i can't run this cuz my computer is ARM based lol

/* ----- PART 1: ASSEMBLY ----- */

// original C function:
//
// int sumArr(long *a, long size) {
//   long result = 0;
//   for (long i = size - 1; i >= 0; --i) {
//     result += a[i];
//   }
//   return result;
// }
//
// assembly: your implementation below

long sumArr(long *a, long size) {
        // Declare and initialize result var – do not modify.
        long result = 0;

        // Ensure that argument *from* is in %rdi,
        // argument *to* is in %rsi, *result* is in %rax - *do
        // not modify*.
        __asm__ ("movq %0, %%rdi # from in rdi;" :: "r" ( a )); // a in rdi
        __asm__ ("movq %0, %%rsi # to in rsi;" :: "r" ( size )); // size in rsi
        __asm__ ("movq %0, %%rax # result in rax;" :: "r" ( result )); // result in rax

        // Your x86-64 code goes below - comment each instruction...
        __asm__(
                // TODO - Replace the two lines below with add, compare,
                // jump instructions, labels, etc as necessary to implement
                // the loop.
		// comment each line explaining its purpose

		// for (long i = size - 1; i >= 0; --i) {
		// 	result += a[i];
		// }

		// remember your for loops:
		// 1. init i, 2. condition, 3. enter body, 4. decrement, 5. go to 2. and repeat
		
		// size is in rsi, want to init i
		// long i = size - 1;
                "subq $1, %rsi;" // rsi -= 1; (size in rsi, reuse for i)
                ".LOOP:" // loop body label
		// i >= 0, 1 in rsi from above
                "cmpq $-1, %rsi;"
		// equivalent to subtraction except result discarded
		// rsi - (-1) = rsi + 1
                "je .END;" // if rsi - (-1) == 0, jump to end
		// could also do testq %rsi, %rsi, would need to change the jump

		// loop body: result += a[i];
		// a (or &a[0]) in rdi, i in rsi, sizeof(long) = 8
		// remember: (a, b, c) --> a + b*c
                "addq (%rdi, %rsi, 8), %rax;"
		// rax += rdi + 8*rsi
		// result += a + sizeof(a[0])*i, equivalent to result += a[i]

		// dec i
                "subq $1, %rsi;"
                "jmp .LOOP;" // unconditional jump to LOOP
                ".END:" // end label
        );

        // Ensure that *result* is in %rax for return - *do not modify*.
        __asm__ ("movq %%rax, %0 #result in rax;" : "=r" ( result ));
        return result;
}

/* ----- PART 2: RECURSION AND STACK FRAMES ----- */

// if you're curious, check out backtrace()

void rec(int depth, int *caller)
{
        int loc = 0;
        int *p = &loc;
        printf("depth: %d, loc:\t%p, diff: %ld\n", depth, p, (caller - p)*4);
        if (depth == 0) 
        {
                return;
        } 
        rec(depth-1, p);
}

// stack pointer modifiers: pushes, pops, calls, and rets
// call is a push and a jump, ret is a pop and a jump

// size of a stack frame: sum of size of arguments, return addr, and local vars
// eg for rec, we have depth, caller, loc and p, return addr: 4 + 8 + 4 + 8 + 8 = 32

// stack frame is 32 bytes for rec()

/*
 * main
 * 	rec(5)
 * 		rec(4)
 * 			rec(3)
 * 				rec(2)
 * 					rec(1)
 * 						rec(0)
 * 						ret
 * 					ret
 * 				ret
 * 			ret
 * 		ret
 * 	ret
 */

int main() {
        printf("----- PART 1 -----\n");
        long testArr[5] = {1, 2, 3, 4, 5};
        printf("sumArr({1, 2, 3, 4, 5}, 5): %ld\n", sumArr(testArr, 5));

        printf("----- PART 2 -----\n");
        printf("main: %p, rec: %p.\n", main, rec);
        int loc = 0;
        int *p = &loc;
        printf("%ld, %ld.\n", sizeof(loc), sizeof(p));
        printf("sp:\t\t%p\n", p);
        rec(5, p);
}
