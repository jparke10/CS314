// convert 11100101 from 8 bit float to decimal

// separate sign, exponent, and mantissa

// 4 bit exponent: 1 1100 101

// restore the mantissa leading 1

// 1.101

// subtract bias from exponent. bias = 2^(k-1)-1, where k = number of digits in exponent field (3 for 8bit floats)

// 2^(4-1)-1
// 8-1 = 7
// exp: 1100 = 2^0 * 0 + 2^1 * 0 + 2^2 * 1 + 2^3 * 1
// = 0 + 0 + 4 + 8 = 12
// 12 - 7 = 5 is our "denorm factor" (shift)

// denormalize mantissa: move decimal point according to the preceeding step

// 1.101 * 2^5 = 110100.00

// convert to decimal: multiply each digit by 2^x, where x is the "place" of the digit, and then sum

// skip decimals since they're all 0, and work backwards
// 0 * 2^0 + 0 * 2^1 + 1 * 2^2 + 0 * 2^3 + 1 * 2^4 + 1 * 2^5
// = 2 + 16 + 32 = 50

// apply sign bit

// sign 1 = -1
// -1 * 50 = **-50**
// done!

#include <stdio.h>

unsigned int unsignedBinaryToDecimal(unsigned char *s, int length) {
    unsigned int result = 0;
    for (int i = 0; i < length; i++) {
        // TODO: implement
	// bit from s
	unsigned int bit = s[length - i - 1];
	// exp
	unsigned int exp = 1 << i;
	// bit * exp
	unsigned int mult= bit * exp;
	// add to result
	result += mult;
    }
    return result;
}

int main() {
    unsigned char s[8] = {0, 1, 1, 0, 1, 0, 1, 1};

    printf("%d\n", unsignedBinaryToDecimal(s, 8));
}
