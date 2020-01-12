/**
 * Author(s): D. M. C. Dissanayake, S. Gunasekara, H. M. K. M. Herath
 * Student No: PS/2017/035, PS/2017/050, PS/2017/064
 * Date: 07/07/2019
 * Purpose: Handling transactions.
 **/

#include "impl.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "consts/commands.h"
#include "db/connection.h"
#include "consts/database.h"
#include "consts/dbtables.h"
#include <stdlib.h>
#include "utils/strutils.h"

#define MAX_INPUT_LENGTH 40
#define MAX_NUM_SIZE 100

float pt_total_cost, pt_discount, pt_final_cost, pt_payment, pt_balance;
char pt_customer_name[MAX_INPUT_LENGTH];

void _poskeep_transaction_reset() {
    pt_total_cost = 0.0f;
    pt_discount = 0.0f;
    pt_final_cost = 0.0f;
    pt_payment = 0.0f;
    pt_balance = 0.0f;
}

bool _poskeep_transaction_handle_item_list() {
    printf("Item List Purchased:\n");
    printf("======================\n");
    while (true) {
        char ins_db_id_item[MAX_INPUT_LENGTH];
        printf("Please Enter the ID of the Item: ");
        scanf(" %s", ins_db_id_item);
        
        if (strcmp(ins_db_id_item, COMMAND_CANCEL) == 0) {
            return false;
        }
        else if (strcmp(ins_db_id_item, COMMAND_DONE) == 0) {
            break;
        }
        else {
            bool is_num = true;
            for (int i = 0; i < strlen(ins_db_id_item); i++) {
                if (!isdigit(ins_db_id_item[i])) {
                    is_num = false;
                    break;
                }
            }
            
            if (is_num) {
                char* query[] = {"SELECT * FROM `", POSKEEP_DB_TABLE_INVENTORY, "` WHERE `", POSKEEP_DB_TABLE_INVENTORY_COLUMN_ID, "`='", ins_db_id_item, "'"};
                char*** resultset = poskeep_db_execute_query(query, (sizeof(query) / sizeof(query[0])));
                
                if (resultset != NULL) {
                    int record_count = (int)(*(int*)resultset[0][0]) - 2;
                    int column_count = (int)(*(int*)resultset[0][1]) - 2;
                    if (record_count > 0) {
                        char* item_name;
                        int unit_price;
                        for (int i = 0; i < column_count; i++) {
                            if (strcmp(resultset[1][i], POSKEEP_DB_TABLE_INVENTORY_COLUMN_ITEM_NAME) == 0) {
                                item_name = resultset[2][i];
                            }
                            else if (strcmp(resultset[1][i], POSKEEP_DB_TABLE_INVENTORY_COLUMN_UNIT_PRICE) == 0) {
                                unit_price = atoi(resultset[2][i]);
                                break;
                            }
                        }
                        
                        printf("Item %s has a unit price of %d\n", item_name, unit_price);
                        
                        float purchase_quantity;
                        printf("Please enter the quantity to purchase(complying with the appropriate units): ");
                        scanf(" %f", &purchase_quantity);
                        
                        float item_cost = unit_price * purchase_quantity;
                        pt_total_cost += item_cost;
                        printf("Cost for %s = %g\n", item_name, item_cost);
                        printf("Outstanding Total Cost = %g\n", pt_total_cost);
                    }
                    else {
                        printf("Error: There is no such item in the inventory with the ID number you've provided.");
                    }
                    
                    poskeep_db_free_resultset(resultset, record_count + 2);
                }
                else {
                    printf("MySQL Error.\nError Message: %s\n", poskeep_db_get_last_error());
                }
            }
            else {
                printf("Invalid Input\n");
            }
        }
    }
    
    printf("Please enter the discount amount(if there isn't, enter 0): ");
    scanf(" %f", &pt_discount);

    pt_final_cost = pt_total_cost - pt_discount;
    printf("Final Cost = %g\n", pt_final_cost);

    printf("Please enter the Paid Amount: ");
    scanf("%f", &pt_payment);

    pt_balance = pt_payment - pt_final_cost;
    printf("Balance = %g\n", pt_balance);
    
    printf("End of the Item List Purchased\n");
    printf("===============================\n");
    
    return true;
}

bool _poskeep_transaction_get_customer_details() {
    printf("Details of the Customer\n");
    printf("========================\n");
    
    printf("Customer Name(40 characters) or type \"-\" if unknown: ");
    scanf(" %s", pt_customer_name);
    
    printf("End of Customer Details\n");
    printf("========================\n");
    
    return strcmp(pt_customer_name, COMMAND_CANCEL) != 0;
}

bool _poskeep_transaction_db_insert() {
    char* tmp_customer_name = (pt_customer_name != NULL) ? pt_customer_name : "";
    char* tmp_total_cost = float_to_string(pt_total_cost);
    char* tmp_discount = float_to_string(pt_discount);
    char* tmp_final_cost = float_to_string(pt_final_cost);
    char* tmp_payment = float_to_string(pt_payment);
    
    char* query[] = {
        "INSERT INTO `", POSKEEP_DB_TABLE_TRANSACTIONS, "`(`", 
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_ID, "`,`"
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_CUSTOMER_NAME, "`,`",
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_TOTAL_COST, "`,`",
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_DISCOUNT, "`,`",
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_FINAL_COST, "`,`",
        POSKEEP_DB_TABLE_TRANSACTIONS_COLUMN_PAYMENT, "`) VALUES (",

        "null", ",'",
        tmp_customer_name, "','",
        tmp_total_cost, "','",
        tmp_discount, "','",
        tmp_final_cost, "','",
        tmp_payment,"')",
    };
    bool state_ins_query = poskeep_db_execute_update(query, (sizeof(query) / sizeof(query[0])));
    free(tmp_total_cost);
    free(tmp_discount);
    free(tmp_final_cost);
    free(tmp_payment);
    
    if (state_ins_query) {
        printf("Transaction successfully recorded in the database.\n");
    }
    else {
        printf("Transaction was processed but an unexpected error occurred while trying to record in the database.\n");
    }
    
    return true;
}

bool poskeep_transaction() {
    _poskeep_transaction_reset();
    printf("New Transaction\n");
    printf("================\n");
    
    if (_poskeep_transaction_handle_item_list()) {
        _poskeep_transaction_get_customer_details();
        
        char ins_conf;
        printf("Confirm the transaction; y(for yes) or any other letter(for no): ");
        scanf(" %c", &ins_conf);

        if (ins_conf == 'y') {
            _poskeep_transaction_db_insert();
        }
        else {
            printf("Transaction was cancelled.\n");
        }
    }
    
    return true;
}
