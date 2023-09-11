#include <stdio.h>

/* godbolt compile returned:

_Z4factl: // label for main function body, called for recursion
        cmpq    $1, %rdi // compare "1 - x"
        jle     .L3 // combined with cmpq, "if x <= 1 jump" (base case)
        pushq   %rbx // save current return pointer address to stack
        movq    %rdi, %rbx // set return pointer equal to x
        leaq    -1(%rdi), %rdi // x * (x - 1)
        call    _Z4factl // push return address %rbx to stack and goto top of _Z4factl
        imulq   %rbx, %rax // multiply return value from recursion into function return register
        popq    %rbx // load recursion pointer address from stack and jump to that address
        ret // return number at that address (has had recursion operation performed on it)
.L3: // 
        movl    $1, %eax // move 1 to return register before returning base case
        ret

stack frame is 16 bytes. 8 byte argument x, no local variables, 8 byte return address

*/

long fact(long x) {
	if (x <= 1) {
		return 1;
	}
	return x * fact(x-1);
}

int main() {
	printf("fact(1): %li\n", fact(1));
	printf("fact(3): %li\n", fact(3));
	printf("fact(5): %li\n", fact(5));
}
