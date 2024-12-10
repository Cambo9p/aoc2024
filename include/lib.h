#ifndef LIB_H
#define LIB_H

void quicksort(int *x, int l, int r);

int num_occurances(int* arr, int len, int x);

// moves forward in the string  as long as 
// the current char is not a digit
void walk_string(char* buffer);

// removes a val from the array and cascades
void remove_element(int *vals, int i, int len);

#endif
