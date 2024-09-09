import logging
import socket
import random
import time
import utils
from PDU import PDU

config = utils.read_config('config.ini')
logger = utils.setup_logger('Sender')


# 发送方
class Sender:
    def __init__(self, send_host, send_port, receive_host, receive_port, window_size, timeout, file_path):
        self.send_host = send_host
        self.send_port = send_port
        self.receive_host = receive_host
        self.receive_port = receive_port
        self.file_path = file_path
        self.window_size = window_size
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.send_host, self.send_port))  # 绑定发送端的IP和端口
        self.seq_num = int(config['InitSeqNo'])
        self.sock.settimeout(int(timeout))
        self.send_count = 0
        self.data_size = int(config['DataSize'])
        self.window = []
        self.last_ackNo = 0

    def send_file(self):
        with open(self.file_path, 'rb') as file:
            end = False
            while True:
                print('-' * 50)
                while len(self.window) < int(self.window_size):
                    print('\nwindow:', len(self.window))
                    data = file.read(self.data_size)
                    print('data:', len(data))
                    if not data:
                        pdu = PDU(0, b'', True)
                        self.send_pdu(pdu, 'Final')
                        end = True
                        break
                    pdu = PDU(self.seq_num, data, False)
                    # pdu = simulate_error_loss(pdu)
                    self.send_pdu(pdu, 'New')
                    self.window.append(pdu)
                if end is True:
                    print('-' * 30, ' Send Done ', '-' * 30)
                    break
                self.handle_ack()

    def send_pdu(self, pdu, status):
        self.send_count += 1
        pdu_bytes = pdu.to_bytes()
        self.sock.sendto(pdu_bytes, (self.receive_host, self.receive_port))
        if pdu.final == 1:
            return
        print('No.', self.send_count, 'send', len(pdu_bytes), 'bytes')
        logger.info(f'Send: {self.send_count}, pdu_to_send={pdu.seq_num}, status={status}, ackedNo={self.last_ackNo}')
        self.seq_num += 1

    def handle_ack(self):
        print('handle_ack')
        while True:
            try:
                ack, _ = self.sock.recvfrom(4)
                ack_num = int.from_bytes(ack, byteorder='big', signed=True)
                if ack_num < 0:  # 如果接收到的是NAK
                    nak_num = -ack_num  # 获取NAK的序列号
                    print('nak', nak_num)
                    for pdu in self.window:
                        self.send_pdu(pdu, 'RT')  # 重新发送PDU
                    break
                else:  # 如果接收到的是ACK
                    print('ack', ack_num)
                    self.last_ackNo = ack_num
                    while len(self.window) > 0 and self.window[0].seq_num <= ack_num:
                        print('pop', self.window[0].seq_num)
                        self.window.pop(0)
                    if len(self.window) == 0:
                        break
            except socket.timeout:
                for pdu in self.window:
                    self.send_pdu(pdu, 'TO')


# # 错误和丢失率处理
# def simulate_error_loss(pdu):
#     error_rate = int(config['ErrorRate'])
#     loss_rate = int(config['LossRate'])
#     rate = random.randint(1, 100)
#     type_choose = random.randint(1, 2)
#     type = ''
#     if type_choose == 1:
#         type = 'error'
#     elif type_choose == 2:
#         type = 'loss'
#     if rate <= error_rate and type == 'error':
#         # 模拟 PDU 错误
#         pdu.data = b'corrupted_data'
#         print('Error:', error_rate, rate)
#     if rate <= loss_rate and type == 'loss':
#         # 模拟 PDU 丢失
#         print('Loss:', loss_rate, rate)
#         return None
#     return pdu


filePath = 'exampleFile.txt'
sender = Sender(config['SenderHost'], int(config['SenderPort']), config['ReceiverHost'], int(config['ReceiverPort']), config['SWSize'], config['Timeout'], filePath)
sender.send_file()
