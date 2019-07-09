/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 02/07/2019
 * Purpose: Handling the Commands from the Command Line.
 **/

#include <stdbool.h>
#include <stdio.h>
#include <string.h> 

#include "commands.h"
#include "model/modelcommands.h"

/*
Each an every mapping must be created with a create_command_mapping call.
This must include the following arguments.
        1. The character input by the user which is used to map the command.
        2. The function pointer with the return type bool and returning false only in the case, receipt of exit command.
        3. A help string which describes what is the purpose of the command.
 Note: Initialize mappings as decribed above in _poskeep_init_commands function
 */
CommandMapping* POSKEEP_COMMAND_MAPPINGS = NULL;

bool _poskeep_process_command(char *ins_ptr) {
    for (int i = 0; i < (sizeof (*POSKEEP_COMMAND_MAPPINGS) / sizeof (POSKEEP_COMMAND_MAPPINGS[0])); i++) {
        CommandMapping curr_cmd_mapping = POSKEEP_COMMAND_MAPPINGS[i];
        if (curr_cmd_mapping.cmd == *ins_ptr) {
            bool(*func)() = curr_cmd_mapping.func_ptr;
            return func();
        }
    }
}

bool _poskeep_grab_commands() {
    char ins;
    printf("Please enter a command to continue: ");
    scanf("%c", &ins);
    return _poskeep_process_command(&ins);
}

void _poskeep_init_commands() {
    CommandMapping cmdmap_exit;
    create_command_mapping(&cmdmap_exit, 'e', poskeep_exit, "Exits the POSKeep system");
    
    CommandMapping cmdmap_inv_search;
    create_command_mapping(&cmdmap_inv_search, 'i', poskeep_inv_search, "Search the Inventory for specific items");

    CommandMapping tmp_cmd_mappings[] = {
        cmdmap_exit,
        cmdmap_inv_search,
    };

    POSKEEP_COMMAND_MAPPINGS = malloc(sizeof (tmp_cmd_mappings));
    for (int i = 0; i < (sizeof (tmp_cmd_mappings) / sizeof (tmp_cmd_mappings[0])); i++) {
        POSKEEP_COMMAND_MAPPINGS[i] = tmp_cmd_mappings[i];
    }
}

void poskeep_handle_commands() {
    _poskeep_init_commands();

    bool exit_flag = false;
    while (!exit_flag) {
        exit_flag = !_poskeep_grab_commands();
    }
}
