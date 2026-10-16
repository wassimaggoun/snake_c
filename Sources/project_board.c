#include "project_board.h"
#include "alloc.h"
#include "error.h"

direction opposite(direction dir) {
    if (dir == DOWN){
        return UP;
    }
    if (dir == UP){
        return DOWN;
    }
    if (dir == RIGHT){
        return LEFT;
    }
    if (dir == LEFT){
        return RIGHT;
    }
    return dir;
}

int get_adj_cell(board *b, int cell, direction dir) {
    int row = cell / b->hsize;
    int col = cell % b->hsize;
    if (dir == UP) {
        row--;
    } else if (dir == DOWN) {
        row++;
    } else if (dir == LEFT) {
        col--;
    } else if (dir == RIGHT) {
        col++;
    } else {
        return -1; 
    }
    if (row >= 0 && row < b->vsize && col >= 0 && col < b->hsize) {
        return row * b->hsize + col;
    }
    return -1; 
}


board *new_board_nomask(int hsize, int vsize){
    if (hsize<=0 || vsize<=0){
        return NULL;
    }
    board *b=(board*)malloc(sizeof(board));
    if (b== NULL){
        return NULL;
    }
    b->hsize=hsize;
    b->vsize=vsize;
    b->size=hsize*vsize;
    b->nb_food=0;
    b->empty_cells_count=b->size;
    b->masked=(bool*)calloc(b->size,sizeof(bool));
    b->objects=(object*)calloc(b->size, sizeof(object));
    b->indirs=(direction*)calloc(b->size,sizeof(direction));
    b->outdirs=(direction*)calloc(b->size,sizeof(direction));
    b->empty_cells_listing=(int*)malloc(b->size*sizeof(int));
    b->empty_cells_indices=(int*)malloc(b->size*sizeof(int));
    if (b->masked == NULL || b->objects == NULL || b->indirs == NULL ||
        b->outdirs == NULL || b->empty_cells_listing == NULL ||
        b->empty_cells_indices == NULL){
        delete_board(b);
        return NULL;
    }
    for (int i=0;i<b->size;i++){
        b->empty_cells_listing[i]=i;
        b->empty_cells_indices[i]=i;
    }
    return b;
}

board *new_board_mask(mask *m) {
    if (m==NULL || m->grid==NULL|| m->nbmasked>= m->hsize * m->vsize){
        return NULL;
    }
    board*b=(board*)malloc(sizeof(board));
    if (b== NULL)return NULL;
    b->hsize=m->hsize;
    b->vsize=m->vsize;
    b->size=m->hsize*m->vsize;
    b->nb_food=0;
    b->empty_cells_count=0;
    b->masked=(bool*)malloc(b->size*sizeof(bool));
    b->objects=(object*)calloc(b->size,sizeof(object));
    b->indirs=(direction*)calloc(b->size,sizeof(direction));
    b->outdirs=(direction*)calloc(b->size,sizeof(direction));
    b->empty_cells_listing=(int*)malloc(b->size*sizeof(int));
    b->empty_cells_indices=(int*)malloc(b->size*sizeof(int));
    if (b->masked == NULL || b->objects == NULL || b->indirs == NULL ||
        b->outdirs == NULL || b->empty_cells_listing == NULL ||
        b->empty_cells_indices == NULL){
        delete_board(b);
        return NULL;
    }
    for (int i=0;i<b->size;i++){
        b->masked[i]=m->grid[i];
        if(b->masked[i]){
            b->objects[i]=EMPTY;
            b->empty_cells_indices[i]=-1;
        }
        else{
            b->objects[i]=EMPTY;
            b->empty_cells_listing[b->empty_cells_count]=i;
            b->empty_cells_indices[i]=b->empty_cells_count;
            b->empty_cells_count++;
        }
    }

    return b;
    
}



void delete_board(board *b) {
    if (b==NULL){
    return;
    }
    multiple_free(b->masked, b->objects, b->indirs, b->outdirs, b->empty_cells_indices,b->empty_cells_listing,b, NULL);
}

void swap_empty_cells(board *b, int i1, int i2){
    if (i1==i2) return;
    int cell1= b->empty_cells_listing[i1];
    int cell2= b-> empty_cells_listing[i2];
    int temp= b->empty_cells_listing[i1];
    b->empty_cells_listing[i1]=b->empty_cells_listing[i2];
    b->empty_cells_listing[i2]=temp;
    b->empty_cells_indices[cell1]=i2;
    b->empty_cells_indices[cell2]=i1;
}
void fill_cell_board(board *b, int i, object obj) {
    if (obj == EMPTY) {
        fprintf(stderr,"object can not be empty\n");
        return;
    }
    if (b == NULL || i < 0 || i >= b->size || b->masked[i]) {
        return;
    }
    if (b->objects[i] != EMPTY) {
        return;
    }
    b->objects[i] = obj;
    int idx = b->empty_cells_indices[i];
    if (idx >= 0 && idx < b->empty_cells_count) {
        swap_empty_cells(b, idx, b->empty_cells_count - 1);
        b->empty_cells_count--;
        b->empty_cells_indices[i] = -1;
    }
    if (obj >= APPLE && obj <= MUSHROOM) {
        b->nb_food++;
    }
}

void empty_cell_board(board *b, int i) {
    if (b == NULL || i < 0 || i >= b->size || b->masked[i]) {
        return;
    }
    if (b->objects[i] == EMPTY) {
        return;
    }
    if (b->objects[i] >= APPLE && b->objects[i] <= MUSHROOM) {
        b->nb_food--;
    }
    b->objects[i] = EMPTY;
    b->empty_cells_listing[b->empty_cells_count] = i;
    b->empty_cells_indices[i] = b->empty_cells_count;
    b->empty_cells_count++;
}