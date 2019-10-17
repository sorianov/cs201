#include <stdio.h>
#include <stdlib.h>

const int BITS_PER_BYTE = 8;

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
 * num - value to print
 * numBytes - how many bytes to print
 *
 * Output:
 * Prints binary representation with two spaces between bytes
 * and one space between nibbles.
 */
void printAsBinary(int num, int numBytes) {
    int numBits = BITS_PER_BYTE * numBytes;
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

void printSignBit(int num) {
    int signBit = nthBit(num, 31);
    printf("Sign:     %d\t%x\t", signBit, signBit);
    printAsBinary(signBit, 1);
    puts("");
}

int main(int argc, char* argv[]) {
    float y;

    // Verify we recieved the correct amount of arguments
    if (argc != 2) {
        printf("Usage: %s float_value\n", argv[0]);
        return -1;
    }

    // Convert c-string argument into float
    y = atof(argv[1]);

    union {
        float f;
        int i;
    } fInt = { .f = y };

    printAuthor();
    puts("");
    printf("Float val:   %f\n", y);
    printf("In hex:      %#0x\n", fInt.i);
    printf("In binary:   ");
    printAsBinary(fInt.i, 4);
    puts("");
    printSignBit(fInt.i);

    return 0;
}
