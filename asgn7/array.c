
/* ***********************************************************
 Name: array.c
 Desc: Initialzies, manipulates, and finds largest value in a
        2-d array.

	Students will analyze with gprof and improve code.

************************************************************* */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int findLargest(int a[][SIZE]) {
	int largeNum=a[0][0];
	for(int x=0; x<SIZE; x++) {
		for(int y=0; y<SIZE; y++) {
            if (a[x][y] > largeNum) {
                largeNum = a[x][y];
            }
        }
    }
	
    return largeNum;
}

void doubleVals(int a[][SIZE]) {
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
			//a[x][y] = a[x][y]*2;	
			a[x][y] = a[x][y] << 1;
}

void initialize(int a[][SIZE]) {
	for(int x=0; x<SIZE; x++) {
		for(int y=0; y<SIZE; y++) {
			a[x][y] = x-y;	
        }
    }
}

int main() {
	static int a[SIZE][SIZE];
	int large;

	initialize(a);
	doubleVals(a);
	large = findLargest(a);	
	printf("%d\n",large); 

	return 0;
}
