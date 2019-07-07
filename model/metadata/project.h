/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 02/07/2019
 * Purpose: Definitions for different models/structures required for the program.
 **/
 
#ifndef __POSKEEP_CONSTS_PROJECT
#define __POSKEEP_CONSTS_PROJECT

typedef struct {

	char* name;
	char* stud_num;

} ProjectDeveloper;

typedef struct {

	char* title;
	ProjectDeveloper developer;
	int sub_tasks_count;
	char* *sub_tasks;

} ProjectComponent;

#endif