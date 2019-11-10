/*****************************************************************************
 * Author: Victor Soriano Mendoza
 * Instructor: Rich Albers
 * Date: 2019-11-10
 * Title: Assignment 6: Dynamic Memory Allocation, File I/O, and 
 *                      Bit Manipulation
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t EXTENSION_LENGTH = 3;
const size_t MIN_ARGUMENTS = 2;

size_t strLength(char* str) {
    size_t i = 0;
    while(str[i] != '\0') {
        ++i;
    }
    return i;
}

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

char swapNibbles(char byte) {
    return (byte & 0x0f) << 4 | (byte & 0xf0) >> 4;
}

char flipBits(char byte) {
    return ~byte;
}

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
