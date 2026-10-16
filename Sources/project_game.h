/**
 * @file project_game.h
 * @brief
 * Game.
 *
 * @details
 * Type used to represent a single game and associated functions.
 */

#ifndef _GAME_H_
#define _GAME_H_



 /*   ____    _    __  __ _____ ____   */
 /*  / ___|  / \  |  \/  | ____/ ___|  */
 /* | |  _  / _ \ | |\/| |  _| \___ \  */
 /* | |_| |/ ___ \| |  | | |___ ___) | */
 /*  \____/_/   \_\_|  |_|_____|____/  */

#include <stdbool.h>
#include <stdlib.h>
#include "project_snake.h"
#include "project_board.h"
#include "project_score.h"
#include "project_tools.h"


/**
 * @brief
 * Type used to represent a single game.
 *
 * @remark
 * In the array, snakes_array, the pointers to the snakes are stored in the following order:
 * - The cells 0 to nb_ais-1 contain the pointers to the computer controlled snakes.
 * - The cells nb_ais and nb_ais + 1 contain the pointers to the two players (if they are in the game).
 */
typedef struct game {
  board *b; //!< The game board.

  int nb_ais; //!< The number of computer controlled snakes in the game (0 or
              //!< more).
  int nb_players; //!< The number of players in the game (0, 1 or 2).
  int nb_alive; //!< The number of remaining alive snakes (at most nb_players +
                //!< nb_ais).
  int nb_turns; //!< The number of turns played in the game since the
                //!< beginning.

  snake **snakes_array; //!< The array containing all snakes in the game (size
                        //!< "nb_ais + nb_players"). The players (if any) are
                        //!< stored at the end of the array.
} game;

/**
 * @brief
 * Allocates a new game on the heap.
 *
 * @return
 * A pointer to the new game.
 */
game *new_game(int hsize, //!< Horizontal size of the board.
               int vize,  //!< Vertical size of the board.
               mask *m,   //!< Mask used to create the board (NULL if no mask).
               int nh,    //!< Number of human players (0, 1 or 2)
               int ns,    //!< Number of computer controlled snakes.
               int vs,    //!< Common initial speed of the snakes.
               int ls     //!< Common initial full length of the snakes.
);

/**
 * @brief
 * Deletes a game.
 */
void delete_game(game *g //!< The game.
);

/**
 * @brief
 * Updates the moving direction of the first player (if it exists).
 *
 * @remark
 * The direction is NOT updated if one of the two following conditions is met:
 * - The snake is dead, or,
 * - The new direction is the one the snake used to enter its current cell (the snake cannot turn backwards).
 */
void set_direction_player1(game *g,      //!< The game.
                           direction dir //!< The new direction.
);

/**
 * @brief
 * Updates the moving direction of the second player (if it exists).
 *
 * @remark
 * The direction is NOT updated if one of the two following conditions is met:
 * - The snake is dead, or,
 * -  
 */
void set_direction_player2(game *g,      //!< The game.
                           direction dir //!< The new direction.
);

/**
 * @brief
 * Moves all snakes in a game and updates the game state.
 *
 * @remark
 * A pointer to a score_table is also given as a parameter. If a snake died as a result of
 * the movement, its scores values must be filled in this score_table (for the current game).
 * See the file project_score.h for more information on scores.
 *
 * @remark
 * In order to retrieve the time a snake spent alive before dying (for its score), you may use
 * the function get_time_counter() defined in project_tools.h which returns the time spent since the
 * beginning of the game in milliseconds. Do note that the time must be filled in seconds in the
 * score_table.
 *
 * @remark
 * If a NULL pointer is given for the score_table, the scores are not updated.
 */
void implement_turn_all_snakes(game *g,        //!< The game.
                               score_table *st //!< The game scores.
);

#endif
