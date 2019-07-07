/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 02/07/2019
 * Purpose: Definitions for different models/structures required for mapping string commands to function pointers.
 **/

#include <stdbool.h>
#include <stdlib.h>

#ifndef __POSKEEP_MODEL_COMMANDS
#define __POSKEEP_MODEL_COMMANDS

typedef struct {

	char cmd;
	bool (*func_ptr)();
	char* help_str;

} CommandMapping;

void create_command_mapping(CommandMapping *cmd_mapping, char ch_cmd, bool (*func_ptr)(), char* help_str);

#endif