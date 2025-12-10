/**
 * 
 * @file main.c
 * 
 * This is the main project file with the tool to connect to the database
 * 
 * This is a part of the Project 3 submission for the class COMP-443 Ethical Hacking December 2025
 * 
 * To compile the program the flag "-l sqlite3" is necessary e.g. : gcc *.c -l sqlite3 -o main
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

    int action = 0; // Store the input of the user
    bool isDone = false;    // Turns to true if the user chooses action 5 to exit the program

    do{     // Do-while looping until user wishes to exit the program
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
            queryDB();
            break;
        case 4:
            dropDB();
            break;
        case 5:
            printf("Exiting the program . . .\n");
            isDone = true;
            break;
        default:
            printf("Error action is invalid: %d", action);  // Error clause if the chooseAction() function returns an invalid number
            return -1;
        }
    }while(!isDone);

    return 0;
}

int chooseAction(){

    int action = 0;

    char buff[2]; // Buffer for the input of the action
    printf("Welcome to the employee database query tool, choose your action:\n\n");

    while(!((action > 0) && (action < 6))){
        printf("1. Create the database for the employees\n2. Populate the database for the employees\n3. Search the address for an employee\n4. Drop the database\n5. Exit the program\n\n");
        printf("Type the number corresponding to the action you want to execute: ");

        fgets(buff, 2, stdin);  // Store the user input to buff, limit the user input to two characters

        action = atoi(buff);    // Converts the string to an integer
        
        //Clear stdin cache after so that fgets doesn't read the \n from the stdin cache next time it is called, also has to check if \n was read into buff or is still in the stdin cache
        if(buff[strlen(buff)-1] != '\n'){
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        
        // Let user know if it is not a valid choice
        if(!((action > 0) && (action < 6))){
            printf("\n%d is not a valid action\n", action);
            printf("\n---------------------\n\nPlease enter a valid action \n\n");
        }
    }

    return action;

}