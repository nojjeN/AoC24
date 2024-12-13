#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WIDTH_HEIGHT 140

int checkXmasFromCell(char (*arr)[MAX_WIDTH_HEIGHT], int row, int column);
bool checkArrIfMas(char * arr);

int main() {

    FILE* file = fopen("input.txt", "r");

    if(file == NULL) {
        printf("ERROR READING FILE");
        return 1;
    }

    char arr[MAX_WIDTH_HEIGHT][MAX_WIDTH_HEIGHT];
    int sum = 0;

    for (int i = 0; i < MAX_WIDTH_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH_HEIGHT; j++) {
            char ch = fgetc(file);
            if (ch == EOF || ch == '\n') {
                fprintf(stderr, "Unexpected file format or end of file.\n");
                fclose(file);
                return 1;
            }
            arr[i][j] = ch;
        }
        fgetc(file);
    }

    fclose(file);
    
    for (int i=0; i<MAX_WIDTH_HEIGHT; i++) {
        for (int j=0; j<MAX_WIDTH_HEIGHT; j++) {
            if(arr[i][j] == 'A') {
                sum += checkXmasFromCell(arr, i, j);
            }
        }
    }

    printf("%d", sum);

    return 0;
}

int checkXmasFromCell(char (*arr)[MAX_WIDTH_HEIGHT], int row, int column) {
    int occurences = 0;

    char arrToTest1[2];
    char arrToTest2[2];


    if(row-1 >= 0 && column-1 >=0 && column + 1 < MAX_WIDTH_HEIGHT && row + 1 < MAX_WIDTH_HEIGHT) {
        arrToTest1[0] = arr[row-1][column-1];
        arrToTest1[1] = arr[row+1][column+1];

        arrToTest2[0] = arr[row-1][column+1];
        arrToTest2[1] = arr[row+1][column-1];

        occurences += checkArrIfMas(arrToTest1) && checkArrIfMas(arrToTest2);
    }

    return occurences;
}

bool checkArrIfMas(char * arr) {
    return arr[0] != arr[1] && (arr[0] == 'M' || arr[0] == 'S') && (arr[1] == 'M' || arr[1] == 'S');
}