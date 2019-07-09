/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 02/07/2019
 * Purpose: Entry Point for the POSKeep.
 **/

#include "databases.h"
#include "welcome.h"
#include "commands.h"

/*
 Entry point to the program
 */
void main() {
    poskeep_databases_init();
    poskeep_print_welcome();
    poskeep_handle_commands();
}