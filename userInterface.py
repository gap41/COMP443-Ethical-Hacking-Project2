# A simple GUI to demonstrate SQL injections for project 3 COMP443

import sqlite3
from nicegui import ui



def queryDB():

    name = nameInput.value  # Set name to the user input

    con = sqlite3.connect("employee.db")    # Connect to the database
    cur = con.cursor()  # Create a cursor that can execute the queries

    
    query = "SELECT NAME, ADDRESS FROM EMPLOYEES WHERE LOWER(NAME) = '" + name + "'"

    # Prone to sql injection where it manipulates the database, but can't fetch results of more than one query, so isn't prone to " '; SELECT * FROM EMPLOYEES; --"
    # But is prone to dropping the table and other manipulations
    
    cur.executescript(query)    # Execute the queries, have to use executescript() since execute() only executes one SQL statement and therefore protects against SQL injection

    result = cur.fetchall()     # Fetch the results

    print(result)

    con.close()     # Close the connection

    if result:
        print("Found")
        print(query)
        for name, address in result:    # Prints every match
            print(f"Found employee: Name = {name}, Address = {address}")
            resultLabel.text = f"Found employee: Name = {name}, Address = {address}"    # Prints the results to the label in the GUI
    else:
        print("Not found")
        print(query)
        resultLabel.text = "No employee found with that name"


ui.label('Welcome to the Employee database tool to search for employee names')

nameInput = ui.input("Enter an employee name")  # User input field

ui.button("Search name", on_click=queryDB)      # Button to submit the text

resultLabel = ui.label("")  # Placeholder for the label to show the results, gets updated in the method above

ui.run()







