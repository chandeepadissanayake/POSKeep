/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 03/07/2019
 * Purpose: Implementation fo the functions for handling arrays.
 **/
#include "mdarrutils.h"
#include <stdlib.h>

int _poskeep_utils_2d_arr_last_rows = 0;
int _poskeep_utils_2d_arr_last_cols = 0;

char*** poskeep_utils_allocate_2d_arr(int rows, int cols) {
    char*** arr_ptr = (char***) malloc(rows * sizeof (char*));
    if (arr_ptr == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        arr_ptr[i] = (char**) malloc(cols * sizeof (char*));
    }

    _poskeep_utils_2d_arr_last_rows = rows;
    _poskeep_utils_2d_arr_last_cols = cols;

    return arr_ptr;
}

int poskeep_utils_get_last_2d_arr_rows() {
    return _poskeep_utils_2d_arr_last_rows;
}

int poskeep_utils_get_last_2d_arr_cols() {
    return _poskeep_utils_2d_arr_last_cols;
}

void poskeep_utils_deallocate_2d_arr(char*** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }

    free(arr);
}
