# import pymysql
import sqlite3
import sys

ini = sys.argv[1]

sid = ini.split("&")[0].split("=")[1]
sname = ini.split("&")[1].split("=")[1]
sclass = ini.split("&")[2].split("=")[1]

db = sqlite3.connect('database/student.db')
cursor = db.cursor()


sql = "SELECT * from student"

id_flag = 1
id_name = 1
id_class = 1

if sid == "":
    id_flag = 0
if sname == "":
    id_name = 0
if sclass == "":
    id_class = 0

if id_flag == 0 and id_name == 0 and id_class == 0:
    pass
else:
    sql += " where"
    if id_flag == 1:
        sql += " id = " + sid

    if id_flag == 0 and id_name == 1:
        sql += " name = \'" + sname + "\' "
    elif id_flag == 1 and id_name == 1:
        sql += " and name = \'" + sname + "\' "

    if id_flag == 0 and id_name == 0 and id_class == 1:
        sql += " class = \'" + sclass + "\' "
    elif id_class == 1:
        sql += " and class = \'" + sclass + "\' "

sql += ";"

cursor.execute(sql)

data = cursor.fetchone()

if data is None or (id_flag == 0 and id_name == 0 and id_class == 0):
    data = ["Not Exist", "Not Exist", "Not Exist"]


output = ""
with open("cgi-bin/query_res.html", "r") as f:
    for line in f:
        output += line
    output = output.replace("$id", data[0])
    output = output.replace("$name", data[1])
    output = output.replace('$class', data[2])
    print(output)
