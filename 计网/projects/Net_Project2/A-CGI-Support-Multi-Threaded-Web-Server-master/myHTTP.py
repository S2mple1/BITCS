import socket
import os
import subprocess
import time


# 实现 HTTP1.0

class HTTPRequestHandler:
    def __init__(self, client_socket, logfile):
        # 处理的socket
        self.client_socket = client_socket
        # 超时时间
        self.timeout = 10
        # 处理http请求相关信息
        # 元素为header每一项的列表
        self.msg = None
        # 状态码
        self.status_code = -1
        # 文件句柄
        self.file_handle = None
        # CGI子程序
        self.subproc = None
        # 日志文件路径
        self.logfile = logfile

    # 释放本次连接的所有相关资源
    def release_resource(self):
        # 文件句柄
        if self.file_handle is not None:
            self.file_handle.close()
        # socket 套接字
        if self.client_socket is not None:
            try:
                # 通知关闭双方的套接字连接
                self.client_socket.shutdown(socket.SHUT_RDWR)
                # 关闭套接字
                self.client_socket.close()
            except Exception as e:
                print("socket close error:", e)
        # CGI子程序
        if self.subproc is not None and self.subproc.poll() is not None:
            self.subproc.kill()
            self.subproc = None

    def log_request(self, size):
        log_content = ""
        # ip
        log_content += (self.msg[1].split(':'))[1]
        log_content += '--'
        # time
        current_time = time.localtime()
        time_str = '_'.join(
            [str(current_time.tm_year), str(current_time.tm_mon), str(current_time.tm_mday), str(current_time.tm_hour),
             str(current_time.tm_min), str(current_time.tm_sec)])
        log_content += " [" + time_str + "]"
        # request_line
        log_content += ' "' + self.msg[0] + '"'
        # state_code
        log_content += " " + str(self.status_code)
        # file size
        log_content += " " + str(size)
        # referer
        # user-angency
        for entry in self.msg:
            if entry.split(":")[0] == "Referer":
                log_content += ' "' + entry.split(" ")[1] + '"'
            if entry.split(':')[0] == "User-Agent":
                log_content += ' "' + entry.split(" ")[1] + '"'
        with open(self.logfile, 'a') as file:
            file.write(log_content)
            file.write('\n')

    # 错误对应的响应构造
    def build_error_response(self, isHead=False):
        code = self.status_code
        if code == 400:
            content = b'HTTP/1.0 400 Bad Request\r\nContent-Type: text/html;charset=utf-8\r\n'
            file_path = '400.html'
        elif code == 404:
            content = b"HTTP/1.0 404 Not Found\r\nContent-Type: text/html;charset=utf-8\r\n"
            file_path = '404.html'
        elif code == 403:
            content = b"HTTP/1.0 403 Forbidden\r\nContent-Type: text/html;charset=utf-8\r\n"
            file_path = '403.html'
        # response header
        content += b'\r\n'
        self.client_socket.sendall(content)

        file_size = 0
        # response body
        # 发送对应的错误提示页面
        if not isHead:
            file_size = os.path.getsize(file_path)
            with open(file_path, 'rb') as file:
                self.file_handle = file
                for line in file:
                    self.client_socket.sendall(line)
        # log
        self.log_request(file_size)

    def handle_get(self, file_path):
        # print("enter GET")
        if os.path.isfile(file_path):
            self.status_code = 200
            # 需要区分css和html文件，设置正确的content-type
            suffix = (file_path.split('.'))[-1].encode()
            # response header
            content = b"HTTP/1.0 200 OK\r\nContent-Type: text/" + suffix + b";charset=utf-8\r\n"
            content += b'\r\n'
            self.client_socket.sendall(content)
            # response body
            with open(file_path, 'rb') as file:
                self.file_handle = file
                for line in file:
                    # print(line)
                    self.client_socket.sendall(line)
            # log
            self.log_request(os.path.getsize(file_path))
        else:
            self.status_code = 404
            self.build_error_response()

    def handle_post(self, file_path, args):
        cmd = ['python', file_path, args]
        self.subproc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        self.subproc.wait()
        # 检查子进程返回状态
        if self.subproc.poll() == 2:
            self.status_code = 403
            self.build_error_response()
        else:
            self.status_code = 200
            content = b"HTTP/1.0 200 OK\r\nContent-Type: text/html;charset=utf-8\r\n"
            content += b'\r\n'
            content += self.subproc.stdout.read()
            self.client_socket.sendall(content)
            self.log_request(os.path.getsize(file_path))

    def handle_head(self, file_path):
        if os.path.isfile(file_path):
            self.status_code = 200
            # response header
            content = b"HTTP/1.0 200 OK\r\nContent-Type: text/html;charset=utf-8\r\n"
            content += b'\r\n'
            self.client_socket.sendall(content)
            self.log_request(0)
        else:
            self.status_code = 404
            self.build_error_response(isHead=True)

    # 解析http请求函数
    def handle_request(self):
        # 设置超时时间，避免处理时间过长拖慢服务性能
        self.client_socket.settimeout(self.timeout);
        try:
            # 处理 HTTP 请求的逻辑
            # 获取request数据
            request_data = b''
            while True:
                chunk = self.client_socket.recv(1024)
                if not chunk:
                    break
                request_data += chunk
                # 检查结束标志
                if b'\r\n\r\n' in request_data:
                    break
            # 解析请求
            # 解码并按行拆分
            self.msg = request_data.decode('utf-8').split('\r\n')
            # print(self.msg )
            # 先判断请求长度非空
            if self.msg:
                # # 解析header的键值对
                # for line in self.msg[1:]:
                #     if line.strip():
                #         key,value=line.split(':',1)
                #         self.header[key]=value

                # 解析首行的request line
                request_line = self.msg[0].split()
                # print(request_line )
                if len(request_line) < 2:
                    raise ValueError("incorret request line")
                # 获得url和method
                method = request_line[0]
                url = request_line[1]

                target_file_path = None
                # 解析目标文件路径
                if url == "/":
                    target_file_path = 'index.html'
                else:
                    # 略去首个"/"
                    target_file_path = url[1:]
                # print("file:",target_file_path)
                # 按照method不同，进行处理
                if method == 'GET':
                    self.handle_get(target_file_path)
                elif method == "POST":
                    # msg的最后一个元素(即body)装载参数
                    self.handle_post(target_file_path, self.msg[-1])
                elif method == "HEAD":
                    self.handle_head(target_file_path)
                else:
                    self.status_code = 400
                    self.build_error_response()
            else:
                raise ValueError("blank request")
        except socket.timeout:
            print('error: process timeout')
        except KeyboardInterrupt:
            print("KeyboardInterrupt")
        except ValueError as e:
            print("error: ", str(e))
        finally:
            # 发送完毕，清理资源    
            self.release_resource()
