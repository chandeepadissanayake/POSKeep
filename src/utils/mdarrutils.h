/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 03/07/2019
 * Purpose: Functions for handling arrays.
 **/
#pragma once

/*
 Constants
 */
#define POSKEEP_ERROR_MEMORY_ALLOC_FAILED -5

/*
 Allocates memory for a 2-Dimensional Array and returns a pointer to it.
 */
char*** poskeep_utils_allocate_2d_arr(int rows, int cols);

/*
 Returns the number of rows in the last allocated 2-Dimensional array.
*/
int poskeep_utils_get_last_2d_arr_rows();

/*
 Returns the number of columns in the last allocated 2-Dimensional array.
*/
int poskeep_utils_get_last_2d_arr_cols();

/*
 Deallocates and frees up memory used for a 2-Dimensional array.
 */
void poskeep_utils_deallocate_2d_arr(char*** arr, int rows);
