#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_line(const char *line, int *numbers) {
    int count = 0;
    while (*line) {
        if (*line >= '0' && *line <= '9') {
            numbers[count] = strtol(line, (char**)&line, 10);
            count++;
        } else {
            line++;
        }
    }
    return count;
}

int is_valid(int *arr, int len) {
    int dir = 0;

    for (int i = 0; i < len - 1; i++) {
        int d = arr[i] - arr[i + 1];
        if (d == 0 || abs(d) > 3) return 0;

        int current_dir = (d > 0) ? 1 : -1;

        if (dir == 0) {
            dir = current_dir;
        } else if (dir != current_dir) {
            return 0;
        }
    }

    return 1;
}

int valid_with_one_removed(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        int temp[64], k = 0;
        for (int j = 0; j < len; j++) {
            if (j != i) temp[k++] = arr[j];
        }
        if (is_valid(temp, k)) return 1;
    }
    return 0;
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        printf("Il file non esiste\n");
        return 1;
    }

    char line[256];
    int part1 = 0, part2 = 0;
    int arr[64];

    while (fgets(line, sizeof(line), f)) {
        int n = parse_line(line, arr);
        if (is_valid(arr, n)) part1++;
        if (valid_with_one_removed(arr, n) || is_valid(arr, n)) part2++;
    }

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);

    fclose(f);
    return 0;
}
