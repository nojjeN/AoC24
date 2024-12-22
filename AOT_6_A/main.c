#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ROW_COL_COUNT 130

int calculatePath(char* buffer);
bool isDirection(char c);
char getNextDirection(char c);
int moveInDirection(char* buffer, char direction, int x, int y);
bool contains(int arr[], int size, int value);



int main() {
    FILE* file = fopen("input.txt", "r");


    char directions[] = {'>', '<', 'v', '^'};
    char* buffer = 0;

    if (file) {
        fseek (file, 0, SEEK_END);
        int length = ftell (file);

        fseek (file, 0, SEEK_SET);
        buffer = malloc (length);

        if (buffer) {
            fread (buffer, sizeof(char), length, file);
        }
        
        fclose(file);
    }

    int sum = calculatePath(buffer);

    printf("Sum: %d", sum);
    printf("\n");


    for(int i=0; i<ROW_COL_COUNT; i++) {
        for(int j=0; j<ROW_COL_COUNT; j++) {
            printf("%c ", buffer[i*ROW_COL_COUNT+j]);
        }
        printf("\n");
    }

    return 0;
}

int calculatePath(char* buffer) {
    for (int y=0; y<ROW_COL_COUNT; y++) {
        for (int x=0; x<ROW_COL_COUNT; x++) {
            if(isDirection(buffer[y*ROW_COL_COUNT+x])) {
                printf("Pos: %d, %d\n", x, y);
                return moveInDirection(buffer, '^', x, y);
            } 
        }
    }
}

bool isDirection(char c) {
    return c == '^' || c == 'v' || c == '>' || c == '<';
}

char getNextDirection(char c) {
    switch(c) {
        case '^':
            return '>';
        case '>' :
            return 'v';
        case 'v':
            return '<';
        case '<':
            return '^'; 
    }
}

int moveInDirection(char* buffer, char direction, int x, int y) {

    int xModifier = x, yModifier = y;
    int xPrevious, yPrevious;
    char newDirection = direction;
    int newPosition = y*ROW_COL_COUNT+x;
    int visitedSquares[ROW_COL_COUNT*ROW_COL_COUNT];

    int count = 0;

    visitedSquares[count++] = newPosition;
    buffer[newPosition] = newDirection;

    while (xModifier >= 0 && yModifier >= 0 && xModifier < ROW_COL_COUNT && yModifier < ROW_COL_COUNT) {
        xPrevious = xModifier;
        yPrevious = yModifier;

        if(newDirection == '^') {
            yModifier += -1;
        } else if(newDirection == '>') {
            xModifier += 1;
        } else if(newDirection == 'v') {
            yModifier += 1;
        } else if(newDirection == '<') {
            xModifier += -1;
        }



        //printf("Pos: %d, %d, %d, %d %c\n", x, y, xModifier, yModifier, buffer[(y+yModifier)*ROW_COL_COUNT+(x+xModifier)]);
        if(buffer[(yModifier)*ROW_COL_COUNT+(xModifier)] == '#') {
            newDirection  = getNextDirection(newDirection);
            xModifier = xPrevious;
            yModifier = yPrevious;
            //printf("Found #, standing at pos:%d\n", newPosition);

            //printf("new Dir\n");
        } else {
            newPosition = (yModifier)*ROW_COL_COUNT+(xModifier);

            if(!contains(visitedSquares, ROW_COL_COUNT*ROW_COL_COUNT, newPosition) && (xModifier >= 0 && yModifier >= 0 && xModifier < ROW_COL_COUNT && yModifier < ROW_COL_COUNT)) {

                
                visitedSquares[count] = newPosition;
                count++;
                //printf("Count:%d\n", count);
                //buffer[newPosition] = (count % 10) + '0';
                buffer[newPosition] = newDirection;

            }
        }
    }
    return count;
}

bool contains(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true; 
        }
    }
    return false; 
}