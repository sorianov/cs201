
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
    register double sum = 0;
    register double sum2 = 0;
    register double sum3 = 0;
    register double sum4 = 0;
    register const size_t limit = ARR_SIZE - 3;
    register size_t i;
    for (i = 0; i < limit; i+=4) {
        sum += a[i];
        sum2 += a[i+1];
        sum3 += a[i+2];
        sum4 += a[i+3];
    }
    for (;i < ARR_SIZE;++i) {
        sum += a[i];
    }
    return sum + (sum2 + (sum3 + sum4));
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
