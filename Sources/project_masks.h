/**
 * @file project_masks.h
 * @brief
 * Masks.
 *
 * @details
 * Contains the definition of the type used to represent a mask as well as the basic functions
 * that we will use to manipulate this type.
 */
#ifndef _PROJECT_MASKS_H_
#define _PROJECT_MASKS_H_


 /*  __  __    _    ____  _  ______   */
 /* |  \/  |  / \  / ___|| |/ / ___|  */
 /* | |\/| | / _ \ \___ \| ' /\___ \  */
 /* | |  | |/ ___ \ ___) | . \ ___) | */
 /* |_|  |_/_/   \_\____/|_|\_\____/  */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


 /**
 * @brief
 * Type used to represent a mask.
 *
 * @remark
 * The cells are indexed by integers ranging from 0 to hsize*vsize-1. They are ordered line by line from Top to Bottom.
 * The cell of index 0 is at the Top-Left corner. The cells ranging from 0 to hsize-1 constitute the first line at the
 * top of the grid, the cells ranging from hsize to 2*hsize-1 constitute the second line, and so on.
 *
 * @attention
 * We always assume that a mask contains at least one non-masked cell (this property must be checked when reading a mask
 * file).
 */
typedef struct {
  int hsize;    //!< Horizontal size.
  int vsize;    //!< Vertical size.
  int nbmasked; //!< Number of masked cells. Always strictly less than the total
                //!< number of cells (at least one cell must be unmasked).
  bool *grid;   //!< Boolean array indicating the masked cells. Cell i is in the
                //!< i-th case of the array (true: masked, false: unmasked).
} mask;

/**
 * @brief
 * Allocation of an empty mask on the heap: no cell is masked.
 *
 * @return
 * The mask created.
 */
mask *create_empty_mask(int hsize, //!< Horizontal size.
                        int vsize //!< Vertical size.
);

/**
 * @brief
 * Release of the memory allocated for a mask.
 */
void delete_mask(mask *m //!< The mask.
);

/**
 * @brief
 * Resizing a mask.
 *
 * @details
 *  Conversion of a mask whose dimensions are arbitrary to give it the desired dimensions.
 *
 * @attention
 * The mask must be resized to the new dimensions. The number of masked cells must be updated.
 * At least one cell must be unmasked.
 *
 */
void resize_mask(mask *m,    //!< The mask to resize.
                 int nhsize, //!< New horizontal size.
                 int nvsize  //!< New vertical size.
);

/**
 * @brief
 * Display of a mask on the terminal (useful only for testing).
 */
void print_mask(mask *m //!< The mask to display.
);

/**
 * @brief
 * Generation of a mask from a file.
 *
 * @attention
 * The file must contain an ASCII representation of the grid:
 * - The character X corresponds to a masked cell.
 * - Any other character indicates an unmasked cell.
 *
 * @remark
 * Examples of such files are given in the "Masks" directory.
 *
 * @attention
 * The file must contain a perfect rectangle (all lines must have the same length).
 * The mask must contain at least one unmasked cell. If the file does not meet these conditions, the function returns NULL.
 *
 * @return
 * The mask read in the file.
 */
mask *read_mask(const char *path //!< String containing the path to the file.
);

#endif // _PROJECT_MASKS_H_
