#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file1 = fopen("input.txt", "r");
    FILE* file2 = fopen("input2.txt", "r");


    if(file1 == NULL || file2 == NULL) {
        printf("Error");
        return 1;
    }

    int constraints[2352];
    int index = 0;
    char buffer[10];

    while (fgets(buffer, sizeof(buffer), file1) != NULL) {
        if (strlen(buffer) == 1 && buffer[0] == '\n') {
            break;
        }
        sscanf(buffer, "%d|%d", &constraints[index], &constraints[index+1]);
        index += 2;
    }

    char line[100];
    char* token;
    int idx = 0;
    int arr[201][25];


    while (fgets(line, 100, file2) != NULL && idx < 201) {
        token = strtok(line, ",");
        int counter = 0;

        while (token != NULL && counter < 25) {

            arr[idx][counter++] = atoi(token);
            token = strtok(NULL, ",");
        }
        idx++;
    }

    for(int i=0; i<201; i++) {
        for(int j=0; j<25; j++) {
            if(arr[i][j] == 0) {
                break;
            }
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


    return 0;
}