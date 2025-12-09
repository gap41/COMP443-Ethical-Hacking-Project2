/**
 * 
 * @file dbSetupScript.c
 * 
 * This is the source code to create, populate and query the database
 * 
 * This is a part of the Project 2 submission for the class COMP-443 Ethical Hacking December 2025
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
static int callback(void *, int argc, char **argv, char **azColName);

/**********************************
 * Functions
 **********************************/

int createDB(){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);


    if(rc){
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        printf("Opened database successfully\n");
    }

    sql = "CREATE TABLE EMPLOYEES(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL," \
        "USERNAME       CHAR(10)," \
        "PASSWORD       CHAR(10));"
        ;

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("The table has been created\n\n\n");
    }

    sqlite3_close(db);

}

int populateDB(){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);

    if(rc){
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        printf("Opened database successfully\n");
    }

    sql = "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) "  \
         "VALUES (1, 'Anders', 34, 'Oslo', 540000, 'AND', 'password123' ); " \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) "  \
         "VALUES (2, 'Allan', 65, 'Trondheim', 870000, 'ALL', 'unicorn47' ); "     \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) " \
         "VALUES (3, 'Olav', 43, 'Revetal', 354000, 'OLA', 'OlavTheBest!44' );" \
         "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY, USERNAME, PASSWORD) " \
         "VALUES (4, 'Morten', 28, 'Fredrikstad ', 550000, 'MOR', 'Password4Work123' );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("The data has been added\n\n\n");
    }

    sqlite3_close(db);

    return 0;
}

int queryDB(){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    char query[100];

    rc = sqlite3_open("employee.db", &db);

    if(rc){
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        printf("Opened database successfully\n");
    }

    char buff[100];

    strcpy(query, "SELECT NAME, ADDRESS FROM EMPLOYEES WHERE NAME LIKE '");

    printf("Name: ");

    fgets(buff, 70, stdin);

    //Clear stdin cache after so that fgets doesn't read the \n from the stdin cache next time it is called, also has to check if \n was read into buff or is still in the stdin cache
    if(buff[strlen(buff)-1] != '\n'){
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }

    if(buff[strlen(buff)-1] == '\n'){
        buff[strlen(buff)-1] = '\0';
    }

    strcat(query, buff);
    strcat(query, "'");

    // Prone to the input "'; OR 1=1; --" and "'; SELECT * FROM EMPLOYEES; --" This provides the whole table
    // Also prone to drop the table by entering "'; DROP TABLE EMPLOYEES; --" This drops the table and deletes the data in the table


    sql = query;

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Query successfully executed\n\n\n");
    }

    sqlite3_close(db);

    return 0;

}

static int callback(void *, int argc, char **argv, char **azColName){
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
    
    if(remove("employee.db") == 0){
        printf("Successfully deleted the database file\n\n\n");
    }else{
        perror("Error deleting the database");
    }

    return 0;
}