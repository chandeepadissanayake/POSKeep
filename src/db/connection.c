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

MYSQL *_poskeep_db_con;

int poskeep_db_connect() {
	_poskeep_db_con = mysql_init(NULL);

	if (_poskeep_db_con == NULL) {
		return POSKEEP_ERROR_DB_CONNECT_CREATE_FAILED;
	}

	if (mysql_real_connect(_poskeep_db_con, POSKEEP_DB_HOST, POSKEEP_DB_USER, POSKEEP_DB_PWD, POSKEEP_DB_NAME, POSKEEP_DB_PORT, NULL, 0) == NULL) {
		return POSKEEP_ERROR_DB_CONNECT_CONNECT_FAILED;
	}

	return POSKEEP_RESPONSE_DB_CONNECT_SUCCESS;
}

char*** poskeep_db_execute_query(char* query) {
	if (!mysql_query(_poskeep_db_con, query)) {
		return POSKEEP_ERROR_DB_QUERY_FAILED;
	}

	MYSQL_RES *result = mysql_store_result(_poskeep_db_con);
	if (result == NULL) {
		return POSKEEP_ERROR_DB_RESULTSET_STORE_FAILED;
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

	if (resultset == NULL) {
		return POSKEEP_ERROR_MEMORY_ALLOC_FAILED;
	}

	// Inserting the array sizes
	resultset[0][0] = poskeep_utils_get_last_2d_arr_rows();
	resultset[0][1] = poskeep_utils_get_last_2d_arr_cols();

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

void poskeep_db_free_resultset(char*** resultset) {
	int rows = resultset[0][0];
	poskeep_utils_deallocate_2d_arr(resultset, rows);
}

char* poskeep_db_get_last_error() {
	return mysql_error(_poskeep_db_con);
}

void poskeep_db_disconnect() {
	mysql_close(_poskeep_db_con);
}