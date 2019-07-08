/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 03/07/2019
 * Purpose: Implementation of the connecting functions to the MySQL Databases.
 **/

#include "databases.h"
#include "db/connection.h"
#include <stdio.h>
#include "config/db.h"
#include <stdlib.h>

void poskeep_databases_init() {
	int connect_status = poskeep_db_connect();
	if (connect_status != POSKEEP_RESPONSE_DB_CONNECT_SUCCESS) {
		printf("Failed to Connect to the MySQL Databases at %s@%s:%d; using password:%s\n", POSKEEP_DB_USER, POSKEEP_DB_HOST, POSKEEP_DB_PORT, (POSKEEP_DB_PWD != "" ? "YES" : "NO"));
		printf("Error Message: %s", poskeep_db_get_last_error());
		exit(connect_status);
	}
}
