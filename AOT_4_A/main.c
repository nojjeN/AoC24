#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WIDTH_HEIGHT 140

int checkXmasFromCell(char (*arr)[MAX_WIDTH_HEIGHT], int row, int column);
bool checkArrIfXmas(char * arr, int row, int col);

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
            if (ch == EOF || ch == '\n') { // Handle unexpected EOF or newline in the middle
                fprintf(stderr, "Unexpected file format or end of file.\n");
                fclose(file);
                return 1;
            }
            arr[i][j] = ch;
        }
        fgetc(file); // Skip the newline character after each row
    }

    fclose(file);


        printf("1:%s\n", arr[1]);
        printf("2:%s\n", arr[2]);
        printf("3:%s\n", arr[3]);
        printf("4:%s\n", arr[4]);

    
    for (int i=0; i<MAX_WIDTH_HEIGHT; i++) {
        for (int j=0; j<MAX_WIDTH_HEIGHT; j++) {
            if(arr[i][j] == 'X') {
                sum += checkXmasFromCell(arr, i, j);
            }
        }
    }

    printf("%d", sum);

    return 0;
}



//MMMSXXMASM
//MSAMXMSMSA
//AMXSXMAAMM
//MSAMASMSMX

int checkXmasFromCell(char (*arr)[MAX_WIDTH_HEIGHT], int row, int column) {
    int occurences = 0;

    char arrToTest[3];
    if(row - 3 >= 0) {
        arrToTest[0] = arr[row-1][column];
        arrToTest[1] = arr[row-2][column];
        arrToTest[2] = arr[row-3][column];
        occurences += checkArrIfXmas(arrToTest, row, column);

        if(column - 3 >= 0) {
            arrToTest[0] = arr[row-1][column-1];
            arrToTest[1] = arr[row-2][column-2];
            arrToTest[2] = arr[row-3][column-3];
            occurences += checkArrIfXmas(arrToTest, row, column);

        }
        if(column + 3 < MAX_WIDTH_HEIGHT) {
            arrToTest[0] = arr[row-1][column+1];
            arrToTest[1] = arr[row-2][column+2];
            arrToTest[2] = arr[row-3][column+3];
            occurences += checkArrIfXmas(arrToTest, row, column);
        }
    }
    if(row + 3 < MAX_WIDTH_HEIGHT) {
        arrToTest[0] = arr[row+1][column];
        arrToTest[1] = arr[row+2][column];
        arrToTest[2] = arr[row+3][column];

        occurences += checkArrIfXmas(arrToTest, row, column);

        if(column - 3 >= 0) {
            arrToTest[0] = arr[row+1][column-1];
            arrToTest[1] = arr[row+2][column-2];
            arrToTest[2] = arr[row+3][column-3];
            occurences += checkArrIfXmas(arrToTest, row, column);
        }
        if(column + 3 < MAX_WIDTH_HEIGHT) {
            arrToTest[0] = arr[row+1][column+1];
            arrToTest[1] = arr[row+2][column+2];
            arrToTest[2] = arr[row+3][column+3];
            occurences += checkArrIfXmas(arrToTest, row, column);
        }
    }

    if(column - 3 >= 0) {
        arrToTest[0] = arr[row][column-1];
        arrToTest[1] = arr[row][column-2];
        arrToTest[2] = arr[row][column-3];
        occurences += checkArrIfXmas(arrToTest, row, column);
    }

    if(column + 3 < MAX_WIDTH_HEIGHT) {
        arrToTest[0] = arr[row][column+1];
        arrToTest[1] = arr[row][column+2];
        arrToTest[2] = arr[row][column+3];
        occurences += checkArrIfXmas(arrToTest, row, column);
    }

    return occurences;
}

bool checkArrIfXmas(char * arr, int row, int col) {
    return arr[0] == 'M' && arr[1] == 'A' && arr[2] == 'S';
}