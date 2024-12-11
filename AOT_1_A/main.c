#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Comparison function
int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}


int main() {
    
    FILE* fPtr = fopen("input.txt", "r");

    if(fPtr == NULL) {
        printf("Could not open file for read");
        fclose(fPtr);
    }

    int arr1[1000], arr2[1000];

    int arr1Index = 0, arr2Index = 0;

    int num;
    int counter = 0;
    int sum = 0;

    while (fscanf(fPtr, "%d", &num) == 1)
    {
        printf("Index:%d, num:%d\n", counter, num);

        if(counter % 2 == 0) {
            arr1[arr1Index++] = num;
        } else {
            arr2[arr2Index++] = num;
        } 
        counter++;
    }

    qsort(arr1, 1000, sizeof(int), compare);
    qsort(arr2, 1000, sizeof(int), compare);



    for(int i=0; i<1000; i++) {
        sum += abs(arr1[i] - arr2[i]);
    }
 

    printf("%d", sum);

    fclose(fPtr);

    return 0;
}

