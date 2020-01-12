
/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 11/01/2020
 * Purpose: Inserts transactions to the database using a data file.
 **/

#include "impl.h"
#include <stdio.h>
#include <stdbool.h>
#include "consts/commands.h"
#include "utils/fileutils.h"
#include <stdlib.h>
#include <string.h>
#include "consts/database.h"
#include "consts/dbtables.h"
#include "utils/strutils.h"
#include "db/connection.h"

#define MAX_INPUT_LENGTH 40
#define MAX_PATH_LENGTH 260
#define MAX_INPUT_FLOAT_LENGTH 10

const char* INPUT_FILE_DELIMITER = ";";

// Struct for encapsulating transaction data.
typedef struct file_data_transaction {
    char customer_name[MAX_INPUT_LENGTH];
    float total_cost;
    float discount;
    float final_cost;
    float payment;
} FileDataTransaction;

// Function to read transaction data in the file to the array. (read_data function)
void _poskeep_transactions_read_file(FILE* fp_ins, FileDataTransaction* file_data_records) {
    const int line_length = MAX_INPUT_LENGTH + (4 * MAX_INPUT_FLOAT_LENGTH); // As there are 4 float type values in the line
    char file_record[line_length];

    int record_index = 0;
    while (fgets(file_record, line_length, fp_ins) != NULL) {
        FileDataTransaction* file_data_record = file_data_records + record_index;
        strcpy(file_data_record->customer_name, strtok(file_record, INPUT_FILE_DELIMITER));
        file_data_record->total_cost = atof(strtok(NULL, INPUT_FILE_DELIMITER));
        file_data_record->discount = atof(strtok(NULL, INPUT_FILE_DELIMITER));
        file_data_record->final_cost = atof(strtok(NULL, INPUT_FILE_DELIMITER));
        file_data_record->payment = atof(strtok(NULL, INPUT_FILE_DELIMITER));

        record_index++;
    }
}

// Function to process/insert the transaction data into the databases.
void _poskeep_transactions_insert_db(FileDataTransaction* file_data_records, int file_records_count) {
    for (int record_index = 0; record_index < file_records_count; record_index++) {
        FileDataTransaction* file_data_record = file_data_records + record_index;

        // Generates a query and executes it on the databases.
        char* query[] = {"INSERT INTO `", POSKEEP_DB_TABLE_TRANSACTIONS, "` (`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_ID, "`,`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_CUSTOMER_NAME, "`,`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_TOTAL_COST, "`,`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_DISCOUNT, "`,`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_FINAL_COST, "`,`",
            POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_PAYMENT, "`) VALUES (",
            
            "NULL", ", '",
            file_data_record->customer_name, "', '",
            float_to_string(file_data_record->total_cost), "', '",
            float_to_string(file_data_record->discount), "', '",
            float_to_string(file_data_record->final_cost), "', '",
            float_to_string(file_data_record->payment),  "')",
        };
        poskeep_db_execute_query(query, (sizeof(query) / sizeof(query[0])));
    }
}

bool poskeep_transactions_insert() {
    // Prompts the user for the path of the input file.
    char ins_path_to_input_file[MAX_PATH_LENGTH];
    printf("Please enter the absolute path to the file containing the transactions' details or \"%s\" to cancel: ", COMMAND_CANCEL);
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
            // Counting the number of records in the file.
            int input_record_count = _poskeep_count_lines_file(ins_path_to_input_file);

            // Dynamically allocates memory to the array of records for the above number of records.
            FileDataTransaction* file_data_records = (FileDataTransaction*) malloc(input_record_count * sizeof(FileDataTransaction));
            // Reads data in the file into the array of FileDataTransaction.
            _poskeep_transactions_read_file(fp_ins, file_data_records);
            // Processes the data - Inserts them into the database.
            _poskeep_transactions_insert_db(file_data_records, input_record_count);

            printf("Successfully added transactions to the database.\n");
        }
        else {
            printf("Cannot read the file correctly.\n");
        }
    }

    return true;
}
