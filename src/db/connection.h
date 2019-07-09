/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 03/07/2019
 * Purpose: Including the functions required for connecting to databases(MySQL)
 **/
#pragma once

/*
 Constants
 */
#define POSKEEP_ERROR_DB_CONNECT_CREATE_FAILED -1
#define POSKEEP_ERROR_DB_CONNECT_CONNECT_FAILED -2
#define POSKEEP_ERROR_DB_QUERY_FAILED -3
#define POSKEEP_ERROR_DB_RESULTSET_STORE_FAILED -4

#define POSKEEP_RESPONSE_DB_CONNECT_SUCCESS 1

/*
 Connects to the MySQL Database using the credentials provided at config/db.h
 */
int poskeep_db_connect();

/*
 Executes SELECT queries on MySQL Database and returns an array formatted as follows.
 Row Index		Column Index		Data
 0				0					Number of Rows in the resultset array(Subtract 2 by this value to obtain the number of records returned by query)
 0				1					Number of Columns in the resultset array(Subtract 2 by this value to obtain the number of columns in the table in the database queried)
 1				(Any)				Names of Columns in the table of the database queried.
 
 From Row #2 onwards there will be the records returned by the query.
 */
char*** poskeep_db_execute_query(char* query);

/*
 Used to free up the memory used by a resultset returned by executing poskeep_db_execute_query function.
 This must be called once the resultset array is useless.
 */
void poskeep_db_free_resultset(char*** resultset);

/*
 Returns the last error encountered by MySQL Connection.
 */
const char* poskeep_db_get_last_error();

/*
 Used to obtain the error code associated with the last error.
 */
int poskeep_db_get_last_error_code();

/*
 Disconnects from the MySQL databases.
 This must be called once the use of MySQL connection is over
 */
void poskeep_db_disconnect();