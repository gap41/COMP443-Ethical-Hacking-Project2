/**
 * 
 * @file dbSetupScript.c
 * 
 * This is the source code to create, populate and query the database
 * 
 * This is a part of the Project 3 submission for the class COMP-443 Ethical Hacking December 2025
 * 
 */


/**********************************
 * Includes
 **********************************/
#include "dbSetupScript.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

/**********************************
 * Prototypes
 **********************************/
//Callback is used to print the output of the SELECT query
static int callback(void *, int argc, char **argv, char **azColName);

/**********************************
 * Functions
 **********************************/

int createDB(){

    sqlite3 *db; // Pointer to the sqlite3 struct, could be thought of as the database object
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc; // Variable to save the status of the database function commited to check if it was successful or not
    char *sql; // pointer to point to the sql query string
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db); //Open the database, or create it if it doesn't exist

    if(rc){ //Error handling if the opening of the database failed
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }else{
        printf("Opened database successfully\n");
    }

    //The query to create the table EMPLOYEES
    sql = "CREATE TABLE EMPLOYEES(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL," \
        "USERNAME       CHAR(10)," \
        "PASSWORD       CHAR(10));"
        ;

    //Execute the SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){    //Error handling if the query fails
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);  //Freeing up the memory allocated to the zErrMsg
    }else{
        printf("The table has been created\n\n\n");
    }

    sqlite3_close(db);  //Close the database connection

}

int populateDB(){

    sqlite3 *db; // Pointer to the sqlite3 struct, could be thought of as the database object
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc; // Variable to save the status of the database function commited to check if it was successful or not
    char *sql; // pointer to point to the sql query string
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);

    if(rc){ //Error handling if the opening of the database failed
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }else{
        printf("Opened database successfully\n");
    }

    //The SQL query to populate the database
    sql = "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) "  \
         "VALUES (1, 'Anders', 34, 'Oslo', 540000, 'AND', 'password123' ); " \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) "  \
         "VALUES (2, 'Allan', 65, 'Trondheim', 870000, 'ALL', 'unicorn47' ); "     \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) " \
         "VALUES (3, 'Olav', 43, 'Revetal', 354000, 'OLA', 'OlavTheBest!44' );" \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) " \
         "VALUES (4, 'Morten', 28, 'Fredrikstad ', 550000, 'MOR', 'Password4Work123' );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // Executing the SQL query

    if(rc != SQLITE_OK){    //Error handling if the SQL query fails to execute
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg); //Freeing up the memory allocated to the zErrMsg
    }else{
        printf("The data has been added\n\n\n");
    }

    sqlite3_close(db);  //Closes the database connection

    return 0;
}

int queryDB(){

    sqlite3 *db; // Pointer to the sqlite3 struct, could be thought of as the database object
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc; // Variable to save the status of the database function commited to check if it was successful or not
    char *sql; // pointer to point to the sql query string
    const char* data = "Callback was called";

    char query[100];    // Creating a character array fitting 100 characters for the SQL query

    rc = sqlite3_open("employee.db", &db);

    if(rc){     //Error handling if the opening of the database failed
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }else{
        printf("Opened database successfully\n");
    }

    char buff[100];     // Creating a character array fitting 100 characters for the user input

    strcpy(query, "SELECT NAME, ADDRESS FROM EMPLOYEES WHERE NAME LIKE '"); // Copy the provided string into the query character array

    printf("Name: ");

    fgets(buff, 70, stdin);     // Stores the user input into the buff character array, restricts the length of the user input to avoid buffer overflow

    // Clear stdin cache after so that fgets doesn't read the \n from the stdin cache next time it is called, also has to check if \n was read into buff or is still in the stdin cache
    if(buff[strlen(buff)-1] != '\n'){
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }

    // Removes the \n index from the character array from the user input to prepare to concatenate the user input into the SQL query without the newline character
    if(buff[strlen(buff)-1] == '\n'){
        buff[strlen(buff)-1] = '\0';
    }

    //Concatenates the user input to the SQL query and then adds the apostrophe at the end
    strcat(query, buff);
    strcat(query, "'");

    // Prone to the input "'; SELECT * FROM EMPLOYEES; --" This provides the whole table
    // Also prone to drop the table by entering "'; DROP TABLE EMPLOYEES; --" This drops the table and deletes the data in the table


    sql = query;

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){    // Error handling if the query fails to execute
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg); //Freeing up the memory allocated to the zErrMsg
    }else{
        printf("Query successfully executed\n\n\n");
    }

    sqlite3_close(db);  // Close the database connection

    return 0;

}

static int callback(void *, int argc, char **argv, char **azColName){
    // Goes through each argument by using the argument counter
    // Each argument is the result of the SQL Query, e.g. SELECT
    for(int i = 0; i < argc; i++){
        if(argv[i] != NULL){
            printf("%s = %s\n", azColName[i], argv[i]);
        }else{
            printf("%s = %s\n", azColName[i], "NULL");
        }
        printf("\n");       
    }

    return 0; 

}

int dropDB(){
    
    if(remove("employee.db") == 0){ // If the database exist delete the file
        printf("Successfully deleted the database file\n\n\n");
    }else{
        perror("Error deleting the database");  // Print error if error occurs
        return -1;
    }

    return 0;
}