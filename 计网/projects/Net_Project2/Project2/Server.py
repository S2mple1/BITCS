import socket
from Worker import tasks, working_thread, sema, Worker
import threading
import time

# 设置最大连接数和监听端口
# 创建服务器socket，绑定地址并开始监听

try:
    max_connection = eval(input("Input the Max Connection: "))
except:
    max_connection = 10
    print("Error!")

port = 8888
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_name = socket.gethostname()
host_name = socket.gethostbyname(host_name)
address = ("0.0.0.0", port)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(address)
server_socket.settimeout(60)
server_socket.listen(max_connection)

print(host_name + ':' + str(port))


class ThreadPoolManager(threading.Thread):  # 线程池管理类，负责创建Worker和管理线程池的大小
    def __init__(self, log_name):
        threading.Thread.__init__(self)
        self.setDaemon(True)  # 设置为守护线程
        self.start()
        self.log_name = log_name

    def run(self):
        # 创建指定数量的Worker
        # 不断检查线程池的大小，如果线程池已满，删除一个线程
        for i in range(max_connection):
            Worker(log_name)
        while True:
            for i in range(10):
                if (len(working_thread) == max_connection and max_connection != 0 and (not tasks.empty())):
                    working_thread[0].restart()
            sema.acquire(timeout=1)


# 每一次运行都创建一个日志文件
now_time = time.localtime()
log_name = "log/" + str(now_time.tm_year) + "-" + str(
    now_time.tm_mon) + "-" + str(now_time.tm_mday) + "-" + str(
    now_time.tm_hour) + "-" + str(now_time.tm_min) + "-" + str(
    now_time.tm_sec) + ".txt"

ThreadPoolManager(log_name)

while True:  # 接收客户端的连接请求并加入到任务队列
    try:
        client, addr = server_socket.accept()
        print("recv: ", client.getpeername(), client.getsockname())
        tasks.put(client)
    except socket.timeout:
        print("Timeout")
