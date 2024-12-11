#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


bool followsRules(int current, int previous, bool asc);
bool checkArray(int* arr, int size);

int main() {

    FILE* file = fopen("input.txt", "r");

    char line[100];
    char* token;
    int safeCounter = 0;

    while (fgets(line, 100, file) != NULL) {
        token = strtok(line, " ");
        int arr[10] = {0};
        int counter = 0;

        while (token != NULL) {
            arr[counter++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if(checkArray(arr, counter)) {
            safeCounter++;
        }
    }

    printf("Safecounter = %d", safeCounter);

    return 0;
}

bool followsRules(int current, int previous, bool asc) {
    return 1 <= abs(current - previous) && 
           abs(current - previous) <= 3 && 
           ((asc && current > previous) || (!asc && current < previous));
}

bool checkArray(int* arr, int size) {
    int prevNum = -1;
    int asc = -1;

    for (int i=0; i<size; i++) {
        if(prevNum == -1) {
            prevNum = arr[i];
            continue;
        }

        if(asc == -1) {
            asc = prevNum < arr[i];

        } 

        if(followsRules(arr[i], prevNum, asc)) {
            prevNum = arr[i];
        } else {
            return 0;
        }
    }
    return 1;
}