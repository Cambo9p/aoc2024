#include <ctype.h>
int partition(int *x, int l, int r);
void swap(int *x, int p1, int p2);

int num_occurances(int* arr, int len, int x) {
    int c = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == x) {
            c++;
        }
    }

    return c;
}

// sorts an array of NUM_LINES length
void quicksort(int *x, int l, int r) {
    if (l < r) {
        int pivot = partition(x, l, r);
        quicksort(x, l, pivot - 1);
        quicksort(x, pivot + 1, r);
    }
}

int partition(int *x, int l, int r) {
    int pivot = x[r];
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (x[j] < pivot) {
            i++;
            swap(x, i, j);
        }
    }
    swap(x, i + 1, r);

    return i + 1;
}

void swap(int *x, int p1, int p2) {
    int tmp = x[p1];
    x[p1] = x[p2];
    x[p2] = tmp;
}

// walks string when not a digit
void walk_string(char* buffer) {
    while (*buffer != '\0' && !isdigit(*buffer) && *buffer != '\n') {
        buffer++;
    }
}

void remove_element(int *vals, int i, int len) {
    for (int j = i + 1; j < len; j++) {
        vals [j - 1] = vals[j];
    }
}
