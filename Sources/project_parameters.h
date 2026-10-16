/**
 * @file project_parameters.h
 * @brief Parameters.
 *
 * @details Macros for the following parameters:
 * - Activation of some debugging features.
 * - Dimensions of the window.
 * - Default parameters for the games. These are the parameters used if a quick game is launched.
 */

#ifndef _PROJECT_PARAMETERS_H_
#define _PROJECT_PARAMETERS_H_

 /*  ____                                _                 */
 /* |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___  */
 /* | |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __| */
 /* |  __/ (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \ */
 /* |_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/ */


/***************/
/*+ Debugging +*/
/***************/


/**
 * @brief Removes the onscreen message when pausing the game. Uncomment to activate.
 *
 * @details
 * If this macro is defined, the onscreen message that appears when the game is paused will be removed.
 * This gives a better look at the game board for debugging purposes.
 */
 // #define HIDEPAUSE

/**
* @brief Activates debugging fo snakes. Uncomment to activate.
*
* @details
* If this macro is defined, the cells that are marked as filled with a snake will be highlighted
* in white in the application.
*/
//#define DEBUGSNAKES

/**
 * @brief Activates first debugging for the empty cells. Uncomment to activate.
 *
 * @details
 * If this macro is defined, the cells that listed as empty in the empty_cell_listing array will be
 * highlighted in yellow in the application.
 */
   // #define DEBUGEMPTYLIST

/**
 * @brief Activates second debugging for the empty cells. Uncomment to activate.
 *
 * @details
 * If this macro is defined, the cells marked as as empty in the empty_cell_indices array will be
 * highlighted in blue in the application.
 */
   //#define DEBUGEMPTYINDICES


/**
 * @brief Activates debugging for the masks. Uncomment to activate.
 *
 * @details
 * If this macro is defined, the selected mask will be displayed on the terminal (by calling the
 * function print_mask which you have to write) before the game is launched.
 */
//#define DEBUGMASK


/***********************/
/*+ Window dimensions +*/
/***********************/


/**
 * @brief Horizontal dimension of the application in pixels (default = 1820).
 */
#define WINDOW_SCREENWIDTH 1820

/**
 * @brief Vertical dimension of the application in pixels (default = 980).
 */
#define WINDOW_SCREENHEIGHT 980


/************************/
/*+ Default parameters +*/
/************************/

/**
 * @brief Number of games to play for the quick game command.
 */
#define QUICK_NBGAMES 2


/**
 * @brief Horizontal dimension of the board in cells for quick games.
 */
#define QUICK_HSIZE 25

/**
 * @brief Vertical dimension of the board in cells for quick games.
 */
#define QUICK_VSIZE 25

/**
 * @brief Mask used in quick games: a string containing the name of the file such as "loveC.msk" (NULL if no mask is desired).
 */
#define QUICK_MASK NULL

/**
 * @brief  How many players are there in quick games (0, 1 or 2)
 */
#define QUICK_PLAYERS 1

/**
 * @brief Number of IAs in quick games.
 */
#define QUICK_IA 1

/**
 * @brief Initial maximum length of the snakes in quick games.
 */
#define QUICK_MAXLENGTH 4

/**
 * @brief Common strategy of all IAs in quick games.
 */
#define QUICK_STRAT STRAT_SCORE

/**
 * @brief Starting speed of the snakes in quick games.
 */
#define QUICK_SPEED SLOW

/**
 * @brief Object generator used in quick games.
 */
#define QUICK_OBJGEN OGEN_BASIC

/**
 * @mainpage The snake game project.
 *
 */

#endif // _PROJECT_PARAMETERS_H_
