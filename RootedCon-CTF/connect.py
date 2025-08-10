import sqlite3

# Solution = "CASE WHEN (SELECT SUBSTR(password,1,1) FROM users WHERE id=1) LIKE 'F' THEN 2 ELSE 1 END"

def execute(value):
	con = sqlite3.connect("sqlite.db")
	value = "SELECT CAST("+value+" AS INT)"
	cur = con.cursor()
	cur.execute(value)
	res = cur.fetchone()[0]
	query = "SELECT post FROM blogs WHERE id = "+str(res)
	cur.execute(query)
	res = cur.fetchone()[0]
	return res
