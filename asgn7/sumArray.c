
/* ***********************************************************
 Name: sumArray.c
 Desc: Assignment 7 - Sums up array elements numerous times

	Students will modify sumArray routine to improve 
	performance.

 Compile 
	gcc -m32 -std=gnu99 -Wall -g sumArray.c -o sumArray

 Time execution:
	time sumArray

************************************************************* */


#include <stdio.h>
#include <stdlib.h>

#define NUM_TIMES 50000
#define ARR_SIZE  100000

double sumArray(double a[]) {
    register int size = ARR_SIZE;
    register double sum = 0;
for (register int i = 0; i < size; i+=20) {
sum += a[i]+a[i+1]+a[i+2]+a[i+3]+a[i+4]+a[i+5]+a[i+6]+a[i+7]+a[i+8]+a[i+9];
sum += a[i+10]+a[i+11]+a[i+12]+a[i+13]+a[i+14]+a[i+15]+a[i+16]+a[i+17]+a[i+18]+a[i+19];
}
    return sum;
}

int main() {
	//print your name
	printf("Victor Soriano Mendoza\n");

	//create and initialize array
	double *array = calloc(ARR_SIZE, sizeof(double));

	array[0]=5;
	array[ARR_SIZE-1]=4;

	//sum up array elements a bunch of times (once is too fast)
	double sum;
	for(int n=0; n<NUM_TIMES; n++) {
		sum=sumArray(array);
	}

	/* print out total to verfiy we processed all entries */
	printf("sum: %lf\n", sum);

	return 1;
}
