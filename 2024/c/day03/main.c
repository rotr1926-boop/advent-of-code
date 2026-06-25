#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_mul(const char *s, int *x, int *y) {
    if (strncmp(s, "mul(", 4) != 0) return 0;

    int i = 4;
    char num1[4] = {0}, num2[4] = {0};
    int j = 0;

    while (isdigit(s[i]) && j < 3) num1[j++] = s[i++];
    if (j == 0 || s[i] != ',') return 0;
    i++;

    j = 0;
    while (isdigit(s[i]) && j < 3) num2[j++] = s[i++];
    if (j == 0 || s[i] != ')') return 0;

    *x = atoi(num1);
    *y = atoi(num2);
    return 1;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        perror("Errore apertura file");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    long long sum_part1 = 0;
    long long sum_part2 = 0;
    int enabled = 1;

    for (size_t i = 0; buffer[i]; i++) {
        if (strncmp(&buffer[i], "do()", 4) == 0) {
            enabled = 1;
            i += 3;
        } else if (strncmp(&buffer[i], "don't()", 7) == 0) {
            enabled = 0;
            i += 6;
        } else if (strncmp(&buffer[i], "mul(", 4) == 0) {
            int x, y;
            if (is_valid_mul(&buffer[i], &x, &y)) {
                sum_part1 += x * y;
                if (enabled) sum_part2 += x * y;
            }
        }
    }

    printf("Part 1: %lld\n", sum_part1);
    printf("Part 2: %lld\n", sum_part2);

    free(buffer);
    return 0;
}
