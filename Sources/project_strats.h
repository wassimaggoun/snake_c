/**
 * @file project_strats.h
 * @brief
 * Strategy functions for the AIs.
 *
 * @details
 * These are the functions used to determine the moves of the ai controlled snakes. A strategy function
 * takes as input the game and the index of the snake to modify. It chooses the direction that the snake
 * will use to exit the current cell and assigns this direction to the "move" field of the snake.
 *
 * @attention
 * A snake cannot exit a cell by going back to the cell it came from. Hence, the strategy function must
 * choose among at most three directions (the fourth unavailable direction is the one that the snake came
 * from).
 *
 * @remark
 * You have to write the strategy functions. On the other hand, you should NOT call them yourself. Indeed,
 * the strategy are called in the game loop which is already written. Each turn of the game loop consists
 * of the following four steps:
 * 1. Use a generation function to generate new objects (the function is chosen when creating the game).
 * 2. Update the moving directions of player controlled snakes according to keyboard inputs.
 * 3. Apply strategy function to update the moving directions of the AI controlled (the functions are chosen when creating the game).
 * 4. Implement the turn for all snakes by calling the "implement_turn_all_snakes" function.
 */


#ifndef _PROJECT_STRATS_H_
#define _PROJECT_STRATS_H_

 /*  ____  _             _             _              __              _   _               _    ___      */
 /* / ___|| |_ _ __ __ _| |_ ___  __ _(_) ___  ___   / _| ___  _ __  | |_| |__   ___     / \  |_ _|___  */
 /* \___ \| __| '__/ _` | __/ _ \/ _` | |/ _ \/ __| | |_ / _ \| '__| | __| '_ \ / _ \   / _ \  | |/ __| */
 /*  ___) | |_| | | (_| | ||  __/ (_| | |  __/\__ \ |  _| (_) | |    | |_| | | |  __/  / ___ \ | |\__ \ */
 /* |____/ \__|_|  \__,_|\__\___|\__, |_|\___||___/ |_|  \___/|_|     \__|_| |_|\___| /_/   \_\___|___/ */
 /*                              |___/                                                                  */

#include <stdlib.h>
#include <stdbool.h>
#include "project_game.h"
#include "project_tools.h"


/**
 * @brief
 * Internal names of the available strategy.
 *
 * @details
 * In order to add a new strategy function, you must add a new internal name for this strategy,
 * at the end of the list (before STRAT_SIZE). Then you must complete the three following steps:
 * 1) Write the strategy function.
 * 2) Add the function's name at the end of the strategy_funs array in project_objgen.c (this array contains all strategy functions).
 * 3) Add a string describing the strategy at the end of the strategy_names array in project_objgen.c (this string will be displayed in the interface).
 */
typedef enum {
  STRAT_EMPTY,        //!< Does nothing
  STRAT_CLOSESTFRUIT, //!< Tries to get the closest fruit.
  STRAT_SCORE,        //!< Tries to maximize the score.
  STRAT_STUDENTS,     //!< Tries to maximize the number of students eaten.
  STRAT_DISTANCE,     //!< Tries to maximize the distance traveled.
  STRAT_TIME,         //!< Tries to maximize the time alive.
  STRAT_SIZE,         //!< Number of strategies
} strat;

/**
 * @brief Array of strategy functions.
 */
extern void (*strat_funs[STRAT_SIZE]) (game*, int);


/**
 * @brief Array of strategy names.
 */
extern const char *strat_names[STRAT_SIZE];

/************************/
/*+ Strategy functions +*/
/************************/

/**
 * @brief
 * A strategy that does nothing.
 */
void empty_strategy(game *g, // The game.
                    int i    // The index of the snake.
);

/**
 * @brief
 * The strategy that always tries to get to the closest fruit.
 */
void closest_fruit_strategy(game *g, // The game.
                            int i    // The index of the snake.
);

/**
 * @brief
 * The strategy that tries to maximize the score above all concerns.
 */
void score_strategy(game *g, // The game.
                    int i    // The index of the snake.
);

/**
 * @brief
 * The strategy that tries to maximize the number of students eaten above all concerns.
 */
void students_strategy(game *g, // The game.
                       int i    // The index of the snake.
);

/**
 * @brief
 * The strategy that tries to maximize the distance traveled above all concerns.
 */
void distance_strategy(game *g, // The game.
                       int i    // The index of the snake.
);

/**
 * @brief
 * The strategy that tries to maximize the time alive above all concerns.
 */
void time_strategy(game *g, // The game.
                   int i    // The index of the snake.
);

/**
 * @brief
 * Deprecated alternative version of time_strategy.
 */
void avoid_strategy(game *g, // The game.
                    int i    // The index of the snake.
);

#endif // _PROJECT_STRATS_H_
