/**
 * @file project_objgen.h
 * @brief
 * Objects generators.
 *
 * @details
 * These are the functions used to generate new objects on the board. An object generator function
 * takes as input the game and fills its board with one or more objects.
 *
 * @details
 * In order to generate random numbers, you can use the "int rand();" function from the standard library.
 * This function returns a pseudo-random number in the range [0, RAND_MAX]. You can use the modulo operator
 * to get a random number in a specific range. For example, to get a random number in the range [0, 9], you
 * can use the following code: "rand() % 10".
 *
 * @remark
 * You have to write the generator functions. On the other hand, you should NOT call them yourself. Indeed,
 * the strategy are called in the game loop which is already written. Each turn of the game loop consists
 * of the following four steps:
 * 1. Use a generation function to generate new objects (the function is chosen when creating the game).
 * 2. Update the moving directions of player controlled snakes according to keyboard inputs.
 * 3. Apply strategy function to update the moving directions of the AI controlled (the functions are chosen when creating the game).
 * 4. Implement the turn for all snakes by calling the "implement_turn_all_snakes" function.
 */

#ifndef _PROJECT_OBJGEN_H_
#define _PROJECT_OBJGEN_H_

 /*   ___  _     _           _                                     _                  */
 /*  / _ \| |__ (_) ___  ___| |_    __ _  ___ _ __   ___ _ __ __ _| |_ ___  _ __ ___  */
 /* | | | | '_ \| |/ _ \/ __| __|  / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \| '__/ __| */
 /* | |_| | |_) | |  __/ (__| |_  | (_| |  __/ | | |  __/ | | (_| | || (_) | |  \__ \ */
 /*  \___/|_.__// |\___|\___|\__|  \__, |\___|_| |_|\___|_|  \__,_|\__\___/|_|  |___/ */
 /*           |__/                 |___/                                              */


#include <stdlib.h>
#include <stdbool.h>
#include "project_game.h"
#include "project_tools.h"


/**
 * @brief
 * Internal names of the available object generators.
 *
 * @details
 * In order to add a new generator, you must add a new name here, at the end before OGEN_SIZE.
 * Then you must complete the three following steps:
 * - Write the corresponding generator function.
 * - Add the function at the end of the generator_funs array in project_objgen.c (it contains all generators functions).
 * - Add the name at the end of the generator_names array in project_objgen.c (it contains all generators names). This is
 *  used to display the generator name in the interface.
 */
typedef enum {
  OGEN_EMPTY,  //!< Empty generator.
  OGEN_BASIC,  //!< Basic random generator.
  OGEN_SAPPLE, //!< Generator ensuring that only a single apple is always
               //!< present on the board.
  OGEN_TENPE,  //!< Generator ensuring that ten parcent of the empty cells are
               //!< always filled with random objects.
  OGEN_STINV,  //!< Generator that fills the board with students only.
  OGEN_SIZE,   //!< Number of generators.
} generator;

/**
 * @brief Array of generator functions.
 */
extern void (*generator_funs[OGEN_SIZE])(game *);

/**
 * @brief Array of strategy names.
 */
extern const char *generator_names[OGEN_SIZE];

/*************************/
/*+ Generator functions +*/
/*************************/

/**
 * @brief
 * Empty generator.
 *
 * @details
 * Does nothing (no objects are generated).
 */
void gen_empty(game *g //!< The board.
);

/**
 * @brief
 * Basic object generator.
 *
 * @details
 * Every LENGTH_CELL turns, this generator picks a random empty cell and fills it with a random object.
 */
void gen_basic(game *g //!< The board.
);

/**
 * @brief
 * Single apple generator.
 *
 * @details
 * Ensures that only a single apple is always present on the board. If the apple is eaten, a new one is generated.
 */
void gen_single_apple(game *g //!< The board.
);

/**
 * @brief
 * Ten percent generator.
 *
 * @details
 * Ensures that exactly ten percent of the empty cells are always filled with random objects. If the percentage
 * of filled cells drops below ten percent, the generator fills randomly chosen empty cells with random objects
 * until the percentage is ten percent.
 */
void gen_ten_percent(game *g //!< The board.
);

/**
 * @brief
 * Invasion of the students generator.
 *
 * @details
 * Ensures that exactly twenty percent of the empty cells are always filled with students. If the percentage
 * of filled cells drops below twenty percent, the generator fills randomly chosen empty cells with students
 * until the percentage is twenty percent.
 *
 * @attention
 * When eaten, students can increase the length of the snakes significantly. Before tou use this generator,
 * make sure that the function used to consume food handles the error that may happen when the full length
 * of the snake becomes "too high".
 */
void gen_student_invasion(game *g //!< The board.
);

#endif // _PROJECT_OBJGEN_H_
