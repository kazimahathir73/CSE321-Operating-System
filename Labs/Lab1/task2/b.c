#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *input, *output;
    char s[500];

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    char *word = strtok(s, " ");
    while (word != NULL) {
        fputs(word, output);
        word = strtok(NULL, " ");
        if (word != NULL) {
            fputc(' ', output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}
