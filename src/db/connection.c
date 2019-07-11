/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 03/07/2019
 * Purpose: Implementation of the required functions required for database connection(MySQL)
 **/

#include "connection.h"
#include <mysql.h>
#include "config/db.h"
#include "utils/mdarrutils.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

MYSQL *_poskeep_db_con;
int _poskeep_db_last_error_code;

int poskeep_db_connect() {
    _poskeep_db_con = mysql_init(NULL);

    if (_poskeep_db_con == NULL) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_DB_CONNECT_CREATE_FAILED;
        return POSKEEP_ERROR_DB_CONNECT_CREATE_FAILED;
    }

    if (mysql_real_connect(_poskeep_db_con, POSKEEP_DB_HOST, POSKEEP_DB_USER, POSKEEP_DB_PWD, POSKEEP_DB_NAME, POSKEEP_DB_PORT, NULL, 0) == NULL) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_DB_CONNECT_CONNECT_FAILED;
        return POSKEEP_ERROR_DB_CONNECT_CONNECT_FAILED;
    }

    return POSKEEP_RESPONSE_DB_CONNECT_SUCCESS;
}

char*** poskeep_db_execute_query(char* query_elems[], int query_elem_count) {
    char* query;
    
    if (query_elem_count == 0) {
        query = "";
    }
    else {
        int query_char_count = 0;
        for (int i = 0; i < query_elem_count; i++) {
            query_char_count += strlen(query_elems[i]);
        }
        
        query = (char*) malloc(query_char_count * sizeof(char));
        strcpy(query, query_elems[0]);
        for (int i = 1; i < query_elem_count; i++) {
            strcat(query, query_elems[i]);
        }
    }
        
    if (mysql_query(_poskeep_db_con, query)) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_DB_QUERY_FAILED;
        if (query_elem_count != 0) {
            free(query);
        }
        return NULL;
    }
    
    if (query_elem_count != 0) {
        free(query);
    }
    
    MYSQL_RES *result = mysql_store_result(_poskeep_db_con);
    if (result == NULL) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_DB_RESULTSET_STORE_FAILED;
        return NULL;
    }

    const int count_columns = mysql_num_fields(result);
    const int count_records = mysql_num_rows(result);
    /*
     Structure of the resultset array
     =================================
     [0][0] = Number of rows in the resultset array(allocation).
     [0][1] = Number of rows in the resultset array(allocation).

     [1] = Row containing the column names in the table of the database queried.

     [2]... = Resulting Recordset
     */
    char*** resultset = (char***) poskeep_utils_allocate_2d_arr(count_records + 2, count_columns + 2);
    int resultset_row_count = poskeep_utils_get_last_2d_arr_rows();
    int resultset_column_count = poskeep_utils_get_last_2d_arr_cols();

    if (resultset == NULL) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_MEMORY_ALLOC_FAILED;
        return NULL;
    }

    // Inserting the array sizes
    resultset[0][0] = (char*)&resultset_row_count;
    resultset[0][1] = (char*)&resultset_column_count;

    // Inserting the column names
    MYSQL_FIELD* fields = mysql_fetch_fields(result);
    for (int i = 0; i < count_columns; i++) {
        resultset[1][i] = fields[i].name;
    }

    MYSQL_ROW row;
    int row_index = 2;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < count_columns; i++) {
            resultset[row_index][i] = row[i];
        }

        row_index++;
    }

    mysql_free_result(result);
    return resultset;
}

bool poskeep_db_execute_update(char** query_elems, int query_elem_count) {
    char* query;
    
    if (query_elem_count == 0) {
        query = "";
    }
    else {
        printf("1\n");
        int query_char_count = 0;
        for (int i = 0; i < query_elem_count; i++) {
            printf("ELEM: %s\n", query_elems[i]);
            query_char_count += strlen(query_elems[i]);
        }
        printf("2\n");
        
        printf("3\n");
        query = (char*) malloc(query_char_count * sizeof(char));
        printf("4\n");
        strcpy(query, query_elems[0]);
        printf("5\n");
        for (int i = 1; i < query_elem_count; i++) {
            strcat(query, query_elems[i]);
        }
        printf("6\n");
    }
    
    if (mysql_query(_poskeep_db_con, query)) {
        _poskeep_db_last_error_code = POSKEEP_ERROR_DB_QUERY_FAILED;
        if (query_elem_count != 0) {
            free(query);
        }
        return false;
    }
    
    free(query);
    
    return true;
}

void poskeep_db_free_resultset(char*** resultset, int rows) {
    poskeep_utils_deallocate_2d_arr(resultset, rows);
}

const char* poskeep_db_get_last_error() {
    return mysql_error(_poskeep_db_con);
}

int poskeep_db_get_last_error_code() {
    return _poskeep_db_last_error_code;
}

void poskeep_db_disconnect() {
    mysql_close(_poskeep_db_con);
}