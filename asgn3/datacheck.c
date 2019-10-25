/**************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-10-21
 * Title: Assignment 2b: Data Interpretation
 *************************************************************************/
#include <stdio.h>

/**
 * Prints the name of the author of this code.
 */
void printAuthor() {
    puts("Author: Victor Soriano Mendoza\n");
}

/**
 * Prints numBytes as hexadecimal values.
 *
 * Input:
 * unsigned char* startAddr - Pointer to start at
 * int            numBytes  - Number of bytes to print
 *
 * Output:
 * Prints bytes as hexadecimal values with 2 digit padding.
 */
void printBytes(unsigned char* startAddr, int numBytes) {
    for (int byte = 0; byte < numBytes; ++byte) {
        printf("0x%02x ", *startAddr++);
    }
    printf("\n");
}

int main(void) {
    unsigned int ui = 3200253952;
    int si = -1094713344;
    unsigned short us = 48832;
    short ss = -16704;
    float f = -.375;

    printAuthor();

    printf("unsigned int:   %u ", ui);
    printf("\tBytes: ");
    printBytes((unsigned char*)&ui, 4);

    printf("int:            %d ", si);
    printf("\tBytes: ");
    printBytes((unsigned char*)&si, 4);

    printf("unsigned short: %d ", us);
    printf("\t\tBytes: ");
    printBytes((unsigned char*)&us, 2);

    printf("short:          %d ", ss);
    printf("\t\tBytes: ");
    printBytes((unsigned char*)&ss, 2);

    printf("float:          %f ", f);
    printf("\tBytes: ");
    printBytes((unsigned char*)&f, 4);

    return 0;
}
