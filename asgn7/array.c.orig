
/* ***********************************************************
 Name: array.c
 Desc: Initialzies, manipulates, and finds largest value in a
        2-d array.

	Students will analyze with gprof and improve code.

************************************************************* */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int largest(int x, int y) {
	if (x>y)
		return x;
	else
		return y;
}

int findLargest(int a[][SIZE]) {
	int largeNum=a[0][0];
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
			largeNum = largest(largeNum, a[x][y]);	
	return largeNum;
}

void doubleVals(int a[][SIZE]) {
	for(int x=0; x<SIZE; x++)
		for(int y=0; y<SIZE; y++)
			a[x][y] = a[x][y]*2;	
}

void initialize(int a[][SIZE]) {
	for(int y=0; y<SIZE; y++)
		for(int x=0; x<SIZE; x++)
			a[x][y] = x-y;	
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
