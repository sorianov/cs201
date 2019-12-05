#include <stdio.h>
#include "stringlist.h"

int main(int argc, char* argv[]) {
    node* llhead = NULL;
    char* name = "Victor";
    char* name2 = "Soriano";
    char* name3 = "Mendoza";
    addName(&llhead, name);
    addName(&llhead, name2);
    addName(&llhead, name3);
    printList(&llhead);
    removeName(&llhead, "Soriano");
    printList(&llhead);
    removeName(&llhead, "Mendoza");
    removeName(&llhead, "C3P0");
    printList(&llhead);
    removeName(&llhead, "Victor");
    printList(&llhead);
    addName(&llhead, name);
    addName(&llhead, name2);
    addName(&llhead, name3);
    printList(&llhead);
    removeName(&llhead, "Victor");
    printList(&llhead);
    removeName(&llhead, "Soriano");
    removeName(&llhead, "Mendoza");
    printList(&llhead);
    return 0;
}

