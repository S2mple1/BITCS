import csv
import sys

ini = sys.argv[1]
hostname = sys.argv[2]
port = sys.argv[3]
student_id = ini.split("=")[1]
csv_file = './data/Student_data.csv'

with open(csv_file, 'r', encoding='utf-8') as f:
    reader = csv.reader(f)
    student_data = list(reader)

Get_res = 0
res = ""

with open("./cgi-bin/Que_res.html", "r", encoding="utf-8") as f:
    for line in f:
        res += line
    for student in student_data:
        if student[0] == student_id:
            temp = "<tr>"
            for i in range(5):
                temp += "<th>" + student[i] + "</th>"
            temp += "</tr>\n"
            res = res.replace("$data", temp, 1)
            Get_res = 1
            
if not Get_res:
    temp = "<p>Sorry, there's no corresponding data for your request.</p>\n"
    res = res.replace("$data", temp, 1)

print(res)
