#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_arr(int size, int* arr) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

// returns len of array
int init_array( long long *arr, char *s) {
    char *saveptr;

    char *token = strtok_r(s, " ", &saveptr);
    
    int i = 0;
    while (token != NULL) {
        char* endptr;
        arr[i] = strtol(token, &endptr, 10);
        i++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    return i;
}

// copies elements from arr1 into arr2 excluding the first one
// len: size of arr1
void remove_head(long long *arr1, long long *arr2, int len) {
    for (int i = 0; i < len - 1; i++) {
        arr2[i] = arr1[i + 1];
    }
}

// recustion boi
// we are doing this backwards so i dont need to reallocate some memory
// e.g 1 4 6 will get split into two calls 6 + ( 1 4 ) and 6 * ( 1 4 )
// and if one gets the answer we will return true
int evaluate_line( long long *arr, int size,  long long goal) {
    if (size == 1) {
        return arr[0] == goal; 
    }

    int tmp = arr[0]; // head of the array
                      
     long long *add_arr = ( long long *)calloc(size - 1,sizeof( long long));
     long long *mul_arr = ( long long *)calloc(size - 1,sizeof( long long));

    remove_head(arr, add_arr, size);
    remove_head(arr, mul_arr, size);

    add_arr[0] = tmp + add_arr[0];
    mul_arr[0] = tmp * mul_arr[0];
    //printf("test\n");
    //print_arr(size - 1, mul_arr);
    //print_arr(size - 1, add_arr);

    int add = evaluate_line(add_arr, size - 1, goal);
    int mul = evaluate_line(mul_arr, size - 1, goal);
    free(add_arr);
    free(mul_arr);

    return mul || add;
}

long long process_line(char* line) {
    printf("processing line: %s\n", line);

    char *endptr;
     long long tmp[20];
    //int count = 0; // items in arr

     long long goal = strtol(line, &endptr, 10);

    endptr+=2; // remove space and :

    int len = init_array(tmp, endptr);
     long long *arr = ( long long*)calloc(len, sizeof( long long));

    for (int i = 0; i < len; i++) {
        arr[i] = tmp[i];
        printf("%lld ", arr[i]);
    }
    printf("\n");

    int worked = evaluate_line(arr, len, goal); 
    free(arr);

    return worked ? goal : 0;
}

void solve_p1(char* buffer, long long len) {
    char *save_ptr;
    char * token;
    long long sum = 0;

    token = strtok_r(buffer, "\n", &save_ptr);

    while (token != NULL) {
        sum += process_line(token);

        token = strtok_r(NULL, "\n", &save_ptr);
    }

    printf("\nThe ans is %lld\n", sum);
    
}
