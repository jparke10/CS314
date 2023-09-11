#include <stdio.h>
#include <stdlib.h>

// struct intArray ...
/*
struct IntArray {
	int length;
	int *dataPtr;
};

typedef struct {
	int length;
	int *dataPtr;
} intArray;
*/
// intArray ...

int readInt() 
{
        char lineBuf[10];
        char *p = NULL;
        int n;

        while (1) {
                // char* fgets (char* str, int num, FILE* stream);
                fgets(lineBuf, sizeof(lineBuf), stdin);

                // long int strtol (const char* str, char** endptr, int base);
                n = strtol(lineBuf, &p, 10);
                if (lineBuf != p) {
                        printf("Pointers after read:\n\tLinebuf: %p\n\tp: %p\n", 
                                lineBuf, p);
                        break;
                }

                printf("Invalid input\n");
        }

        return n;
}

long f(long x, long y, long z) 
{
        // x in %rdi, y in %rsi, z in %rdx, %rax holds return value.
        // Comment each line of assembly in terms of x, y, and z
        // good reference: https://flint.cs.yale.edu/cs421/papers/x86-asm/asm.html (or find another resource that works for you)

        // leaq (%rdi,%rsi), %rax
	// lea (%ebx, %esi, 8), %edi - the quantity EBX+8*ESI is polaced in EDI
	// formula for lea (a, b, c), d :
	// d = a + b*c
	// if we know x is in rdi and y is in rsi, C code is:
	// leaq (x, y), result --> result = x + y;
	long result = x + y;

        // imulq %rdx, %rax
	// imul (%ebx), %eax — multiply the contents of EAX by the 32-bit contents of the memory at location EBX. Store the result in EAX.
	// for imul a, b --> b = a * b
	// we know that z is in rdx, what's the C code?
	result *= z;

	// note: parens around register interpret as dereference (go to mem location specified by address in register)

        // ret
	return result;

        // after comments, implement in C (replace "return 0" to match asm)
        // compile with flags: -Wall -Og -S -masm=att for .s file, or use godbolt
}

int main() 
{
	// get length from stdin w/ readInt()
	// number accessing:
	// struct IntArray intArray
	// intArray.length = ...
	// &intArray->length = ...
	// OR:
	// struct IntArray *intArray
	// intArray->length = ...
	// swap and sort are up to you, no need to reinvent the wheel
	// e.g. use bubble sort
	// cite your sources
	
        // ---------- PART 1: memory management ----------

        // create int array of fixed length, but with malloc

        int i, length, *arr;
	
	length = 3;

	// normally for a fixed length array
	// int exampleArray[length];
	// fixed at compile time
	
        // loop over array and fill with readInt
	arr = (int*)malloc(length * sizeof(int));
	// not fixed at compile time
	// "resolved" during runtime
	
	// assn 1: make this into readIntArray
        for (i = 0; i < length; i++) 
        {
		printf("Enter value %d: ", i);
		arr[i] = readInt();
        }

        // loop over again and print

        for (i = 0; i < length; i++) 
        {
		printf("%d, ", arr[i]);
        }
	printf("%d]\n", arr[i]);

        // free malloc'd array pointer
	
	free(arr);

        // ---------- PART 2: reverse engineering ASM ----------

        // implement f() above

        printf("f(1, 2, 3): %ld.\n",   f(1, 2, 3));
        printf("f(7, 11, 13): %ld.\n", f(7, 11, 13));
}
