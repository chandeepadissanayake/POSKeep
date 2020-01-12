/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 04/07/2019
 * Purpose: Implementation of the functions in string utilities.
 **/

#include "strutils.h"
#include <stdlib.h>

char* float_to_string(float value) {
    char* buffer = malloc((NUM_DIGITS_FLOAT_TO_STRING + 1) * sizeof(char));
    gcvt(value, NUM_DIGITS_FLOAT_TO_STRING + 1, buffer);
    return buffer;
}
