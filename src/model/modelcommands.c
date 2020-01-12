
#include <stdio.h>
#include "modelcommands.h"

void create_command_mapping(CommandMapping* cmd_mapping, char ch_cmd, bool(*func_ptr)(), char* help_str) {
    *cmd_mapping = *(CommandMapping*) malloc(sizeof (CommandMapping));
    if (cmd_mapping != NULL) {
        cmd_mapping->cmd = ch_cmd;
        cmd_mapping->func_ptr = func_ptr;
        cmd_mapping->help_str = help_str;
    }
}
