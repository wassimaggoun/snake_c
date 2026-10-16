#include "project_strats.h"
#include "alloc.h"
#include "error.h"
#include "project_tools.h"
#include "project_board.h"
#include <limits.h>
#include <stdlib.h>

void (*strat_funs[STRAT_SIZE])(game *, int) = {
    empty_strategy,    
    closest_fruit_strategy, 
    score_strategy,
    students_strategy, 
    distance_strategy, 
    time_strategy
};

const char *strat_names[STRAT_SIZE] = {
    "Empty",
    "Closest fruit",
    "Maximize score",
    "Eat lots of students",
    "Maximize distance",
    "Survive"
};

void empty_strategy(game *g, int i) {
    return;
}

void closest_fruit_strategy(game *g, int i) {
    snake* s = g->snakes_array[i];
    if (!s || !s->alive) return;

    board *b = g->b;
    int head = s->head;
    direction entry = b->indirs[head];

    int max_search_distance = 5;
    int closest_dist = max_search_distance + 1;
    direction best_dir = -1;

    for (int d = 0; d < DIRECTION_SIZE; d++) {
        if (d == entry) continue;

        int cell = head;
        for (int dist = 1; dist <= max_search_distance; dist++) {
            cell = get_adj_cell(b, cell, (direction)d);
            if (cell == -1 || b->masked[cell]) break;

            object obj = b->objects[cell];
            if (obj != EMPTY && obj != SNAKE) {
                if (dist < closest_dist) {
                    closest_dist = dist;
                    best_dir = (direction)d;
                }
                break;
            }
            if (obj == SNAKE) {
                break;
            }
        }
    }

    if (best_dir != -1) {
        s->move = best_dir;
        return;
    }

    for (int d = 0; d < DIRECTION_SIZE; d++) { //in case no fruit is found
        if (d == entry) continue;

        int cell = head;
        for (int dist = 1; dist <= max_search_distance; dist++) {
            cell = get_adj_cell(b, cell, (direction)d);
            if (cell == -1 || b->masked[cell]) break;

            object obj = b->objects[cell];
            if (obj == EMPTY) {
                s->move = (direction)d;
                return;
            }
            if (obj == SNAKE) {
                break;
            }
        }
    }
}

void score_strategy(game *g, int i) {
    snake* s = g->snakes_array[i];
    if (!s || !s->alive) return;

    int head = s->head;
    direction entry = g->b->indirs[head];
    int best_score = -1;
    direction best_dir = s->move;

    for (int d = 0; d < DIRECTION_SIZE; d++) {
        if (d == entry) continue;

        int cell = get_adj_cell(g->b, head, d);
        if (cell == -1 || g->b->masked[cell]) continue;

        object obj = g->b->objects[cell];
        int score = 0;

        switch (obj) {
            case APPLE: score = 10; break;
            case CHERRY: score = 20; break;
            case BANANA: score = 30; break;
            case GRAPES: score = 40; break;
            case PINEAPPLE: score = 50; break;
            case STUDENT: score = 100; break;
            default: break;
        }

        if (score > best_score) {
            best_score = score;
            best_dir = d;
        }
    }

    s->move = best_dir;
}

void students_strategy(game *g, int i) {
    snake* s = g->snakes_array[i];
    if (!s || !s->alive) return;

    board *b = g->b;
    int head = s->head;
    direction entry = b->indirs[head];

    int max_search_distance = 5;
    int closest_student = max_search_distance + 1;
    direction best_dir = -1;

    for (int d = 0; d < DIRECTION_SIZE; d++) {
        if (d == entry) continue;

        int cell = head;
        for (int dist = 1; dist <= max_search_distance; dist++) {
            cell = get_adj_cell(b, cell, (direction)d);
            if (cell == -1 || b->masked[cell]) break;

            if (b->objects[cell] == STUDENT) {
                if (dist < closest_student) {
                    closest_student = dist;
                    best_dir = (direction)d;
                }
                break;
            }
            if (b->objects[cell] != EMPTY) {
                break;
            }
        }
    }

    if (best_dir != -1) {
        s->move = best_dir;
    } else {
        closest_fruit_strategy(g, i);
    }
}


void distance_strategy(game *g, int i) {
    snake *s = g->snakes_array[i];
    if (!s || !s->alive) {
        return;
    }

    board *b = g->b;
    int head = s->head;
    direction entry = b->indirs[head];

    int best_way = -1;
    direction best_dir = s->move;

 
    for (int dir = 0; dir < DIRECTION_SIZE; dir++) {
        if (dir == entry) {
            continue;
        }

        int run_length = 0;
        int cell = head;

        while (true) {
            cell = get_adj_cell(b, cell, (direction)dir);
            if (cell < 0) {
                break;
            }
            if (b->masked[cell]) {
                break;
            }
            object obj = b->objects[cell];
            if (obj == SNAKE) {
                break;
            }
            run_length++;
        }

        if (run_length > best_way) {
            best_way = run_length;
            best_dir = (direction)dir;
        }
    }

    s->move = best_dir;
}

void time_strategy(game *g, int i) {
    snake* s = g->snakes_array[i];
    if (!s || !s->alive) return;

    int head = s->head;
    direction entry = g->b->indirs[head];

    direction safest_dir = s->move;
    int safest_value = -1;

    for (int d = 0; d < DIRECTION_SIZE; d++) {
        if (d == entry) continue;
        int cell = get_adj_cell(g->b, head, d);
        if (cell == -1 || g->b->masked[cell]) continue;
        if (g->b->objects[cell] == SNAKE) continue;

        int count = 0;
        int tmp = cell;
        while (true) {
            tmp = get_adj_cell(g->b, tmp, d);
            if (tmp == -1 || g->b->masked[tmp] || g->b->objects[tmp] == SNAKE) break;
            count++;
        }

        if (count > safest_value) {
            safest_value = count;
            safest_dir = d;
        }
    }

    s->move = safest_dir;
}
