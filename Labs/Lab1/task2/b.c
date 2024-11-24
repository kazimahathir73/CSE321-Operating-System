#include <stdio.h>
#include <string.h>

int main() {
    FILE *input, *output;
    char s[200];

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    char *word = strtok(s, " ");
    while (token != NULL) {
        fputs(token, output);
        fputc(' ', output);
        token = strtok(NULL, " ");
    }

    fclose(input);
    fclose(output);

    return 0;
}
