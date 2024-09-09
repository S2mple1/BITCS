import sys

# 解析参数，得到参数值
ini = sys.argv[1]
ini = ini.split("&")
a = ini[0].split("=")[1]
b = ini[1].split("=")[1]
operation = ini[2].split("=")[1]  # 获取运算类型

# 根据运算类型进行计算
res = ""
if operation == 'add':
    res = str(float(a) + float(b))
elif operation == 'subtract':
    res = str(float(a) - float(b))
elif operation == 'multiply':
    res = str(float(a) * float(b))
elif operation == 'divide':
    if float(b) != 0:
        res = str(float(a) / float(b))
    else:
        res = 'Error: Division by zero'

# 构造html输出
output = ""
with open("cgi-bin/calculator_res.html", "r") as file:
    for line in file:
        output += line
    output = output.replace("$op1", a)
    output = output.replace("$op2", b)
    output = output.replace("$res", res)
    print(output)
