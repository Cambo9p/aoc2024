#include <stdio.h>
#include <stdlib.h>

#include "../include/lib.h"

#define NUM_LINES 1000

int start_parse(char* buffer);


void solve_p1(char* buffer, size_t len) {
    int sum = 0;

    while (*buffer != '\0') {
        sum += start_parse(buffer);
        buffer++;
    }
    printf("sum = %d\n", sum);

}

void solve_p2(char* buffer, size_t len) {
    int sum = 0;

    while (*buffer != '\0') {
        sum += start_parse(buffer);
        buffer++;
    }
    printf("sum = %d\n", sum);

}

int start_parse(char* buffer) {
    long val1;
    long val2;
    int mul_len = 4;
    char mul[] = "mul(";

    for (int i = 0; i < mul_len; i++) {
        if (buffer[0] != mul[i]) {
            return 0;
        }
        buffer++;
    }

    val1 = strtol(buffer, &buffer, 10);
    if (*buffer++ != ',') {
        return 0;
    }
    val2 = strtol(buffer, &buffer, 10);
    if (*buffer++ != ')') {
        return 0;
    }
    return val1 * val2;
}

int parse_2(char *buffer) {
    switch (*buffer) {
        case 'm':
            break;
        case 'd':
            break;
    }
    return 0;
}
