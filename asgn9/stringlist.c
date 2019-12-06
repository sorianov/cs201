#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringlist.h"

/**
 * Creates a new node for a linked list.
 *
 * Input:
 * node** newNode - Pointer to a node that we will overwrite
 * char* name - Data to store in the node
 */
void createNode(node** newNode, char* name) {
    char* string = NULL;
    node* temp = NULL;

    temp = (node*) malloc(sizeof(node));
    string = (char*) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(string, name);
    temp->data = string;
    temp->next = NULL;
    *newNode = temp;
}

/**
 * Adds a name to a linked list.
 *
 * Input:
 * node** head - Pointer to the first node in list
 * char* name - Data to add
 *
 * Return:
 * int 1 - Successful addition
 * int 0 - Failure
 */
int addName(node** head, char* name) {
    node* temp = NULL;
    node* current = NULL;
    createNode(&temp, name); // store new node in temp
    if (*head == NULL) {
        // empty list
        *head = temp;
        return 1;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
        return 1;
    }
    return 0;
}

/**
 * Removes a node from a linked list based on name.
 *
 * Input:
 * node** head - Pointer to the first node in list
 * char* name - Data that should be removed
 *
 * Return:
 * int 1 - Successful removal
 * int 0 - Removal failure
 */
int removeName(node** head, char* name) {
    node* current = *head;
    node* previous = current;

    //traverse list until we reach desired node
    while(strcmp(current->data, name)) {
        previous = current;
        if (current->next == NULL) {
            // these aren't the droids you're looking for
            // AKA couldn't find name
            return 0;
        }
        current = current->next;
    }

    if (previous == current) {
        // head needs to be removed
        if (current->next) {
            // there's at least one other node besides the head
            previous = current;
            current = current->next;
            previous->next = NULL;
            free(previous->data);
            free(previous);
            previous = NULL;
            *head = current;

            return 1;
        } else {
            // only the head remains and it should be removed
            free(current->data);
            free(current);
            current = NULL;
            *head = NULL;

            return 1;
        }
    } else if (current->next == NULL) {
        // we're at the end of the list
        previous->next = NULL;
        free(current->data);
        free(current);
        return 1;
    } else {
        // in the middle of two nodes
        previous->next = current->next;
        free(current->data);
        free(current);
        return 1;
    }

    return 0;
}

/**
 * Prints the data of each node in a linked list.
 *
 * Output:
 * Data of each node space delimited.
 */
void printList(node** head) {
    node* current = *head;

    if (current == NULL) {
        // nothing to print
        return;
    }

    while(current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
}

/**
 * Frees a linked list.
 *
 * Will free the data of each node and the node itself.
 */
void deleteList(node** head) {
    node* current = *head;
    node* next = NULL;

    if (current == NULL) {
        // empty list, or pointer has been lost X_X
        return;
    }

    while (current->next) {
        next = current->next;
        removeName(&current, current->data);
        current = next;
    }

    // remove remaining node
    if (next) {
        removeName(&next, next->data);
    }

    // Only head exists
    if (current) {
        removeName(&current, current->data);
    }

    *head = NULL;
}
