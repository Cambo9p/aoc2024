#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/lib.h"

#define NUM_LINES 1000

int is_safe(int* vals, int len, int skipped);
int check_difference(int a, int b);

void walk_(char* buffer) {
    while (*buffer != '\0' && !isdigit(*buffer)) {
        printf("in");
        buffer++;
    }
}

void solve_p1(char* buffer, size_t len) {
    int num_safe = 0;
    long val;
    for (int i = 0; i < NUM_LINES; i++) {
        int j = 0; // curr index
        int* line = malloc(sizeof(int) * 8);
                   
        while (*buffer != '\0' && *buffer != '\n') {
            val = strtol(buffer, &buffer, 10);
            //printf("%ld\n", val);
            line[j] = val;
            walk_string(buffer);
            j++;
        }

        if (is_safe(line, j, 1)) {
            num_safe++;
        }

        if (*buffer == '\n') { 
            buffer++;
        }

        free(line);
    }
    printf("%d\n", num_safe);

}

void solve_p2(char* buffer, size_t len) {
    int num_safe = 0;
    long val;
    for (int i = 0; i < NUM_LINES; i++) {
        int j = 0; // curr index
        int* line = malloc(sizeof(int) * 8);
                   
        while (*buffer != '\0' && *buffer != '\n') {
            val = strtol(buffer, &buffer, 10);
            line[j] = val;
            walk_string(buffer);
            j++;
        }

        if (is_safe(line, j, 0)) {
            num_safe++;
        }

        if (*buffer == '\n') { 
            buffer++;
        }
    }
    printf("%d\n", num_safe);
}

int is_safe(int* vals, int len, int skipped) {
    printf("checking safe: ");
    for (int j = 0; j < len; j++) {
        printf("%d ", vals[j]);
    }
    int increasing = (vals[1] > vals[0]);

    for (int i = 1; i < len; i++) {
        int diff = vals[i] - vals[i - 1];

        if ((abs(diff) < 1 || abs(diff) > 3) || (increasing && diff < 0) || (!increasing && diff > 0)) {
            printf("between %d and %d\n", vals[i - 1], vals[i]);
            if (!skipped) {
                remove_element(vals, i, len);
                return is_safe(vals, len - 1, 1);
            }
            return 0;
        }
    }

    printf("safe\n");
    return 1;
}

int check_difference(int a, int b) {
    if (abs(a - b) < 1 || abs(a - b) > 3) {
        printf("difference wrong %d %d\n", a, b);
        return 0;
    }
    return 1;
}


