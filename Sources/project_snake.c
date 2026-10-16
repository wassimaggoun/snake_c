#include "project_snake.h"
#include "error.h"
#include "alloc.h"
#include <limits.h>
#include "project_board.h"

const int speed_values[SPEED_SIZE] = {
    SLOWER_VAL,
    SLOW_VAL,
    MEDIUM_VAL,
    FAST_VAL,
    FASTER_VAL,
    LUDICROUS_VAL
};
int speed_to_value(speed s) {
    if (s<0 || s>=SPEED_SIZE){
        return 0;
    }
    return speed_values[s];
}
snake *new_snake(board* b, speed sp, int flen) 
{
    if (b == NULL || flen < 1 || b->empty_cells_count < 2) return NULL;

        int head_idx = rand() % b->empty_cells_count;
        int head = b->empty_cells_listing[head_idx];

        direction dir = rand() % DIRECTION_SIZE;
        int tail = get_adj_cell(b, head, opposite(dir));

        while (tail == -1 || b->empty_cells_indices[tail] == -1)
        {
            head_idx = rand() % b->empty_cells_count;
            head = b->empty_cells_listing[head_idx];
            dir = rand() % DIRECTION_SIZE;
            tail = get_adj_cell(b, head, opposite(dir));
        }

        snake* s = malloc(sizeof(snake));

        s->alive = true;
        s->head = head;
        s->tail = tail;
        s->length = 1;
        s->full_length = flen;
        s->progress = 0;
        s->move = dir;
        s->speed = sp;
        s->score = 0;
        s->distance = 0;
        s->students = 0;

        fill_cell_board(b, head, SNAKE);
        fill_cell_board(b, tail, SNAKE);

        b->indirs[head] = opposite(dir);
        b->outdirs[head] = dir;

        b->indirs[tail] = opposite(dir);
        b->outdirs[tail] = dir;

        return s;

}


void delete_snake(snake *s) {
    if (s != NULL) free(s);
}

void consume_object_snake(snake *s, object obj) {
    if (!s || !s->alive) return;

    if (obj == APPLE) {
        s->full_length += 1;
        s->score += 10;
    } else if (obj == CHERRY) {
        s->full_length += 1;
        s->score += 20;
    } else if (obj == BANANA) {
        s->full_length += 2;
        s->score += 30;
    } else if (obj == GRAPES) {
        s->full_length += 2;
        s->score += 40;
    } else if (obj == PINEAPPLE) {
        s->full_length += 3;
        s->score += 50;
    } else if (obj == STUDENT) {
        s->full_length *= 2;
        s->score += 100;
        s->students += 1;
    } else if (obj == MUSHROOM) {
        if (s->speed > SLOWER) {
            s->speed--;
        }
    } else if (obj == CHILI) {
        if (s->speed < LUDICROUS) {
            s->speed++;
        }
    }
}

bool implement_turn_snake(snake *s, board *b){
    if (!s->alive) return false;
    int speed_progress = speed_to_value(s->speed);
    s->progress += speed_progress;

    if (s->progress < LENGTH_CELL) return false;

    s->progress = 0;
    int new_head = get_adj_cell(b, s->head, s->move);
    if (new_head == -1 || b->objects[new_head] == SNAKE || b->masked[new_head]) {
        s->alive = false;
        return true;
    }
    if (s->length < s->full_length) {
        s->length++;
    } else {
        int next_tail = get_adj_cell(b, s->tail, b->outdirs[s->tail]);
        empty_cell_board(b, s->tail);
        s->tail = next_tail;
    }
    object obj = b->objects[new_head];
    consume_object_snake(s, obj);
    empty_cell_board(b,new_head);

    fill_cell_board(b, new_head, SNAKE);
    b->indirs[new_head] = opposite(s->move);
    b->outdirs[s->head] = s->move;
    s->head = new_head;

    return false;

}