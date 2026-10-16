/**
 * @file project_snake.h
 *
 * @brief
 * Snakes.
 *
 * @details
 * Type used to represent a single snake and associated functions.
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_

 /*  ____              _              */
 /* / ___| _ __   __ _| | _____  ___  */
 /* \___ \| '_ \ / _` | |/ / _ \/ __| */
 /*  ___) | | | | (_| |   <  __/\__ \ */
 /* |____/|_| |_|\__,_|_|\_\___||___/ */

#include <stdlib.h>
#include <stdbool.h>
#include "project_masks.h"
#include "project_board.h"

/**
 * @brief
 * The number of moves it takes a snake to clear a single cell.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define LENGTH_CELL 64

/**
 * @brief
 * Internal names of the available speeds for a snake.
 *
 * @details
 * The speed of a snake determines the number of moves the snake makes
 * in a turn. These numbers of moves are already defined in the global
 * array speed_values declared below (the array itself is defined and
 * initialized in project_snake.c).
 *
 */
typedef enum {
  SLOWER,    //!< Slower speed: 1 move
  SLOW,      //!< Slow speed: 2 moves
  MEDIUM,    //!< Medium speed: 4 moves
  FAST,      //!< Fast speed: 8 moves
  FASTER,    //!< Faster speed: 16 moves
  LUDICROUS, //!< Ludicrous speed: 32 moves
  SPEED_SIZE //!< Number of speeds
} speed;

/**
 * @brief
 * The number of moves made in a single turn by a snake going at SLOWER speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define SLOWER_VAL 1

/**
 * @brief
 * The number of moves made in a single turn by a snake going at SLOW speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define SLOW_VAL 2

/**
 * @brief
 * The number of moves made in a single turn by a snake going at MEDIUM speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define MEDIUM_VAL 4

/**
 * @brief
 * The number of moves made in a single turn by a snake going at FAST speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define FAST_VAL 8

/**
 * @brief
 * The number of moves made in a single turn by a snake going at FASTER speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define FASTER_VAL 16

/**
 * @brief
 * The number of moves made in a single turn by a snake going at LUDICROUS speed.
 *
 * @details
 * USE THIS VALUE BUT DO NOT CHANGE IT (this would break the whole game).
 */
#define LUDICROUS_VAL 32


/**
  * @brief
  * For each speed name, associates the number of moves made in a single turn by a snake going at this speed.
  *
  * @return
  * The number of moves made in a single turn by a snake going at the given speed.
  */
int speed_to_value(speed s //!< The speed.
);


/**
  * @brief
  * The type representing a single snake in the game.
  */
typedef struct {
  bool alive; //!< True if the snake is alive, false if the snake is dead.

  int head; //!< The cell containing the head of the snake is currently moving
            //!< in.
  int tail; //!< The cell the tail of the snake is currently occupying (possibly
            //!< moving out is the snake is at full length).
  int length; //!< The current length of the snake (grows (by 1) each time the
              //!< snake enters a new cell until it is equal to full_length).
  int full_length; //!< The full length of the snake (increased only when the
                   //!< snake eats food).

  int progress;   //!< The progress made by the headof the snake in the current
                  //!< head cell.
  speed speed;    //!< The current speed of the snake.
  direction move; //!< The direction in which the snake is moving. Determines
                  //!< the next head cell the snake will enter after this one.

  int score;    //!< The current score of the snake.
  int distance; //!< The number of cells the snake has visited since the start
                //!< of the game.
  int students; //!< The number of students the snake has eaten since the start
                //!< of the game.
} snake;

