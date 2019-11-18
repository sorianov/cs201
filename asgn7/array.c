
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
	for(int y=0; y<SIZE; y++) {
		for(int x=0; x<SIZE; x+=10) {
			a[x][y] = x-y;	
			a[x+1][y] = (x+1)-y;	
			a[x+2][y] = (x+2)-y;	
			a[x+3][y] = (x+3)-y;	
			a[x+4][y] = (x+4)-y;	
			a[x+5][y] = (x+5)-y;	
			a[x+6][y] = (x+6)-y;	
			a[x+7][y] = (x+7)-y;	
			a[x+8][y] = (x+8)-y;	
			a[x+9][y] = (x+9)-y;	
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
