
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