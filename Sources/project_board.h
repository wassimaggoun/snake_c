/**
 * @file project_board.h
 * @brief
 * Game board.
 *
 * @details
 * Type used to represent a game board and associated functions.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

 /*  ____   ___    _    ____  ____  ____   */
 /* | __ ) / _ \  / \  |  _ \|  _ \/ ___|  */
 /* |  _ \| | | |/ _ \ | |_) | | | \___ \  */
 /* | |_) | |_| / ___ \|  _ <| |_| |___) | */
 /* |____/ \___/_/   \_\_| \_\____/|____/  */

#include <stdlib.h>
#include <stdbool.h>
#include "project_masks.h"
#include "project_tools.h"

 /**
  * @brief
  * Enum type used to represent the four possible directions inside a board.
  */
typedef enum {
  UP,             //!< Up
  RIGHT,          //!< Right
  DOWN,           //!< Down
  LEFT,           //!< Left
  DIRECTION_SIZE, //!< Number of directions
} direction;

/**
 * @brief
 * Returns the opposite direction of a given direction.
 *
 * @return
 * The opposite direction.
 */
direction opposite(direction dir //!< The direction.
);

/**
 * @brief
 * Enum type used to represent all the objects that can be placed inside a cell
 * of the board.
 *
 * @remark
 * The first object is EMPTY, which represents an empty cell. The second object is SNAKE,
 * which represents a cell occupied by a snake section. The other objects represent the
 * different types of food that can be placed in a cell for the snakes to pick up.
 */
typedef enum {
  EMPTY,       //!< Empty cell
  SNAKE,       //!< Snake section
  APPLE,       //!< Apple (1 point + 1 length)
  CHERRY,      //!< Cherry (2 points + 2 length)
  BANANA,      //!< Banana (3 points + 3 length)
  GRAPES,      //!< Grapes (4 points + 4 length)
  PINEAPPLE,   //!< Pineapple (5 points + 5 length)
  STUDENT,     //!< Student (20 points + double length)
  CHILI,       //!< Chili (increases speed, if not at maximum)
  MUSHROOM,    //!< Mushroom (decreases speed, if not at minimum)
  OBJECT_SIZE, //!< Number of objects
} object;

/**
 * @brief
 * The type used to represent a board.
 *
 * @details
 * A board is a rectangular grid of cells. The cells of the board are indexed linearly line by line,
 * from left to right and from top to bottom. If the board has hsize columns and vsize rows, the first
 * cell (in the top-left corner) has index 0, the cell to its right has index 1, and so on. The last
 * cell (in the bottom-right corner) has index (hsize * vsize - 1).
 *
 * @details
 * Each cell in the board can be masked (i.e., it cannot be occupied by snakes or objects). Masked cells
 * are indicated by the masked array. If the cell with index i is masked, then masked[i] is true; otherwise,
 * masked[i] is false.
 *
 * @details
 * The board also contains an array of objects that indicate the content of each unmasked cell. For each i,
 * objects[i] is the object contained in the cell with index i. The object can be EMPTY (this special value
 * indicates that the cell is empty), SNAKE (this special value indicates that the cell is occupied by some
 * snake section), or one of the other objects defined in the object enum. If the cell with index i is masked,
 * then objects[i] is undefined (its value is irrelevant).
 *
 * @details
 * The board also contains two arrays of directions that indicate the directions the snakes used to enter and
 * exit the cells. For each i, if the cell with index i contains a snake section (as indicated by objects[i]),
 * then indirs[i] is the direction the snake used to enter the cell, and outdirs[i] is the direction the snake
 * used to exit the cell. If the cell with index i does not contain a snake section, then indirs[i] and outdirs[i]
 * are undefined (their values are irrelevant).
 *
 * @details
 * Finally, the board also maintains a list of empty cells for quick access (they are the unmasked cells of index
 * i where objects[i] is EMPTY). The empty_cells_count variable indicates the number of empty cells. All the empty
 * cells are listed in the empty_cells_listing array at indices 0, 1, 2, ..., empty_cells_count - 1 in an arbitrary
 * order (the array itself is of size hsize * vsize). The empty_cells_indices array is indexed by the cells indices
 * (0, 1, 2, ..., hsize * vsize - 1), for each i, if the cell with index i is empty, then empty_cells_indices[i] is
 * the index of the cell in the empty_cells_listing array that contains i; otherwise, empty_cells_indices[i] is -1.
*/
typedef struct {
    int hsize; //!< Horizontal size.
    int vsize; //!< Vertical size.
    int size;  //!< Total number of cells (hsize * vsize).
    int nb_food; //!< Number of food items on the board (Fruits, students, mushrooms, chilis).

    bool* masked; //!< For each cell index i, masked[i] is true if the cell is masked and false otherwise.

    object* objects; //!< Array of objects.

    direction* indirs; //!< Array of in directions of the snakes.
    direction* outdirs; //!< Array of out directions of the snakes.

    int empty_cells_count; //!< Number of empty cells.
    int* empty_cells_listing; //!< Array which lists the empty cells.
    int* empty_cells_indices; //!< Array of indices of empty cells in empty_cells_listing.
} board;


