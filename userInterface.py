import sqlite3

con = sqlite3.connect("employee.db")

cur = con.cursor()

#res = cur.execute("SELECT NAME, ADDRESS FROM EMPLOYEES WHERE LOWER(NAME)='olav'")

insert = "'; SELECT * FROM EMPLOYEES; --"

query = "SELECT NAME, ADDRESS FROM EMPLOYEES WHERE LOWER(NAME) = '" + insert + "'"

print(query)

res = cur.executescript(query)

print(res.fetchall())