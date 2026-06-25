#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Il file non esiste");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    rewind(file);

    char *buffer = malloc(file_length + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Errore allocazione memoria\n");
        return NULL;
    }

    fread(buffer, 1, file_length, file);
    buffer[file_length] = '\0';
    fclose(file);
    return buffer;
}

int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return ia - ib;
}

void parse_lists(const char *content, int **left, int *left_count, int **right, int *right_count) {
    int lines = 0;
    for (const char *p = content; *p; p++) {
        if (*p == '\n') lines++;
    }

    *left = malloc(lines * sizeof(int));
    *right = malloc(lines * sizeof(int));

    *left_count = 0;
    *right_count = 0;

    const char *line = content;
    char *next_line;
    while (line && *line) {
        char buffer[128];
        next_line = strchr(line, '\n');

        if (next_line) {
            size_t len = next_line - line;
            if (len >= sizeof(buffer)) len = sizeof(buffer) - 1;
            memcpy(buffer, line, len);
            buffer[len] = '\0';
            line = next_line + 1;
        } else {
            strncpy(buffer, line, sizeof(buffer));
            buffer[sizeof(buffer)-1] = '\0';
            line = NULL;
        }

        int lval, rval;
        if (sscanf(buffer, "%d %d", &lval, &rval) == 2) {
            (*left)[(*left_count)++] = lval;
            (*right)[(*right_count)++] = rval;
        }
    }
}

int solve_part1(const char *content) {
    int *left, *right;
    int left_count, right_count;
    parse_lists(content, &left, &left_count, &right, &right_count);

    qsort(left, left_count, sizeof(int), cmp_int);
    qsort(right, right_count, sizeof(int), cmp_int);

    int total_distance = 0;
    for (int i = 0; i < left_count && i < right_count; i++) {
        int diff = left[i] - right[i];
        if (diff < 0) diff = -diff;
        total_distance += diff;
    }

    free(left);
    free(right);
    return total_distance;
}

int solve_part2(const char *content) {
    int *left, *right;
    int left_count, right_count;
    parse_lists(content, &left, &left_count, &right, &right_count);

    int similarity_score = 0;
    for (int i = 0; i < left_count; i++) {
        int val = left[i];
        int count = 0;
        for (int j = 0; j < right_count; j++) {
            if (right[j] == val) count++;
        }
        similarity_score += val * count;
    }

    free(left);
    free(right);
    return similarity_score;
}

int main() {
    char *content = read_file("input.txt");

    printf("Part 1: %d\n", solve_part1(content));
    printf("Part 2: %d\n", solve_part2(content));

    free(content);
    return 0;
}
