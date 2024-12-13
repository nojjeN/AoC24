#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int getNumericalMatch(regmatch_t* matches, const char* cursor, int groupIndex);

int main() {

    FILE* file = fopen("input.txt", "r");

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

    if (buffer) {
        int sum = 0;

        regex_t regex;
        regmatch_t matches[300];

        int returnInt = regcomp(&regex, "do\\(\\).*?(mul\\(([0-9]{1,3}),([0-9]{1,3})\\))+", REG_EXTENDED);
        int returnInt = regcomp(&regex, "don't\\(\\).*?(mul\\(([0-9]{1,3}),([0-9]{1,3})\\))+", REG_EXTENDED);


        if (returnInt) {
            printf("Regex failed\n");
            return 1;
        }

        const char *cursor = buffer;

        while (regexec(&regex, cursor, 10, matches, 0) == 0) {
            sum += getNumericalMatch(matches, cursor, 1) * getNumericalMatch(matches, cursor, 2);
            cursor += matches[0].rm_eo;
        }
        printf("%d", sum);
    }

    free(buffer);
    return 0;
}

int getNumericalMatch(regmatch_t* matches, const char* cursor, int groupIndex) {
    int start = matches[groupIndex].rm_so;
    int length = matches[groupIndex].rm_eo - matches[groupIndex].rm_so;

    char match[length + 1]; // +1 for null terminator
    strncpy(match, cursor + start, length);
    match[length] = '\0'; // Null-terminate the string

    return atoi(match);
}