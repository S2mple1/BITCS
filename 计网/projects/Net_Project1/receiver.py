import random
import socket
import time

import utils
from PDU import PDU

logger = utils.setup_logger('Receiver')


# 接收方
class Receiver:
    def __init__(self, host, port, file_path):
        self.recv_count = 0
        self.host = host
        self.port = port
        self.file_path = file_path
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.host, port))
        self.expected_seq_num = int(config['InitSeqNo'])  # 期望接收的PDU的序号

    def receive_file(self):
        with open(self.file_path, 'wb') as file:
            while True:
                print('-' * 50)
                pdu_bytes, _ = self.sock.recvfrom(int(config['DataSize']) + PDU.header_length)
                print('Receive:', len(pdu_bytes), 'bytes')
                pdu = PDU.from_bytes(pdu_bytes)
                print('final:', pdu.final)
                print('Expected:', self.expected_seq_num)
                print('Received:', pdu.seq_num)
                if pdu.final == 1:
                    print('-' * 30, ' Receive Done ', '-' * 30)
                    break
                pdu = simulate_error_loss(pdu)
                if pdu is None:
                    print('Loss')
                    time.sleep(2)
                elif pdu.data == b'corrupted_data':  # 检测到错误
                    self.recv_count += 1
                    self.send_nak(pdu.seq_num)  # 发送NAK
                    print('DataErr:', pdu.seq_num)
                    logger.error(
                        f'Receive: {self.recv_count}, pdu_exp={self.expected_seq_num}, pdu_recv={pdu.seq_num}, status=DataErr')
                elif pdu.seq_num != self.expected_seq_num:  # 序号错误
                    self.recv_count += 1
                    self.send_nak(self.expected_seq_num)  # 发送NAK
                    print('NoErr:', pdu.seq_num)
                    logger.error(
                        f'Receive: {self.recv_count}, pdu_exp={self.expected_seq_num}, pdu_recv={pdu.seq_num}, status=NoErr')
                else:
                    file.write(pdu.data)
                    print('Write to file:', len(pdu.data))
                    self.recv_count += 1
                    logger.info(
                        f'Receive: {self.recv_count}, pdu_exp={self.expected_seq_num}, pdu_recv={pdu.seq_num}, status=OK')
                    self.send_ack(pdu.seq_num)
                    self.expected_seq_num += 1  # 更新期望接收的PDU的序号

    def send_ack(self, seq_num):
        ack = seq_num.to_bytes(4, byteorder='big', signed=True)
        self.sock.sendto(ack, (config['SenderHost'], int(config['SenderPort'])))

    def send_nak(self, seq_num):
        nak = (-seq_num).to_bytes(4, byteorder='big', signed=True)
        self.sock.sendto(nak, (config['SenderHost'], int(config['SenderPort'])))


# 错误和丢失率处理
def simulate_error_loss(pdu):
    error_rate = int(config['ErrorRate'])
    loss_rate = int(config['LossRate'])
    rate = random.randint(1, 100)
    type_choose = random.randint(1, 2)
    type = ''
    if type_choose == 1:
        type = 'error'
    elif type_choose == 2:
        type = 'loss'
    if rate <= error_rate and type == 'error':
        # 模拟 PDU 错误
        pdu.data = b'corrupted_data'
        # print('Error:', error_rate, rate)
    if rate <= loss_rate and type == 'loss':
        # 模拟 PDU 丢失
        # print('Loss:', loss_rate, rate)
        return None
    return pdu


config = utils.read_config('config.ini')
filePath = 'receivedFile.txt'
receiver = Receiver(config['ReceiverHost'], int(config['ReceiverPort']), filePath)
receiver.receive_file()
