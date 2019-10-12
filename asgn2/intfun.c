/**************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-10-09
 * Title: Assignment 1: Integer Representation
 *************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t HEX_LENGTH = 7; // length to store hex string
const size_t BINARY_LENGTH = 20; // length to store binary string
const size_t NIBBLE_LENGTH = 5; // length to store nibble string

/**
 * Function declarations.
 */
size_t isBigEndian();
void printAuthor();
void printEndian();
void printDatasizes();
void printAsBinary(short);
void printDataTable();
void hexCharToNibble(char, char*);
void hexToBin(char*, char*);

/**
 * Determines whether the machine is little endian or big endian.
 *
 * Return
 * size_t - 0 if little endian, 1 if big endian.
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
 * Returns a pointer to a character array that holds a nibble respresentation
 * of parameter hexChar.
 *
 * Input:
 * char hexChar - A hexadecimal character.
 *
 * Return:
 * char* nibble - A pointer to a null terminated character array.
 */
void hexCharToNibble(char hexChar, char* nibble) {
    switch (hexChar) {
        case '0':
            strcpy(nibble, "0000\0");
            break;
        case '1':
            strcpy(nibble,"0001\0");
            break;
        case '2':
            strcpy(nibble,"0010\0");
            break;
        case '3':
            strcpy(nibble,"0011\0");
            break;
        case '4':
            strcpy(nibble,"0100\0");
            break;
        case '5':
            strcpy(nibble,"0101\0");
            break;
        case '6':
            strcpy(nibble,"0110\0");
            break;
        case '7':
            strcpy(nibble,"0111\0");
            break;
        case '8':
            strcpy(nibble,"1000\0");
            break;
        case '9':
            strcpy(nibble,"1001\0");
            break;
        case 'a':
            strcpy(nibble,"1010\0");
            break;
        case 'b':
            strcpy(nibble,"1011\0");
            break;
        case 'c':
            strcpy(nibble,"1100\0");
        case 'd':
            strcpy(nibble,"1101\0");
            break;
        case 'e':
            strcpy(nibble,"1110\0");
            break;
        case 'f':
            strcpy(nibble,"1111\0");
            break;
        default:
            strcpy(nibble,"err.\0");
            break;
    }
}

/**
 * Converts a two byte hexadecimal number string to a two byte binary string.
 * This function assumes that the hexadecimal number string is in 0x#### format.
 * In other * words, I'm assuming the hex parameter is a pointing to a character array
 * with a length of HEX_LENGTH.
 *
 * Input:
 * char* hex - Points to HEX_LENGTH character array
 *
 * Returns:
 * char* binary - Points to a BINARY_LENGTH character array
 */
void hexToBin(char* hex, char* binary) {
    char* nibble = malloc(NIBBLE_LENGTH);
    char b[BINARY_LENGTH];
    size_t printedNibbles = 0;
    size_t binIndex = 0; // will keep track of our position in binary.

    // start at 2 to ignore "0x" in string.
    for (size_t i = 2; i < HEX_LENGTH - 1; ++i) {
        hexCharToNibble(hex[i], nibble);

        for (size_t j = 0; j < NIBBLE_LENGTH - 1; ++j) {
            b[binIndex++] = nibble[j];
        }
        printedNibbles++;

        if (printedNibbles == 1) { // add a space in between nibbles
            b[binIndex++] = ' ';
        } else if (printedNibbles == 2) { // add two spaces in between bytes
            b[binIndex++] = ' ';
            b[binIndex++] = ' ';
            printedNibbles = 0;
        }
    }
    free(nibble);
    b[binIndex] = '\0';
    strcpy(binary, b);
}

/**
 * Prints numToPrint as a two byte binary string.
 *
 * Input:
 * short numToPrint - number to convert.
 *
 * Output:
 * prints Two byte binary representation.
 */
void printAsBinary(short numToPrint) {
    char* hex = malloc(HEX_LENGTH);
    char* binary = malloc(BINARY_LENGTH);
    sprintf(hex, "%#06hx", numToPrint);
    hexToBin(hex, binary);
    printf("%s\n", binary);
    free(hex);
    free(binary);
}

/**
 * Prints a table from -3 to 10 with decimal, hexadecimal, and binary
 * representations.
 */
void printDataTable() {
    puts("Dec\tHex\tBinary");
    for (short i = -3; i < 11; ++i) {
        printf("%d\t%#06hx\t", i, i);
        printAsBinary(i);
    }
}


int main(void) {
    printAuthor();
    printEndian();
    puts("");
    printDatasizes();
    puts("");
    printDataTable();

    return 0;
}
