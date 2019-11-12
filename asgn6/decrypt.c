//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2019-11-10
// Title: Assignment 6: Dynamic Memory Allocation, File I/O, and
//                      Bit Manipulation
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

const size_t EXTENSION_LENGTH = 3;
const size_t MIN_ARGUMENTS = 2;

// Function declarations
size_t strLength(char*);
void addExtension(char*, char*, char*, size_t);
char swapNibbles(char);
char flipBits(char);
char* decryptFile(char*, size_t);

/**
 * Calculates the length of a character array
 *
 * Input:
 * char* str - Pointer to the character array
 *
 * Return:
 * size_t i - Length of the character array
 */
size_t strLength(char* str) {
    size_t i = 0;
    while(str[i] != '\0') {
        ++i;
    }
    return i;
}

/**
 * Concatenates an extension of characters to a character array.
 *
 * Input:
 * char* inFile - The original character array
 * char* outFile - The character array that will hold the original array
 *                 and the extension.
 * char* extension - A character array holding characters to be added. It
 *                   assumed the extension has a length of EXTENSION_LENGTH.
 * size_t inLength - The length of the original array
 *
 * Output:
 * None. The outFile array will be modified in place.
 */
void addExtension(char* inFile, char* outFile, char* extension,
        size_t inLength) {

    size_t i = 0;
    for (;i < inLength; ++i) { // don't want to write null
        outFile[i] = inFile[i];
    }

    for (size_t j = 0; j < EXTENSION_LENGTH; ++j) {
        outFile[i] = extension[j];
        i++;
    }

}

/**
 * Swaps the nibbles of byte. It is assumed that the char type is a byte.
 *
 * Input:
 * char byte - The byte that will have its nibbles swapped.
 *
 * Return:
 * char - A byte with the nibbles swapped.
 */
char swapNibbles(char byte) {
    return (byte & 0x0f) << 4 | (byte & 0xf0) >> 4;
}

/**
 * Flips all the bits in a byte. Assumes the char type is a byte.
 *
 * Input:
 * char byte - The byte that will have its bits flipped.
 *
 * Return:
 * char - A byte with its bits flipped.
 */
char flipBits(char byte) {
    return ~byte;
}

/**
 * Takes a character array and for every even byte will flip
 * the byte's bits, and will swap the nibbles of every odd byte.
 *
 * Input:
 * char* buffer - The character array to decrypt
 * size_t size - The size of buffer
 *
 * Return:
 * char* newBuffer - The buffer that holds the decrypted contents
 *                   of buffer.
 */
char* decryptFile(char* buffer, size_t size) {
    size_t i = 0;
    char c;
    char* newBuffer = (char*) malloc(sizeof(char) * size);

    while(i != size) {
        c = buffer[i];

        if ((i % 2) == 0) {
            c = flipBits(c);
        } else {
            c = swapNibbles(c);
        }

        newBuffer[i] = c;
        i++;
    }

    return newBuffer;
}

int main(int argc, char* argv[]) {
    char* programName = argv[0];
    char* outFilenameExtension = ".d\0";
    char* inFilename = NULL;
    char* outFilename = NULL;
    char* buffer = NULL;
    char* newBuffer = NULL;
    FILE* pFile = NULL;
    long lSize = 0;
    size_t inFilenameLength = 0;
    size_t outFilenameLength = 0;
    size_t result = 0;

    // Check that we have an input file
    if (argc != MIN_ARGUMENTS) {
        printf("%s usage:\n", programName);
        printf("\t%s FILE\n", programName);
        return EXIT_FAILURE;
    }

    // Create output filename
    inFilename = argv[1];
    inFilenameLength = strLength(inFilename);
    outFilenameLength = inFilenameLength + EXTENSION_LENGTH;
    outFilename = (char*) malloc(sizeof(char) * outFilenameLength);
    addExtension(inFilename, outFilename, outFilenameExtension,
                inFilenameLength);

    // Open input file for reading
    pFile = fopen(inFilename, "rb");
    if (pFile == NULL) {
        fputs("Could not open file for writing", stderr);
        return EXIT_FAILURE;
    }

    // Calculate input file size
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // Create buffer to hold input file contents
    buffer = (char*) malloc(sizeof(char) * lSize);
    if (buffer == NULL) {
        fputs("Could not allocate memory to file buffer.", stderr);
        return EXIT_FAILURE;
    }

    // Copy input file contents into buffer
    result = fread(buffer, 1, lSize, pFile);
    fclose(pFile);
    pFile = NULL;
    if (result != lSize) {
        fputs("Error reading file into buffer.", stderr);
        return EXIT_FAILURE;
    }

    // Open output file for writing
    pFile = fopen(outFilename, "wb");
    if (pFile == NULL) {
        fputs("Could not open file for writing", stderr);
        return EXIT_FAILURE;
    }

    // Decrypt buffer contents and place it into new buffer
    newBuffer = decryptFile(buffer, result);

    // Write decrypted buffer to output file
    fwrite((void *)newBuffer, sizeof(char), result, pFile);

    // Cleanup
    fclose(pFile);
    free(buffer);
    free(newBuffer);
    free(outFilename);
    return EXIT_SUCCESS;
}
