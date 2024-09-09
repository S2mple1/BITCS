import socket
import threading
import queue
import time

# 导入自定义HTTP处理类
from myHTTP import HTTPRequestHandler


class ThreadPool:
    def __init__(self, max_connections, logfile):
        # 待处理任务列表
        self.task_queue = queue.Queue()
        # 线程池
        self.thread_list = []
        # 最大并行线程数（连接数）
        self.max_connections = max_connections
        # 线程同步锁，在访问共享变量时加锁
        self.lock = threading.Lock()
        # 初始化线程池
        self.start()
        # 日志文件路径
        self.logfile = logfile

    # 根据 max-connection，初始化线程池
    def start(self):
        for _ in range(self.max_connections):
            work_thread = threading.Thread(target=self.worker)
            work_thread.start()
            self.thread_list.append(work_thread)

    # 子线程的核心业务函数
    def worker(self):
        while True:
            # 循环从队列中取出一个任务，并处理
            client_socket = self.task_queue.get()
            # 检查当前取出的是不是结束标志，如果是，直接结束线程
            if client_socket is None:
                break

            # HTTP 请求处理
            # 创建一个 HTTPRequestHandler对象，开始处理
            request_handler = HTTPRequestHandler(client_socket, self.logfile)
            request_handler.handle_request()

    # 将 socket 放入消息队列
    def sumbit_task(self, client_socket):
        # 放入新连接(client_socket)到task队列中等待处理
        self.task_queue.put(client_socket)

    # 资源释放
    def stop(self):
        # 清空所有task，终止所有线程
        with self.lock:
            self.task_queue.queue.clear()
            for _ in range(self.max_connections):
                self.task_queue.put(None)
        for thread in self.thread_list:
            thread.join()


# ---------------------------------------------------------------------------- #
# command line获得最大连接数 max_connection
while True:
    user_input = input("请输入web server的TCP最大连接数: ")
    try:
        max_connection = int(user_input)
        break
    except ValueError:
        print("无效输入，请再次输入")
# ---------------------------------------------------------------------------- #
# 以当前时间生成log_file的路径
current_time = time.localtime()
time_str = '_'.join(
    [str(current_time.tm_year), str(current_time.tm_mon), str(current_time.tm_mday), str(current_time.tm_hour),
     str(current_time.tm_min), str(current_time.tm_sec)])
logfile = "log/" + time_str + '.txt'

# ---------------------------------------------------------------------------- #
# 创建TCP套接字
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 允许server重启后使用上一次保留状态的端口
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# 生成本机地址
host = "127.0.0.1"
port = 8888
address = (host, port)
# 将socket与地址绑定
server_socket.bind(address)
# 设置监听超时60s
server_socket.settimeout(60)
# 开始监听，
server_socket.listen(max_connection)
print("Web server listening on: localhost:{}".format(port))

# ---------------------------------------------------------------------------- #
# 创建线程池
thread_pool = ThreadPool(max_connection, logfile)

# 开始阻塞监听连接事件
while True:
    try:
        client_socket, client_addr = server_socket.accept()
        print("connection set: {}".format(client_addr))
        # 提交待处理事件到消息队列中
        thread_pool.sumbit_task(client_socket)
    except KeyboardInterrupt:
        break
    except socket.timeout:
        print("socket timeout!")

# ---------------------------------------------------------------------------- #
# 终止服务器，释放资源
# 停止线程池
thread_pool.stop()
# 关闭套接字
server_socket.close()
