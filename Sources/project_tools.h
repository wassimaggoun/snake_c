/**
 * @file project_tools.h
 *
 * @brief
 * Tools.
 *
 * @details
 * A few macros that you can use in your project. Also contains the get_time_counter function.
 * It returns the time spent since the start of an ongoing game (in milliseconds). This is the
 * function that you should use in order to compute the time a snake spent alive when filling
 * an entry in the score table.
 *
 * @remark
 * You should NOT modify this file.
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

 /*  _____           _      */
 /* |_   _|__   ___ | |___  */
 /*   | |/ _ \ / _ \| / __| */
 /*   | | (_) | (_) | \__ \ */
 /*   |_|\___/ \___/|_|___/ */

/**
 * @brief
 * Macro to get the maximum of two values.
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief
 * Macro to get the minimum of two values.
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief
 * Macro to swap two values.
 */
#define SWAP(a, b) { typeof(a) temp = a; a = b; b = temp; }


/**
 * @brief
 * Initializes the time counter.
 *
 * @remark
 * This function is called by the interface. You should NOT call it yourself.
 */
void init_time_counter(void);

/**
 * @brief
 * Pauses the time counter.
 *
 * @remark
 * This function is called by the interface. You should NOT call it yourself.
 */
void pause_time_counter(void);

/**
 * @brief
 * Resumes the time counter.
 *
 * @remark
 * This function is called by the interface. You should NOT call it yourself.
 */
void resume_time_counter(void);

/**
 * @brief
 * Gets the time counter.
 *
 * @return
 * The time counter in milliseconds.
 *
 * @remark
 * This is function that you can call to retrieve the time a snake spent alive to fill a score table.
 */
int get_time_counter(void);




#endif
