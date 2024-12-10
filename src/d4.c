#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int len;
    int height;
} dim_t;

typedef struct {
    char* buffer;
    char* start;
} buf_t ;

char *xmas = "XMAS";
int xmas_len = 4;

void get_length(char* buffer, dim_t* dim) {
    int char_count = 0;
    
    while (*buffer != '\0') {
        if (*buffer == '\n') {
            dim->height += 1;
        } else {
            char_count++;
        }
        buffer++;
    }

    
    dim->len = char_count / dim->height;
}

// north
int check_n(buf_t* buf, dim_t* dim) {
    int pos = buf->buffer - buf->start;
    int lines_above = pos / dim->len + 1;

    if (lines_above < xmas_len - 1) {
        return 0;
    }

    char * tmp_buf = buf->buffer;
    for (int i = 1; i < xmas_len; i++) {
        tmp_buf -= (dim->len + 1); // newline moment

        if (*tmp_buf != xmas[i]) {
            return 0;
        }
    }

    return 1;
}

// south
int check_s(buf_t* buf, dim_t* dim) {
    int pos = buf->buffer - buf->start;

    int lines_below = dim->len - pos / dim->len + 1;

    if (lines_below < xmas_len - 1) {
        return 0;
    }

    char * tmp_buf = buf->buffer;
    for (int i = 1; i < xmas_len; i++) {
        tmp_buf += (dim->len + 1); // newline moment

        if (*tmp_buf != xmas[i]) {
            return 0;
        }
    }

    return 1;
}

int check_e(buf_t* buf, dim_t* dim) {
    int pos = buf->buffer - buf->start;

    //int lines_above = pos / dim->len + 1;
    int lines_right = dim->len - (pos % dim->len);

    if (lines_right < xmas_len - 1) {
        return 0;
    }

    char * tmp_buf = buf->buffer;
    for (int i = 1; i < xmas_len; i++) {
        tmp_buf += 1;

        if (*tmp_buf != xmas[i]) {
            return 0;
        }
    }

    return 1;
}

// west
int check_w(buf_t* buf, dim_t* dim) {
    int pos = buf->buffer - buf->start;

    //int lines_above = pos / dim->len + 1;
    int lines_left = pos % dim->len;

    if (lines_left < xmas_len - 1) {
        return 0;
    }

    char * tmp_buf = buf->buffer;
    for (int i = 1; i < xmas_len; i++) {
        tmp_buf -= 1;

        if (*tmp_buf != xmas[i]) {
            return 0;
        }
    }

    return 1;
}

// checks all directions returns num points
int check_x(buf_t* buf, dim_t* dim) {
    int sum = 0;
    // check n
    sum += check_n(buf, dim);
    sum += check_s(buf, dim);
    sum += check_e(buf, dim);
    sum += check_w(buf, dim);

    // check
    // check
    // check

    return sum;
}

// gets sum for a given x
int get_count(buf_t* buf, dim_t* dim) {
    int sum = 0;
    while (*buf->buffer != '\0') {
        if (*buf->buffer == 'X') {
            sum += check_x(buf, dim);
        }
        buf->buffer += 1;
    }

    return sum;
}

void solve_p1(char* buffer, size_t len) {
    dim_t dim = { .len =  0, .height = 0};
    char *ptr = buffer;
    char *start = buffer;
    buf_t buf = { .buffer = buffer, .start = start };

    get_length(ptr, &dim);
    printf("len = %d, height = %d\n", dim.len, dim.height);
    printf("ans = %d", get_count(&buf, &dim));
}
