/**************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-10-18
 * Title: Assignment 2a: Floating Point Dissection
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>

const int SIGN_BIT = 31;
const int EXP_START_BIT = 30;
const int EXP_END_BIT = 23;
const int FRAC_START_BIT = 22;
const int FRAC_END_BIT = 0;

union floatInt {
    float f;
    int i;
};

/** Function declarations **/
void printFloatInfo(union floatInt);
void printFractionalBits(int);
void printExpBits(int);
void printSignBit(int);
void printAsBinary(int, int);
void printAuthor();
/**************************/

/**
 * Prints the name of the author of this code.
 */
void printAuthor() {
    puts("Author: Victor Soriano Mendoza");
}

/**
 * Determines whether or not the kth bit of n is set.
 *
 * Input:
 * short n - value
 * short k - bit being checked
 *
 * Return:
 * 1 - bit set
 * 0 - bit unset
 */
int nthBit(int n, int k) {
    int mask = 1 << (k - 1);
    if (n & mask) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Prints a short in a n-byte binary representation.
 *
 * Input:
 * int num - value to print
 * int numBits - how many bits to print
 *
 * Output:
 * Prints binary representation with two spaces between bytes
 * and one space between nibbles.
 */
void printAsBinary(int num, int numBits) {
    int modEight = 0;
    int modFour = 0;

    for (int i = numBits; i; --i) {
        modEight = !(i % 8); // eight bits per byte
        modFour = !(i % 4); // four bits per nibble

        if (modEight && i != numBits) { // two spaces between bytes
            printf("  ");
        } else if (modFour && i != numBits) { // one space between nibbles
            printf(" ");
        }
            printf("%d", nthBit(num, i));
    }
}

/**
 * Prints information about the sign bits of a float. This function assumes
 * a union between a float and an int is being used. It also assumes a single
 * precision float.
 *
 * Input:
 * num - the int representation in the union
 *
 * Output:
 * The decimal, hexadecimal, and binary representation of SIGN BIT.
 */
void printSignBit(int num) {
    int signBit = nthBit(num, SIGN_BIT);
    printf("Sign:          %d       0x%x   %d",
        signBit,
        signBit,
        signBit);
    puts("");
}

/**
 * A fake pow() that has only been slightly tested using 2 as a
 * base. Not guaranteed to work on negative exponents. Created because the
 * compilation flags would need to be altered to link against <math.h>.
 *
 * Input:
 * int base - the base to use
 * int exponent - exponent to raise the base to
 *
 * Return:
 * int value - the base multiplied by itself exponent times.
 */
int _pow(int base, int exponent) {
    int value = 1;
    for (int i = 0; i < exponent; ++i) {
       value = value * base;
    }
    return value;
}

/**
 * Prints information about the exponent bits of a float. Assumes a union is
 * being used with a float and int.
 *
 * Input:
 * int num - the integer part of the union.
 *
 * Output:
 * Prints the decimal, hexadecimal, and binary representation of bits 30-23
 */
void printExpBits(int num) {
    int dec = 0;
    int bit = (EXP_START_BIT - EXP_END_BIT) - 1;
    for (int i = EXP_START_BIT; i >= EXP_END_BIT; --i) {
        dec = dec + (_pow(2, bit) * nthBit(num, i));
        --bit;
    }
    printf("Exp bits:    %d      %#x   ", dec, dec);
    printAsBinary(dec, 8); // print a byte
}

/**
 * Prints information about the fractional bits of a float. Assumes a union
 * is being used with a float and int.
 *
 * Input:
 * int num - the integer part of the union.
 *
 * Output:
 * Prints the decimal, hexadecimal, and binary representation of bits 22-0
 */
void printFractionalBits(int num) {
    int dec = 0;
    int bit = (FRAC_START_BIT - FRAC_END_BIT) - 1;
    for (int i = FRAC_START_BIT; i >= FRAC_END_BIT; --i) {
        dec = dec + (_pow(2, bit) * nthBit(num, i));
        --bit;
    }
    if (dec == 0) {
        printf("Fraction:    %d     0x%#05x   ", dec, dec);
    } else {
        printf("Fraction:    %d     %#05x   ", dec, dec);
    }
    printAsBinary(dec, 19); // print 19 bits

}

void printFloatInfo(union floatInt fInt) {
    printf("Float val:   %f\n", fInt.f);
    printf("In hex:      %#0x\n", fInt.i);
    printf("In binary:   ");
    printAsBinary(fInt.i, 32); // print 4 bytes
}

int main(int argc, char* argv[]) {

    // Verify we recieved the correct amount of arguments
    if (argc != 2) { printf("Usage: %s float_value\n", argv[0]);
        return -1;
    }

    union floatInt fInt = { .f = atof(argv[1]) };

    printAuthor();
    puts("");
    printFloatInfo(fInt);
    puts("\n");
    printSignBit(fInt.i);
    printExpBits(fInt.i);
    puts("\n");
    printFractionalBits(fInt.i);
    puts("\n");

    return 0;
}
