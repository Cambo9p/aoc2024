#include <stdio.h>
#include <stdlib.h>

typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT,
} DIRECTION;

typedef struct {
    int len;
    int height;
    int buf_len;
} dim_t;

typedef struct {
    char* buffer;
    char* start;
    dim_t *dim;
} buf_t;

void get_pos_from_num(buf_t buf, int pos, int *x, int* y) {
    printf("len = %d\n", buf.dim->len);
    printf("height = %d\n", buf.dim->height);
    *x = (pos % buf.dim->len);
    *y = (pos / buf.dim->height);
}

char get_char_at_xy(buf_t buf, int x, int y) {
    if (x > buf.dim->len || y > (buf.dim->height)) {
        return '.';
    }

    return *(buf.start + x + (y * buf.dim->len));
}

// gets the position of ^ in the char array
int get_guard_start_pos(char *buffer) {
    char guard = '^';
    int count = 0;

    while (*buffer != guard) {
        count++;
        buffer++;
    }

    return count;
}

void free_buf(buf_t *buf) {
    free(buf->dim);
    free(buf);
}

buf_t * init_buf(char *buffer) {
    buf_t * buf = (buf_t *) malloc(sizeof(buf_t));
    dim_t * dim =  (dim_t *) malloc(sizeof(dim_t));

    char * ptr = buffer;
    int count = 0;
    int newline_count = 0;
    
    while (*ptr != '\0') {
        if (*ptr == '\n') {
            newline_count++;
        }
        count++;
        ptr++;
    }

    dim->height = newline_count;
    dim->len = count / newline_count;
    dim->buf_len = count;

    buf->start = buffer;
    buf->buffer = buffer;
    buf->dim = dim;

    return buf;
}

void update_buf_at_xy(buf_t * buf, int x, int y, char c) {
    *(buf->buffer + x + (y * buf->dim->len)) = c;
}

// updates current guard to be an x 
// then updates the next point to be the guard 
void update_board_after_move(buf_t *buf, DIRECTION d, int *x, int *y) {
    update_buf_at_xy(buf, *x, *y, 'X');
    switch (d) {
        case UP:
            *y-=1;
            update_buf_at_xy(buf, *x, *y, '^');
            break;
        case DOWN:
            *y+=1;
            update_buf_at_xy(buf, *x, *y, 'v');
            break;
        case LEFT:
            *x-=1;
            update_buf_at_xy(buf, *x, *y, '<');
            break;
        case RIGHT:
            *x+=1;
            update_buf_at_xy(buf, *x, *y, '>');
            break;
    }
    printf("after the move:\n");
    //printf("%s\n", buf->buffer);
}

int check_room(buf_t *buf, DIRECTION *d, int x, int y) {
    int can_move;
    switch (get_char_at_xy(*buf, x, y)) {
        case '^':
            *d = UP;
            can_move = y - 1 >= 0;
            break;
        case '>':
            *d = RIGHT;
            can_move = x + 1 <= buf->dim->len;
            break;
        case 'v':
            *d = DOWN;
            can_move = y + 1 <= buf->dim->height;
            break;
        case '<':
            *d = LEFT;
            can_move = x - 1 >= 0;
            break;
        default:
            printf("%s\n", buf->buffer);
            printf("got %c at x %d y %d\n", *buf->buffer, x, y);

            perror("unexpected symbol");
            exit(0);
    }

    return can_move;
}

// changes to move 90 deg right if there is an obsticle in front 
void change_direction(buf_t *buf, int x, int y, DIRECTION *d) {
    char block = '#';
    switch (*d) {
        case UP:
            if (get_char_at_xy(*buf, x, y - 1) == block) {
                update_buf_at_xy(buf, x, y, '>');
                *d = RIGHT;
            }
            break;
        case DOWN:
            if (get_char_at_xy(*buf, x, y + 1) == block) {
                update_buf_at_xy(buf, x, y, '<');
                *d = LEFT;
            }
            break;
        case LEFT:
            if (get_char_at_xy(*buf, x - 1, y) == block) {
                update_buf_at_xy(buf, x, y, '^');
                *d = UP;
            }
            break;
        case RIGHT:
            if (get_char_at_xy(*buf, x + 1, y) == block) {
                update_buf_at_xy(buf, x, y, 'v');
                *d = DOWN;
            }
            break;
    }
}

// 0 means its the end of the game 
// returns 1 if we sucessfully moved in a direction
// if we can move this will place an x and move the guard to 
// the next pos, updating x and y in the parent caller
int move(buf_t *buf, int *x, int *y) {
    printf("entering move at x: %d y %d\n", *x, *y);
    DIRECTION d;
    int can_move = check_room(buf, &d, *x, *y);

    if (!can_move) {
        update_buf_at_xy(buf, *x, *y, 'X');
        return 0;
    }
    // check if we need to move right 
    change_direction(buf, *x, *y, &d);

    update_board_after_move(buf, d, x, y);

    return 1;
}

int count_x(buf_t* buf) {
    printf("counting\n");
    //printf("%s\n", buf->buffer);
    int count = 0;

    while (*buf->start != '\0') {
        if (*buf->start++ == 'X') {
            count++;
        }
    }

    return count;
}

int process_route(buf_t *buf, int curr_x, int curr_y) {
    // call this function in a new state and update the buffer, 
    while (1) {
        if (!move(buf, &curr_x, &curr_y)) {
            break;
        }
    }

    return count_x(buf);
}

void solve_p1(char* buffer, size_t len) {
    buf_t *buf = init_buf(buffer);
    printf("%s\n", buf->buffer);
    int start_pos = get_guard_start_pos(buf->buffer);
    int x = 0;
    int y = 0;
    
    get_pos_from_num(*buf, start_pos, &x , &y);
    printf("%c\n", get_char_at_xy(*buf, x, y));
    printf("start x %d y %d\n", x, y);
    printf("starting buf = %c\n", *buf->buffer);

    printf("the ans is %d\n", process_route(buf, x, y));

    free_buf(buf);
}
