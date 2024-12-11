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

        if(counter % 2 == 0) {
            arr1[arr1Index++] = num;
        } else {
            arr2[arr2Index++] = num;
        } 
        counter++;
    }

    int occurences = 0;
    for(int i=0; i<1000; i++) {
        for(int j=0; j<1000; j++) {
            if(arr1[i] == arr2[j]) {
                occurences++;
            }
        }
        sum += arr1[i] * occurences;
        occurences = 0;
    }

    printf("%d", sum);

    fclose(fPtr);

    return 0;
}