/**
 * @brief
 * Allocates a new snake on the heap.
 *
 * @details
 * A new snake starts at length 2:
 * - The head cell is occupied by the head of the snake: this is the cell the snake is moving in.
 * - The tail cell is occupied by the tail of the snake: this is the cell the snake is moving out of (if it is at full length).
 * These two cells are chosen randomly on the board from the list of empty cells. Naturally, they must be contiguous.
 *
 * @details
 * In order to generate random numbers, you can use the "int rand();" function from the standard library.
 * This function returns a pseudo-random number in the range [0, RAND_MAX]. You can use the modulo operator
 * to get a random number in a specific range. For example, to get a random number in the range [0, 9], you
 * can use the following code: "rand() % 10".
 *
 * @remark
 * If the function fails to create the new snake (for instance, if two contiguous empty cells cannot be found), it returns NULL.
 *
 * @attention
 * Do not forget to update the arrays of the board since the tail and head cell are now occupied by the snake (this includes the
 * arrays indir and outdir).
 *
 * @return
 * A pointer to the new snake.
 */
snake *new_snake(board *b, //!< The board on which the snake will be created.
                 speed sp, //!< The initial speed of the snake.
                 int flen  //!< The initial full length of the snake.
);

/**
 * @brief
 * Deletes a snake.
 */
void delete_snake(snake *s //!< The snake to delete.
);

/**
 * @brief
 * Makes a snake consume an object.
 *
 * @remark
 * Consuming an object consists in updating the snake according to the object. The function does nothing if the
 * snake is dead.
 *
 * @details
 * Modifictions corresponding to each object:
 * - APPLE: The snake's full length grows by one. The score of the snake is increased by 10.
 * - CHERRY: The snake's full length grows by one. The score of the snake is increased by 20.
 * - BANANA: The snake's full length grows by two. The score of the snake is increased by 30.
 * - GRAPES: The snake's full length grows by two. The score of the snake is increased by 40.
 * - PINEAPPLE: The snake's full length grows by three. The score of the snake is increased by 50.
 * - STUDENT: The snake's full length is doubled. The score of the snake is increased by 100 (this also increases the number of students eaten by the snake).
 * - MUSHROOM: The speed of the snake is decreased by one level (if it is not already at the minimum speed).
 * - CHILI: The speed of the snake is increased by one level (if it is not already at the maximum speed).
 *
 * @attention
 * If the passed object is EMPTY or SNAKE, the function does nothing (these are not consummable objects
 * and the functions should NOT be called with these objects).
 */
void consume_object_snake(snake *s,  //!< The snake.
                          object obj //!< The object.
);

/**
 * @brief
 * The function moves the snake according to its current direction and speed. The snake can only move if it is alive.
 *
 * @details
 * This function advances the progress value of the snake according to its speed (it adds the number of moves corresponding
 * to this speed to the progress value).
 *
 * @details
 * If the progress value becomes equal to LENGTH_CELL (the snake has completed the current cell), the function moves the head
 * of the snake to the next cell (determined by the head's current cell and direction). In this case, the function must:
 * - Reset the progress value of the snake (it becomes 0).
 * - Update the length of the snake (it grows by one if the snake is not yet at full length).
 * - Update the tail of the snake if necessary (it loses a cell if the snake is already at full length).
 * - Update the out direction of the snake on the board for the cleared cell (to the direction took by the snake).
 * - If the next cell does not exist, if it is occupied by a snake, or if it is masked, the snake dies.
 *
 * If the snake remains alive, the function must also:
 * - Update the snake according to the object contained in the next cell (if there is one).
 * - Update the head of the snake (it moves to the next cell).
 * - Update the objects array of the board (the next cell is now occupied by the snake).
 * - Update the in direction of the snake in the next cell (the opposite of the direction in which the snake moved out of the previous head cell).
 *
 * @remark
 * If the snake is dead, the function does nothing.
 *
 * @attention
 * This function must update both the snakes and the board according to the rules of the game.
 *
 * @return
 * True if the function killed the snake, false otherwise (the snake is still alive of was already dead). This information
 * is useful in the function that calls implement_turn_snake (namely, implement_turn_all_snakes in game.h).
 */
bool implement_turn_snake(snake *s, //!< The snake.
                          board *b  //!< The board.
);

#endif // _SNAKE_H_
