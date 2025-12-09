import sqlite3
from nicegui import ui



def queryDB():
    name = nameInput.value

    con = sqlite3.connect("employee.db")
    cur = con.cursor()

    
    query = "SELECT NAME, ADDRESS FROM EMPLOYEES WHERE LOWER(NAME) = '" + name + "'"

    # Prone to sql injection where it manipulates the database, but can't fetch results of more than one query, so isn't prone to " '; SELECT * FROM EMPLOYEES; --"
    # But is prone to dropping the table and other manipulations
    
    cur.executescript(query)

    result = cur.fetchall()



    print(result)

    con.close()

    if result:
        print("Found")
        print(query)
        for name, address in result:
            print(f"Found employee: Name = {name}, Address = {address}")
            resultLabel.text = f"Found employee: Name = {name}, Address = {address}"
    else:
        print("Not found")
        print(query)
        resultLabel.text = "No employee found with that name"


ui.label('Welcome to the Employee database tool to search for employee names')

nameInput = ui.input("Enter an employee name")

ui.button("Search name", on_click=queryDB)

resultLabel = ui.label("")

ui.run()





#res = cur.execute("SELECT NAME, ADDRESS FROM EMPLOYEES WHERE LOWER(NAME)='olav'")







