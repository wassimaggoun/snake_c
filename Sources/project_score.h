/**
 * @file project_score.h
 * @brief
 * Scores.
 *
 * @details
 * Type used to represent the scores of a game.
 */


#ifndef _PROJECT_SCORE_H_
#define _PROJECT_SCORE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "project_snake.h"
#include "project_tools.h"


 /*  ____                           */
 /* / ___|  ___ ___  _ __ ___  ___  */
 /* \___ \ / __/ _ \| '__/ _ \/ __| */
 /*  ___) | (_| (_) | | |  __/\__ \ */
 /* |____/ \___\___/|_|  \___||___/ */

/**
 * @brief
 * Type used to represent the different scores.
 */
typedef enum {
  SC_MAIN,     //!< The main score of the snake.
  SC_STUDENTS, //!< The number of students the snake ate.
  SC_LENGTH,   //!< The length of the snake when it died.
  SC_VISITED,  //!< The number of cells the snake visited before dying.
  SC_TIME,     //!< The time the snake spent alive (given in seconds).
  SC_SIZE      //!< The number of score types.
} score_type;

/**
 * @brief
 * Type used to represent the score values of a single snake after a single game.
 */
typedef struct {
  bool filled; //!< True if the score has been filled (false otherwise).
  score_type vals[SC_SIZE]; //!< Array of size SC_SIZE that contains the values
                            //!< of the different scores.
} single_score;

/**
 * @brief Type used to represent the scores of each game in a series of games.
 *
 * @details
 * In the interface, it is possible to create a series of several consecutive games. This type is used to
 * store the scores of each snake in each game of the series as well as the final scores of each snake (the
 * sum of the scores of the snake in each game).
 *
 * @details
 * The array of scores is a two-dimensional array of size nb_snakes x (nb_games + 1). If i is the index of a
 * snake (in the socre table) and j < nb_game is the index of a game, then scores[i][j] contains a pointer to
 * the score of the snake i in the game j (which are filled after this game is played). Also, scores[i][nb_game]
 * contains a pointer to the final score of the snake i: the sum of the scores of the snake in each game (which
 * is filled after all the games are played).
 *
 * @remark
 * The snakes are not necessarily stored in the same order as in the game (this is because it is possible to
 * sort score tables according to one of the scores types). The correspondence with the indices of the snakes
 * in the game is given by the game_to_score and score_to_game arrays.
 */
typedef struct {
  int nb_snakes;          //!< Total number of snakes
  int nb_games;           //!< The total number of games in this series.
  int cu_game;            //!< The number of the game currently being played.
  single_score ***scores; //!< Two dimensional array. Size nb_snakes x (nb_games
                          //!< + 1). Contains the scores of each snake in each
                          //!< game, as well as the final score of each snake.

  int *game_to_score; //!< Array of size nb_snakes. If k is the index of a snake
                      //!< in the game, then game_to_score[k] is the index of
                      //!< the same snake in the score table.
  int *score_to_game; //!< Array of size nb_snakes. If i is the index of a snake
                      //!< in the score table, then score_to_game[i] is the
                      //!< index of the same snake in the game.
} score_table;

/**
 * @brief
 * Allocates a new score_table on the heap.alignas
 *
 * @remark
 * The scores of the snakes are not initialized (the Boolean value filled is set to false
 * for each score). The scores will be filled after each game is played.
 *
 * @return
 * A pointer to the new score_table.
 */
score_table *new_score_table(int n_g, //!< The number of games.
                             int n_s  //!< The total number of snakes.
);

/**
 * @brief
 * Deletes a score_table.
 */
void delete_score_table(score_table *st //!< The score_table.
);

/**
 * @brief
 * Moves to the next game in the series.
 *
 * @details
 * Increments the cu_game field of the score_table.
 *
 * @remark
 * This function is called automatically by the interface.
 */
void move_to_next_game(score_table *st //!< The score_table.
);

/**
 * @brief
 * Updates the score of a single snake in the game.
 *
 * @details
 * The score of the snake is updated after the snake dies in the game.
 *
 * @remark
 * You have to call this function in implement_turn_all_snakes defined in project_game.h
 * after a snake dies.
 */
void update_single_score(
    score_table *st, //!< The score_table.
    int i,           //!< The index of the snake in the game (in the board).
    snake *s,        //!< The snake that died
    int t //!< The time the snake remained alive before dying (given in seconds)
);

/**
 * @brief
 * Computes the final scores of the game after all the games have been played.
 *
 * @remark
 * This function is called automatically by the interface.
 */
void compute_final_scores(score_table *st //!< The score_table.
);

/**
 * @brief
 * Sorts the snakes in a score_table according to a particular type of score for a particular
 * game of the series (or the the final score).
 *
 * @details
 * The array score in the score_table must be sorted in decreasing order of the score type given
 * as a parameter.
 *
 * @remark
 * This function is called automatically by the interface.
 */
void sort_scores(score_table *st, //!< The score_table.
                 int n_g, //!< The game according to which the sort must be made
                          //!< (or nb_games for the final score).
                 score_type type //!< The score type according to which the sort
                                 //!< must be made.
);

#endif


