/**
 * 
 * @file main.c
 * 
 * This is the main project file with the tool to connect to the database
 * 
 * This is a part of the Project 2 submission for the class COMP-443 Ethical Hacking December 2025
 * 
 */


/**********************
 * Includes
 **********************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dbSetupScript.h"
#include <sqlite3.h>
#include <string.h>


/**********************
 * Prototypes
 **********************/
int chooseAction();
int queryTheDB();

int main(){
    int action = 0;
    bool isDone = false;

    do{
        action = chooseAction();
        switch (action)
        {
        case 1:
            createDB();
            break;
        case 2:
            populateDB();
            break;
        case 3:
            queryDB("SELECT * FROM EMPLOYEES");
            break;
        case 4:
            dropDB();
            break;
        case 5:
            printf("Exiting the program . . .\n");
            isDone = true;
            break;
        default:
            printf("Error action is invalid: %d", action);
            return -1;
        }
    }while(!isDone);

    return 0;
}

int chooseAction(){

    int action = 0;

    //Buffer for the input of the action
    char buff[2];
    printf("Welcome to the administrator database, choose your action:\n\n");

    while(!((action > 0) && (action < 6))){
        printf("1. Create the database for the employees\n2. Populate the database for the employees\n3. Search the address for an employee\n4. Drop the database\n5. Exit the program\n\n");
        printf("Type the number corresponding to the action you want to execute: ");

        fgets(buff, 2, stdin);

        action = atoi(buff);
        
        //Clear stdin cache after so that fgets doesn't read the \n from the stdin cache next time it is called, also has to check if \n was read into buff or is still in the stdin cache
        if(buff[strlen(buff)-1] != '\n'){
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        
        if(!((action > 0) && (action < 6))){
            printf("\n%d is not a valid action\n", action);
            printf("\n---------------------\n\nPlease enter a valid action \n\n");
        }
    }

    return action;

}