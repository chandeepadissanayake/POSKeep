/**
 * Author: D. M. C. Dissanayake, S. Gunasekara, H. M. K. M. Herath
 * Student No: PS/2017/035, PS/2017/050, PS/2017/064
 * Date: 02/07/2019
 * Purpose: This header contains a list of definitions for all the functions mapped to a command.
 * Note: Please define your newly added functions here and use pointers to them in the commands.h in root directory to create a proper mapping.
 **/
#pragma once

#include <stdbool.h>

/*
 Exits the POSKeep system
 */
bool poskeep_exit();

/*
 Handles Transactions.
 */
bool poskeep_transaction();

/*
 Inventory search functionality.
 */
bool poskeep_inv_search();

/*
 Inventory export functionality.
 */
bool poskeep_inv_export();
