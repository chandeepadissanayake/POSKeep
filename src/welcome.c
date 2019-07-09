/**
 * Author: D. M. C. Dissanayake
 * Student No: PS/2017/035
 * Date: 02/07/2019
 * Purpose: Welcome Screen of the POSKeep(Point Of Sale Application)
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "welcome.h"
#include "consts/poskeep.h"
#include "model/metadata/project.h"
/*
 Following constants can be changed based on the need.
 */
#define HEAD_LENGTH 30
#define COMPONENT_COUNT 3

ProjectDeveloper PROJECT_DEVELOPERS[COMPONENT_COUNT];
ProjectComponent PROJECT_COMPONENTS[COMPONENT_COUNT];

/*
 Initialize variables.
 Sets values to constants
 Memory allocated by malloc under this function is not freed up as data in those memory blocks are required throughout the program.
 */
void _poskeep_init_project_details() {
    ProjectDeveloper developer_1 = {
        "D. M. C. Dissanayake",
        "PS/2017/035"
    };
    ProjectDeveloper developer_2 = {
        "S. Gunasekara",
        "PS/2017/050"
    };
    ProjectDeveloper developer_3 = {
        "H. M. K. M. Herath",
        "PS/2017/064"
    };

    ProjectDeveloper project_developers[] = {
        developer_1,
        developer_2,
        developer_3
    };
    for (int i = 0; i < (sizeof (project_developers) / sizeof (project_developers[0])); i++) {
        PROJECT_DEVELOPERS[i] = project_developers[i];
    }

    char* component_1_tasks[] = {
        "Filling all the details required inside the loop",
        "Calculation of the bill, discounts and balance"
    };
    ProjectComponent component_1 = {
        "Processing Real time Transactions",
        PROJECT_DEVELOPERS[2],
        (sizeof (component_1_tasks) / sizeof (component_1_tasks[0]))
    };
    component_1.sub_tasks = (char**) malloc(sizeof (component_1_tasks));
    for (int i = 0; i < component_1.sub_tasks_count; i++) {
        component_1.sub_tasks[i] = component_1_tasks[i];
    }

    char* component_2_tasks[] = {
        "Inserting Transactions into the Database",
        "Updating Transactions in the Database",
        "Deleting Transactions in the Database"
    };
    ProjectComponent component_2 = {
        "Storage of Transaction data in the Database",
        PROJECT_DEVELOPERS[1],
        (sizeof (component_2_tasks) / sizeof (component_2_tasks[0]))
    };
    component_2.sub_tasks = (char**) malloc(sizeof (component_2_tasks));
    for (int i = 0; i < component_2.sub_tasks_count; i++) {
        component_2.sub_tasks[i] = component_2_tasks[i];
    }

    char* component_3_tasks[] = {
        "Adding new items to the inventory",
        "Searching/Querying items in the inventory",
        "Modifying existing items in the inventory",
        "Removing/Deleting existing items in the inventory"
    };
    ProjectComponent component_3 = {
        "CRUD Operations for the Stock Management",
        PROJECT_DEVELOPERS[0],
        (sizeof (component_3_tasks) / sizeof (component_3_tasks[0]))
    };
    component_3.sub_tasks = (char**) malloc(sizeof (component_3_tasks));
    for (int i = 0; i < component_3.sub_tasks_count; i++) {
        component_3.sub_tasks[i] = component_3_tasks[i];
    }

    ProjectComponent project_components[] = {
        component_1,
        component_2,
        component_3
    };
    for (int i = 0; i < (sizeof (project_components) / sizeof (project_components[0])); i++) {
        PROJECT_COMPONENTS[i] = project_components[i];
    }
}

/*
 Prints the header for the welcome screen
 */
void _poskeep_print_head() {
    for (int x = 0; x < HEAD_LENGTH; x++) {
        printf("=");
    }
    printf("\n");

    for (int x = 0; x < HEAD_LENGTH; x++) {
        printf("*");
    }
    printf("\n");

    printf("%s", PROJECT_TITLE);
    printf("\n");

    for (int x = 0; x < HEAD_LENGTH; x++) {
        printf("*");
    }
    printf("\n");

    for (int x = 0; x < HEAD_LENGTH; x++) {
        printf("=");
    }
    printf("\n");
}

/*
 Prints the details about the project
 */
void _poskeep_print_project_details() {
    printf("Project Title: %s\n", PROJECT_TITLE);
    printf("Purpose: %s\n", PROJECT_PURPOSE);
    printf("Developers: \n");
    for (int i = 0; i < (sizeof (PROJECT_DEVELOPERS) / sizeof (PROJECT_DEVELOPERS[0])); i++) {
        printf("\t\t%s - %s\n", PROJECT_DEVELOPERS[i].name, PROJECT_DEVELOPERS[i].stud_num);
    }
    printf("Components: \n");
    for (int i = 0; i < (sizeof (PROJECT_COMPONENTS) / sizeof (PROJECT_COMPONENTS[0])); i++) {
        printf("\t\t%d. %s\n", i + 1, PROJECT_COMPONENTS[i].title);
    }
}

/*
 User input requiring function to print out details about specific components.
 */
bool _poskeep_request_learn_more() {
    printf("Please enter component number you wish learn more or \"-1\" to continue:");
    int index_component;
    scanf("%d", &index_component);

    if (index_component > 0 && index_component <= COMPONENT_COUNT) {
        ProjectComponent project_component = PROJECT_COMPONENTS[index_component - 1];
        printf("Additional Details about the component %d\n", index_component);
        printf("Component: %s\n", project_component.title);
        printf("Developer: %s (%s)\n", project_component.developer.name, project_component.developer.stud_num);
        printf("Tasks:\n");
        for (int i = 0; i < project_component.sub_tasks_count; i++) {
            printf("\t\t%s\n", project_component.sub_tasks[i]);
        }
    } else if (index_component < 0) {
        return false;
    } else {
        printf("Invalid Input\n");
    }

    return true;
}

/*
 Prints out the entire welcome screen.
 */
void poskeep_print_welcome() {
    _poskeep_init_project_details();
    _poskeep_print_head();
    _poskeep_print_project_details();

    bool flag_continue = false;
    while (!flag_continue) {
        flag_continue = !_poskeep_request_learn_more();
    }
}