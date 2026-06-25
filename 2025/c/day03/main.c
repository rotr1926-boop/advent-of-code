#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void first_star() {
    FILE *file = fopen("input.txt", "r");
    char lines[256]; 
    int numbers[1024];
    int aa = 0;
    while (fgets(lines, sizeof(lines), file)) {
        int len = strlen(lines);
        int max = -1;

        for (int i = 0; i < len; i++) {
            if (lines[i] == '\n') break;
            int a = lines[i] - '0';

            for (int j = i + 1; j < len; j++) {
                if (lines[j] == '\n') break;
                int b = lines[j] - '0';
                int current = a * 10 + b;
                if (current > max) {
                    max = current;
                }
            }
        }
        numbers[aa++] = max;
    }

    int result = 0;
    for (int i = 0; i < aa; i++) {
        result += numbers[i];
    }

    printf("%d\n", result);
    fclose(file);
}

void second_star() {
    FILE *file = fopen("input.txt", "r");
    char lines[256]; 
    unsigned long long result = 0;

    while (fgets(lines, sizeof(lines), file)) {
        int len = strlen(lines);
        if (lines[len - 1] == '\n') len--;

        char numbers[13] = { 0 };
        int start = 0;

        for (int i = 0; i < 12; i++) {
            int end = len - (12 - i - 1);
            int max = -1;
            int bp = start;

            for (int j = start; j < end; j++) {
                int d = lines[j] - '0';
                if (d > max) {
                    max = d;
                    bp = j;
                }
            }

            numbers[i] = '0' + max;
            start = bp + 1;
        }

        unsigned long long x = strtoull(numbers, NULL, 10);
        result += x;
    }

    printf("%llu\n", result);
    fclose(file);
}

int main() {
    first_star();
    second_star();

    return 0;
}
