#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/lib.h"

#define BUFSIZE 1000000
#define NUM_LINES 1000


void solve_d1(char* buffer, size_t len);
void walk_string(char* buffer);
void create_sorted_lists(char *buffer, int* val1, int* val2);

void solve_p1(char* buffer, size_t len) {
    int* val1 = malloc(sizeof(int) * NUM_LINES);
    int* val2 = malloc(sizeof(int) * NUM_LINES);

    create_sorted_lists(buffer, val1, val2);

    int sum = 0;
    for (int j = 0; j < NUM_LINES; j++) {
        sum += abs(val1[j] - val2[j]);
    }

    printf("the ans is %d\n", sum);

    free(val1);
    free(val2);
}

void solve_p2(char* buffer, size_t len) {
    int* val1 = malloc(sizeof(int) * NUM_LINES);
    int* val2 = malloc(sizeof(int) * NUM_LINES);

    create_sorted_lists(buffer, val1, val2);

    int sum = 0;
    // calc distances
    for (int j = 0; j < NUM_LINES; j++) {
        sum += num_occurances(val2, NUM_LINES, val1[j]) * val1[j];
    }

    printf("the ans is %d\n", sum);

    free(val1);
    free(val2);
}

void create_sorted_lists(char *buffer, int* val1, int* val2) {
    long val;
    for (int i = 0; i <NUM_LINES * 2; i++) {
        val = strtol(buffer, &buffer, 10);

        if (i % 2 == 0) {
            val1[i / 2] = val;
        } else {
            val2[i / 2] = val;
        }
        walk_string(buffer);
    }

    quicksort(val1, 0, NUM_LINES - 1);
    quicksort(val2, 0, NUM_LINES - 1);
}

