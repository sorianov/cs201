/**************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-10-09
 * Title: Assignment 1: Integer Representation
 *************************************************************************/
#include <stdio.h>

const size_t BITS_PER_BYTE = 8;
const size_t BYTES_TO_PRINT = 2;
const short TABLE_BEGIN = -3;
const short TABLE_END = 10;

/**
 * Function declarations.
 */
size_t isBigEndian();
void printAuthor();
void printEndian();
void printDatasizes();
void printAsBinary(short, short);
void printDataTable(short, short);
short nthBit(short, short);

/**
 * Determines whether the machine is little endian or big endian.
 * Code was taken from lecture notes.
 *
 * Return
 * size_t - 0 if little endian, 1 if big endian.
 *
 * Author: Rich Albers
 */
size_t isBigEndian() {
    unsigned int x=0x12345678;
    unsigned char* xp;

    xp = (unsigned char*) &x;
    if (*xp == 0x78) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Prints the name of the author of this code.
 */
void printAuthor() {
    puts("Author: Victor Soriano Mendoza");
}

/**
 * Prints a string indicating the machines endian-ness.
 */
void printEndian() {
    if (isBigEndian()) {
        puts("Computer is big endian.");
    } else {
        puts("Computer is little endian.");
    }
}

/**
 * Prints the number of bytes used by the following datatypes:
 *   - short
 *   - int
 *   - long
 *   - long long int
 */
void printDatasizes() {
    printf("sizeof(short) = %zx\n", sizeof(short));
    printf("sizeof(int) = %zx\n", sizeof(int));
    printf("sizeof(long) = %zx\n", sizeof(long));
    printf("sizeof(long long) = %zx\n", sizeof(long long int));
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
short nthBit(short n, short k) {
    short mask = 1 << (k - 1);
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
 * num - value to print
 * numBytes - how many bytes to print
 *
 * Output:
 * Prints binary representation with two spaces between bytes
 * and one space between nibbles.
 */
void printAsBinary(short num, short numBytes) {
    short numBits = BITS_PER_BYTE * numBytes;
    short modEight = 0;
    short modFour = 0;

    for (short i = numBits; i; --i) {
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
 * Print tab delimited table from begin to end
 * of integers with decimal, hexadecimal, and binary
 * representations.
 *
 * Input:
 * short begin - value to start at
 * short end - value to end at (inclusive)
 */
void printDataTable(short begin, short end) {
    puts("Dec\t Hex\t      Binary");
    for (short i = begin; i <= end; ++i) {
        printf("%d\t%#06hx\t", i, i);
        printAsBinary(i, BYTES_TO_PRINT);
        puts("");
    }
}


int main(void) {
    printAuthor();
    printEndian();
    puts("");
    printDatasizes();
    puts("");
    printDataTable(TABLE_BEGIN, TABLE_END);

    return 0;
}
