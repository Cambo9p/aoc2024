#include <stdio.h>
#include <stdlib.h>

//#include "../include/lib.h"

#define NUM_LINES 1000

int start_parse(char* buffer);

int parse_2(char *buffer, int *swap);

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
    int swap = 0;

    while (*buffer != '\0') {
        sum += parse_2(buffer, &swap);
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

// part two 

// 1 if we are skipping 
// 0 if nothing
// -1 if we hit a do
// i gave up writing this nicely
int parse_d(char*buffer, int* swap) {
    int mul_len = 2;
    char check[] = "do";
    int sec_len = 5;
    char sec[] = "n't()";

    for (int i = 0; i < mul_len; i++) {
        if (buffer[0] != check[i]) {
            return 0;
        }
        buffer++;
    }
    
    switch (*buffer) {
        case '(':
            return ++*buffer == ')' ? -1 : 0;
        case 'n':
            for (int i = 0; i < sec_len; i++) {
                if (buffer[0] != sec[i]) {
                    return 0;
                }
                buffer++;
            }
            return 1;
        default:
            return 0;
            break;
    }
}

int parse_2(char *buffer, int *swap) {
    int tmp = 0;

    switch (*buffer) {
        case 'm':
            if (*swap == 0 || *swap == -1) {
               int test = start_parse(buffer);
               return test;
            }
            break;
        case 'd':
            tmp = parse_d(buffer, swap);
            if (tmp != 0) {
                *swap = tmp;
            }
            break;
    }
    return 0;
}
