#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "d4.c"

#define BUFSIZE 1000000

size_t read_file(char* filename, int buffsize, char *buffer);

int main() {
    char *filename = "input.txt";
    char *buffer = (char*)malloc(sizeof(char) * BUFSIZE);

    size_t len = read_file(filename, BUFSIZE, buffer);

    solve_p1(buffer, len);

    free(buffer);
    return 0;
}

// reads file into buffer
size_t read_file(char* filename, int buffsize, char *buffer) {
    size_t ret;
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("fopen");
    }

    ret = fread(buffer, sizeof(char), BUFSIZE, fp);

    buffer[ret] = '\0';

    fclose(fp);
    return ret;
}
