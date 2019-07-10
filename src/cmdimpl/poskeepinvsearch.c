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
        printf("Enter the Item ID/Item Name or \"%s\" to return: ", COMMAND_DONE);
        scanf("%s", ins_keyword);

        if (strcmp(ins_keyword, COMMAND_DONE) == 0) {
            break;
        }
        else {
            char* query[] = {"SELECT * FROM `", POSKEEP_DB_TABLE_INVENTORY, "` WHERE `", POSKEEP_DB_TABLE_INVENTORY_COLUMN_ID, "` LIKE '", ins_keyword, "' OR `", POSKEEP_DB_TABLE_INVENTORY_COLUMN_ITEM_NAME, "` LIKE '", ins_keyword, "'"};
            char*** resultset = poskeep_db_execute_query(query, (sizeof(query) / sizeof(query[0])));
            if (resultset != NULL) {
                int record_count = (int)(*(int*)resultset[0][0]) - 2;
                printf("Number of Records Found: %d\n", record_count);
                
                poskeep_db_free_resultset(resultset);
            }
            else {
                printf("MySQL Error.\nError Message: %s\n", poskeep_db_get_last_error());
            }
        }
    }

    return true;
}
