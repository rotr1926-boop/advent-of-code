#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool is_invalid_first_star(unsigned long long num) {
    // 32 characters array (stack memory)
    char str[32];
    // convert number to string
    sprintf(str, "%llu", num);

    int len = strlen(str);
    if (len % 2 != 0) return false;
    int half = len / 2;

    for (int i = 0; i < half; i++) {
        if (str[i] != str[half + i]) {
            return false;
        }
    }

    return true;
}

bool is_invalid_second_star(unsigned long long num) {
    char str[32];
    sprintf(str, "%llu", num);
    int len = strlen(str);

    for (int pattern_len = 1; pattern_len <= len / 2; pattern_len++) {
        if (len % pattern_len != 0) continue;

        bool is_repeated = true;
        for (int i = 0; i < len; i++) {
            if (str[i] != str[i % pattern_len]) {
                is_repeated = false;
                break;
            }
        }

        if (is_repeated) return true;
    }

    return false;
}

int main() {
    char line[1024];
    unsigned long long first_star = 0;
    unsigned long long second_star = 0;

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error, no file"); 
        return 1; 
    }

    // reading file line bt line
    while (fgets(line, sizeof(line), file)) {
        // remove the '\n' and sets that into the null temrinator '\0'
        line[strcspn(line, "\n")] = 0;
        // pointer to walk through the string
        char *ptr = line;

        // when ptr = '\0' we know that the line is finished
        while (*ptr) {
            while (*ptr == ' ') ptr++;
            if (!*ptr) break;

            char *start_str = ptr;
            while (*ptr && *ptr != '-') ptr++;
            if (!*ptr) break;
            *ptr = 0;
            ptr++;

            char *end_str = ptr;
            while (*ptr && *ptr != ',') ptr++;
            bool has_more = (*ptr == ',');
            if (*ptr) {
                *ptr = 0;
                ptr++;
            }

            uint64_t start = strtoull(start_str, NULL, 10);
            uint64_t end = strtoull(end_str, NULL, 10);

            for (uint64_t num = start; num <= end; num++) {
                if (is_invalid_first_star(num)) {
                    first_star += num;
                }
            }

            for (uint64_t num = start; num <= end; num++) {
                if (is_invalid_second_star(num)) {
                    second_star += num;
                }
            }

            if (!has_more) break;
        }
    }

    printf("first star: %llu\n", first_star);
    printf("second star: %llu\n", second_star);

    fclose(file);
    return 0;
}
