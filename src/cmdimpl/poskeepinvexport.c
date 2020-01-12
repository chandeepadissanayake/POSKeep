
/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 26/10/2019
 * Purpose: Performs a search in the inventory using user provided data and exports them to the given path.
 **/

#include "impl.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "consts/commands.h"
#include "db/connection.h"
#include "consts/database.h"
#include "consts/dbtables.h"
#include "utils/fileutils.h"

#define MAX_PATH_LENGTH 260
#define MAX_DB_ID_LENGTH 11

bool poskeep_inv_export() {
    // Prompts the user for the path of the input file.
    char ins_path_to_input_file[MAX_PATH_LENGTH];
    printf("Please enter the absolute path to the file containing database IDs of the items to search for or \"%s\" to cancel: ", COMMAND_CANCEL);
    scanf(" %s", ins_path_to_input_file);

    // Checks whether the input is not a path but the command to cancel the process.
    if (strcmp(ins_path_to_input_file, COMMAND_CANCEL) == 0) {
        printf("Successfully cancelled.\n");
    }
    else {
        // Setting up file pointers and starts reading the file.
        FILE *fp_ins;
        fp_ins = fopen(ins_path_to_input_file, "r");

        if (fp_ins != NULL) {
            // Prompts the user for the path of the output file.
            char ins_path_to_output_file[MAX_PATH_LENGTH];
            printf("Please enter the absolute path to the file to output results or \"%s\" to cancel: ", COMMAND_CANCEL);
            scanf(" %s", ins_path_to_output_file);

            // Checks whether the input is not a path but the command to cancel the process.
            if (strcmp(ins_path_to_output_file, COMMAND_CANCEL) == 0) {
                printf("Successfully cancelled.\n");
            }
            else {
                /**
                 * Calculates the length of the file inputs as follows.
                 * Then declares the array to save the IDs contained in the file.
                 * Each line should contain an integer with a maximum length of MAX_DB_ID_LENGTH
                 * Such single entry is counted as one line.
                 * Array to save file data would be of the size number of lines in the file * MAX_DB_ID_LENGTH
                 */
                int ins_file_ids_count = _poskeep_count_lines_file(ins_path_to_input_file);
                char ids_to_search[ins_file_ids_count][MAX_DB_ID_LENGTH];

                // Declares the buffer and reads the file into the array.
                int index_id = 0;
                char buf[MAX_DB_ID_LENGTH];
                while (fgets(buf, MAX_DB_ID_LENGTH, fp_ins) != NULL) {
                    buf[strcspn(buf, "\n")] = 0;
                    strcpy(ids_to_search[index_id++], buf);
                }
                
                // Create the output file and sets it up to be written.
                FILE *fp_outs;
                fp_outs = fopen(ins_path_to_output_file, "w");
                if (fp_outs != NULL) {
                    // Starts writing to the file.
                    for (int search_index = 0; search_index < ins_file_ids_count; search_index++) {
                        // Executes the query for the database ID.
                        char* query[] = {"SELECT * FROM `", POSKEEP_DB_TABLE_INVENTORY, "` WHERE `", POSKEEP_DB_TABLE_INVENTORY_COLUMN_ID, "` = '", ids_to_search[search_index], "'"};
                        char*** resultset = poskeep_db_execute_query(query, (sizeof(query) / sizeof(query[0])));

                        if (resultset != NULL) {
                            int record_count = (int)(*(int*)resultset[0][0]) - 2; // This value should be 1 only if the database IDs are not duplicated.
                            int columns_count = (int)(*(int*)resultset[0][1]) - 2;

                            // Writing the column names to the file, if they weren't written earlier.
                            if (search_index == 0) {
                                for (int column_index = 0; column_index < columns_count; column_index++) {
                                    fprintf(fp_outs, "%-25s", resultset[1][column_index]);
                                }
                                fprintf(fp_outs, "\n");
                            }
                            
                            // Writing the records to the file. It is safe to assume there is only one record here, but just to be safe, we use a loop.
                            for (int record_index = 0; record_index < record_count; record_index++) {
                                for (int column_index = 0; column_index < columns_count; column_index++) {
                                    fprintf(fp_outs, "%-25s", resultset[record_index + 2][column_index]);
                                }
                                fprintf(fp_outs, "\n");
                            }

                            poskeep_db_free_resultset(resultset, record_count + 2);
                        }
                        else {
                            printf("MySQL Error at the database ID: %s.\nError Message: %s\n", ids_to_search[search_index], poskeep_db_get_last_error());
                        }
                    }

                    printf("Successfully exported to: %s\n", ins_path_to_output_file);
                }
                else {
                    printf("Failed to open the file for writing.\n");
                }
            }
        }
        else {
            printf("Failed to open the file for reading.\n");
        }
    }

    return true;
}