/**
 * @brief
 * Computes the index of the cell adjacent to a given cell in a given direction.
 *
 * @return
 * The index of the adjacent cell, or -1 if the adjacent cell does not exist.
 */
int get_adj_cell(board *b,     //!< The board.
                 int cell,     //!< The index of the cell.
                 direction dir //!< The direction.
);

/**
 * @brief
 * Allocates a new board on the heap. Variant without mask.
 *
 * @return
 * A pointer to the new board.
 */
board *new_board_nomask(int hsize, //!< The horizontal size.
                        int vsize  //!< The vertical size.
);

/**
 * @brief
 * Alloactes a new board on the heap. Variant with mask.
 *
 * @remark
 * The dimensions of the board are determined by the dimensions of the mask.
 *
 * @return
 * A pointer to the new board.
 */
board *new_board_mask(mask *m //!< The mask.
);

/**
 * @brief
 * Releases the memory allocated for a board.
 */
void delete_board(board *b //!< The board.
);

/**
 * @brief
 * Swaps the positions of two empty cells in the array empty_cells_listing which lists the empty cells
 *
 * @remark
 * This functions does not change the represented board. It only changes the order in which the empty
 * cells are listed. This is sometimes in order to modify the empty_cells_listing array. For instance,
 * removing a cell from the list of empty cells is done by swapping the cell with the last cell of the
 * array and then decrementing empty_cells_count.
 */
void swap_empty_cells(
    board *b, //!< The board.
    int i1,   //!< The index of the first cell in empty_cells_listing.
    int i2    //!< The index of the second cell in empty_cells_listing.
);

/**
 * @brief
 * Fills a cell of the board with an object.
 *
 * @details
 * If the cell already contains an object, the function does nothing.
 * If the cell was empty, the cell needs to be removed from the list of empty cells. In this
 * case, empty_cells_count, the empty_cells_listing array, and the empty_cells_indices array
 * need to be updated accordingly.
 *
 * @remark
 * The function raises an error if the object is EMPTY (one cannot fill a cell with an empty
 * object as it serves to indicate an empty cell).
 */

void fill_cell_board(board *b,  //!< The board.
                     int i,     //!< The index of the cell.
                     object obj //!< The object.
);

/**
 * @brief
 * Empties a cell of the board.
 *
 * @details
 * If the cell was empty, the function does nothing. If the cell contained an object, the cell
 * is emptied in the objects array of the board. The cell needs to be added to the list of empty
 * cells. In this case, empty_cells_count, the empty_cells_listing array, and the empty_cells_indices
 * array need to be updated accordingly.
 */
void empty_cell_board(board *b, //!< The board.
                      int i     //!< The index of the cell.
);

#endif // _BOARD_H_
