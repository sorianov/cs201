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

/**
 * Adds a ".d" extension to a character array.
 *
 * Input:
 * char* inFilename - The original character array.
 * char** outFilename - A copy of the original character array + the
 *                      ".d" extension.
 *
 * Return:
 * None - outFilename is assigned to the address of a dynamically allocated
 *        memory block that holds the character array.
 */
void createOutFilename(char* inFilename, char** outFilename) {
    char* oFilename = NULL;
    char* oFilenameExtension = ".d\0";
    size_t inFilenameLength = 0;
    size_t oFilenameLength = 0;

    inFilenameLength = strLength(inFilename);
    oFilenameLength = inFilenameLength + EXTENSION_LENGTH;
    oFilename = (char*) malloc(sizeof(char) * oFilenameLength);
    addExtension(inFilename, oFilename, oFilenameExtension,
                inFilenameLength);

    *outFilename = oFilename;
}

/**
 * Reads the contents of a file into a buffer.
 *
 * Input:
 * char** buffer - A pointer pointing to a character pointer that will
 *                 store the file's contents.
 * char* inFilename - The name of the file to be read.
 *
 * Return:
 * size_t result - The number of bytes read in from inFilename.
 */
size_t readIntoBuffer(char** buffer, char* inFilename) {
    FILE* pFile = NULL;
    long lSize = 0;
    size_t result = 0;

    // Open input file for reading
    pFile = fopen(inFilename, "rb");
    if (pFile == NULL) {
        fputs("Could not open file for reading\n", stderr);
        exit(EXIT_FAILURE);
    }

    // Calculate input file size
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // Create buffer to hold input file contents
    *buffer = (char*) malloc(sizeof(char) * lSize);
    if (*buffer == NULL) {
        fputs("Could not allocate memory to file buffer.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // Copy input file contents into buffer
    result = fread(*buffer, 1, lSize, pFile);
    fclose(pFile);
    pFile = NULL;
    if (result != lSize) {
        fputs("Error reading file into buffer.\n", stderr);
        exit(EXIT_FAILURE);
    }

    return result;
}

/**
 * Prints the name of the author of this code.
 */
void printAuthor() {
    puts("Author: Victor Soriano Mendoza");
}

/**
 * Decrypts a buffer and stores the decrypted data to a file named
 * outFilename.
 *
 * Input:
 * char* buffer - Buffer to be decrypted.
 * char* outFilname - Filename where data should be written to.
 * size_t bufSize - The size of buffer.
 *
 * Return:
 * size_t written - The number of bytes written to outFilename.
 */
size_t decryptToFile(char* buffer, char* outFilename, size_t bufSize) {
    char* decrypted = NULL;
    FILE* pFile;
    size_t written = 0;

    // Open output file for writing
    pFile = fopen(outFilename, "wb");
    if (pFile == NULL) {
        fputs("Could not open file for writing.\n", stderr);
        return EXIT_FAILURE;
    }

    // Decrypt buffer contents and place it into new buffer
    decrypted = decryptFile(buffer, bufSize);

    // Write decrypted buffer to output file
    written = fwrite((void *)decrypted, sizeof(char), bufSize, pFile);
    fclose(pFile);
    free(decrypted);
    return written;
}

/**
 * Prints output that follows assignment guidelines.
 *
 * Inputs:
 * char* inFilename - Filename passed as argument.
 * size_t read - Number of bytes read in from inFilename.
 * char* outFilename - Name of the file being written to.
 * size_t written - Number of bytes written to outFilename.
 *
 * Example Output:
 *   Author: Victor Soriano Mendoza
 *   Input file: data.dat
 *   File Size: 28 bytes
 *   Output file: data.dat.d
 *   Decryption Successful! Output file created.
 */
void printAssignmentOutput(char* inFilename, size_t read, char* outFilename,
        size_t written) {

    printAuthor();
    printf("Input file: %s\n", inFilename);
    printf("File Size: %zu bytes\n", read);
    printf("Output file: %s\n", outFilename);
    if (written == read) {
        printf("Decryption Successful! Output file created.\n");
    } else {
        printf("Decryption Unsuccessful! File size mismatch.\n");
    }
}

int main(int argc, char* argv[]) {
    char* programName = argv[0];
    char* inFilename = NULL;
    char* outFilename = NULL;
    char* buffer = NULL;
    size_t written = 0;
    size_t result = 0;

    // Check that we have an input file
    if (argc != MIN_ARGUMENTS) {
        printf("%s usage:\n", programName);
        printf("\t%s FILE\n", programName);
        return EXIT_FAILURE;
    }

    // Create output filename
    inFilename = argv[1];
    createOutFilename(inFilename, &outFilename);
    result = readIntoBuffer(&buffer, inFilename);

    // Decrypt and write to file
    written = decryptToFile(buffer, outFilename, result);

    // Print output according to assignment.
    printAssignmentOutput(inFilename, result, outFilename, written);

    // Cleanup
    free(buffer);
    free(outFilename);
    return EXIT_SUCCESS;
}
