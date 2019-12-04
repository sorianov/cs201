#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringlist.h"

void createNode(node** newNode, char* name) {
    char* string;
    node* temp = NULL;
    
    temp = (node*) malloc(sizeof(node));
    string = (char*) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(string, name);
    temp->data = string;
    temp->next = NULL;
    *newNode = temp;
}

int addName(node** head, char* name) {
    node* temp = NULL;
    node* current = NULL;
    createNode(&temp, name); // store new node in temp
    if (*head == NULL) { // empty list
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

int removeName(node** head, char* name) {
    node* current = *head;
    node* previous = current; 
    
    //traverse list until we reach desired node
    while(strcmp(current->data, name)) {
        previous = current;
        if (current->next == NULL) {
            // these aren't the droids you're looking for
            return 0;
        }
        current = current->next;
    }
    
    if (current->next == NULL) {
        // we're at the end of the list
        previous->next = NULL;
        free(current->data);
        free(current);
    } else {
        // in the middle of two nodes
        previous->next = current->next;
        free(current->data);
        free(current);
    }

    //TODO everything else

    return 1;
}

void printList(node** head) {
    node* current = *head;
    while(current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}
