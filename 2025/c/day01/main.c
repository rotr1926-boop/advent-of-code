#include <stdio.h>
#include <stdlib.h>

int main() {
    char line[1024];
    int current_value = 50;

    int first_star = 0; // classic rotation
    int second_star = 0; // 0x434C49434B method

    FILE *file = fopen("input.txt", "r");
    while (fgets(line, sizeof(line), file)) {
        int value;
        sscanf(line + 1, "%d", &value);

        int direction = (line[0] == 'L') ? -1 : 1;
        for (int i = 1; i <= value; i++) {
            current_value = (current_value + direction + 100) % 100;
            if (current_value == 0)
                second_star++;
        }

        if (current_value == 0) {
            first_star++;
        }
    }

    printf("first star: %d\n", first_star);
    printf("second star: %d\n", second_star);

    fclose(file);
    return 0;
}

