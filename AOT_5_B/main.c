#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RULE_COUNT 1176
#define ROW_COUNT 201
#define ROW_MAX_WIDTH 25

bool checkAgainstRules(int* row, int* rules);
int getMiddleNumber(int* row);

int main() {
    FILE* file1 = fopen("input.txt", "r");
    FILE* file2 = fopen("input2.txt", "r");


    if(file1 == NULL || file2 == NULL) {
        printf("Error");
        return 1;
    }

    int constraints[RULE_COUNT*2];
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
    int arr[ROW_COUNT][ROW_MAX_WIDTH] = {0};


    while (fgets(line, 100, file2) != NULL && idx < ROW_COUNT) {
        token = strtok(line, ",");
        int counter = 0;

        while (token != NULL && counter < ROW_MAX_WIDTH) {

            arr[idx][counter++] = atoi(token);
            token = strtok(NULL, ",");
        }
        idx++;
    }

    int sum = 0;


    for(int i=0; i<ROW_COUNT; i++) {
        if(!checkAgainstRules(arr[i], constraints)) {
            while(!checkAgainstRules(arr[i], constraints));

            sum += getMiddleNumber(arr[i]);
        }
    }
    printf("Sum: %d", sum);
    return 0;
}


bool checkAgainstRules(int* row, int* rules) {
    for(int i=0; i<ROW_MAX_WIDTH; i++) {
        if(row[i] == 0 || row[i+1] == 0) {
            return true;
        }
        for (int j=0; j<RULE_COUNT*2; j+=2) {
            if(row[i] == rules[j+1] && row[i+1] == rules[j]) {
                int tmp = row[i];
                row[i] = row[i+1];
                row[i+1] = tmp;
                return false;
            }
        }
    }
    return true;
}

int getMiddleNumber(int* row) {
    for (int i=0; i<ROW_MAX_WIDTH; i++) {
        if(row[i] == 0) {
            return row[(i-1)/2];
        }
    }
}