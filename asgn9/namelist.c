//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2019-12-05
// Title: Assignment 9: Dynamic Memory Allocation (Linked List)
// Description: A program which uses a linked list to store strings.
//----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringlist.h"

/**
 * Copies the string from argName to name excluding the first character.
 *
 * Input:
 * char* argName -  The source pointer that holds the string
 * char** name   -  The destination pointer that points to the destination
 *                  pointer.
 *
 * Return:
 * Storage of the new string is done by replacing the reference of name to
 * temp.
 */
void parseArgName(char* argName, char** name) {
    char* temp;
    size_t nameLength = strlen(argName);
    temp = (char*)malloc(sizeof(char) * (nameLength));
    for(size_t i = 0; i < nameLength; ++i) {
        temp[i] = argName[i+1];
    }
    *name = temp;
}

/**
 * Processes an argument from the command line
 *
 * Will add name to linked list if name is prefixed with a '+'. Name will be
 * removed from the linked list if it is prefixed with a '-'. Will print error
 * message and exit if the first character of the argument does not match
 * either '+' or '-';
 */
void processName(node** llhead, char* argName) {
    char* name = NULL;
    parseArgName(argName, &name);

    if (argName[0] == '+') {
        // add name to list
        printf("Added %s\t", name);
        addName(llhead, name);
        printf("List: ");
        printList(llhead);
    } else if (argName[0] == '-') {
        // remove name from list
        printf("Removed %s\t", name);
        removeName(llhead, name);
        printf("List: ");
        printList(llhead);
    } else {
        printf("Action '%c' not supported.\n", argName[0]);
    }
    printf("\n");
    free(name);
}

/**
 * Processes commandline arguments
 *
 * Input:
 * int argc - Number of arguments.
 * char* argb[] - Values of arguments.
 * node** llhead - Head node of linked list.
 */
void processArgs(int argc, char* argv[], node** llhead) {
    for (size_t i = 1; i < argc; ++i) {
        processName(llhead, argv[i]);
    }
}

int main(int argc, char* argv[]) {
    node* llhead = NULL;

    printf("Author: Victor Soriano Mendoza\n\n");
    processArgs(argc, argv, &llhead);
    deleteList(&llhead);

    return EXIT_SUCCESS;
}

