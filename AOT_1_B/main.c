#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ROWS 1000


int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main() {
    
    FILE* fPtr = fopen("input.txt", "r");

    if(fPtr == NULL) {
        printf("Could not open file for read");
        fclose(fPtr);
    }

    int arr1[MAX_ROWS], arr2[MAX_ROWS];
    int arr1Index = 0, arr2Index = 0;

    int num;
    int counter = 0;
    int sum = 0;

    while (fscanf(fPtr, "%d", &num) == 1) {
        if(counter % 2 == 0) {
            arr1[arr1Index++] = num;
        } else {
            arr2[arr2Index++] = num;
        } 
        counter++;
    }

    for(int i=0; i<MAX_ROWS; i++) {
        int occurences = 0;
        for(int j=0; j<MAX_ROWS; j++) {
            if(arr1[i] == arr2[j]) {
                occurences++;
            }
        }
        sum += arr1[i] * occurences;
    }

    printf("%d", sum);

    fclose(fPtr);

    return 0;
}

