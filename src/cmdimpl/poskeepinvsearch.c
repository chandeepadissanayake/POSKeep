/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 04/07/2019
 * Purpose: Performs a search in the inventory using user provided data.
 **/

#include "impl.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "db/connection.h"
#include "consts/database.h"
#include "consts/dbtables.h"

const char* COMMAND_DONE = "[done]";

bool poskeep_inv_search() {
	while (true) {
		char* ins_keyword;
		printf("Enter the Item ID/Item Name or \"%s\" to return: \n", COMMAND_DONE);
		scanf("%s", ins_keyword);
		
		if (ins_keyword == COMMAND_DONE) {
			break;
		}
		else {
			// TODO: Code here: Make the query work.
			char*** resultset = poskeep_db_execute_query(strcat("SELECT * FROM `", strcat(POSKEEP_DB_TABLE_INVENTORY, "` WHERE `")));
		}
	}
	
    return true;
}
