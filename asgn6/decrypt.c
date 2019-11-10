#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t EXTENSION_LENGTH = 3;
const size_t MIN_ARGUMENTS = 2;

void addExtension(char* inFile, char* outFile, char* extension,
        size_t inLength, size_t toLength) {

    size_t i = 0;

    for (;i < inLength; ++i) { // don't want to write null
        outFile[i] = inFile[i];
    }
    printf("break: %zu\n", i);
    for (size_t j = 0; j < EXTENSION_LENGTH; ++j) {
        outFile[i] = extension[j];
        printf("%zu\t%c\n", i, outFile[i]);
        i++;
    }

}

int main(int argc, char* argv[]) {
    char* programName = argv[0];
    char* outFileExtension = ".d\0";

    if (argc != MIN_ARGUMENTS) {
        printf("%s usage:\n", programName);
        printf("\t%s FILE\n", programName);
        return EXIT_FAILURE;
    }

    char* inFile = argv[1];
    size_t inFileLength = sizeof(char *) * sizeof(inFile);
    size_t outFileLength = inFileLength + 3;
    char* outFile = malloc(sizeof(char) * outFileLength);
    addExtension(inFile, outFile, outFileExtension,
                inFileLength, outFileLength);


    printf("%s Length: %d\n", inFile, inFileLength);
    printf("%s Length: %d\n", outFile, outFileLength);


    return EXIT_SUCCESS;
}
