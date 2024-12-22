#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_MATCHES 1000 // Maximum number of matches
#define MAX_GROUPS 2   // 1 group for the full match, 1 group for capturing the number

void find_matches(const char *regex_pattern, const char *input, char **matches, int *match_count) {
    regex_t regex;
    regmatch_t match[MAX_GROUPS]; // Array to store full match and capturing group
    int start_offset = 0;         // Offset to start searching
    int ret;

    // Compile the regex
    if (regcomp(&regex, regex_pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    *match_count = 0;
    while (*match_count < MAX_MATCHES && (ret = regexec(&regex, input + start_offset, MAX_GROUPS, match, 0)) == 0) {
        // Check if capturing group matched
        if (match[1].rm_so != -1) {
            int start = match[1].rm_so + start_offset; // Start of capturing group
            int end = match[1].rm_eo + start_offset;   // End of capturing group
            int length = end - start;

            matches[*match_count] = (char *)malloc(length + 1);
            strncpy(matches[*match_count], input + start, length);
            matches[*match_count][length] = '\0';

            (*match_count)++;
        }

        // Move offset forward to search for the next match
        start_offset += match[0].rm_eo;
    }

    regfree(&regex);
}

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

    const char *regex_pattern = "([a-z]+),";
    char *matches[MAX_MATCHES];
    int match_count = 0;

    find_matches(regex_pattern, buffer, matches, &match_count);

    const char *regex_pattern2 = "#([a-z]+)";
    char *matches2[MAX_MATCHES];
    int match_count2 = 0;

    find_matches(regex_pattern2, buffer, matches2, &match_count2);

    int sum;

    printf("Sum: %d", sum);

    return 0;
}


bool findCombination(char * towel, char* patterns)