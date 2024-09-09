import _thread
import random
import PDU
import time
import threading
import utils

config = utils.read_config('config.ini')

error_rate = float(config['ErrorRate']) / 100
lost_rate = float(config['LostRate']) / 100
data_size = int(config['DataSize'])
ack_exp = int(config['InitSeqNo'])
num_packets = 0
resend = False
lock = _thread.allocate_lock()
udt = utils.UDP(lost_rate, error_rate, data_size)
send_count = 0


def send(sock, filename, send_ip_port, recv_ip_port):
    global dur
    global status
    global lock
    global ack_exp
    global num_packets
    global send_count
    global resend

    TO_COUNT = 0
    RT_COUNT = 0
    Total_COUNT = 0
    scale = 100
    packets = []
    start_time = time.time()
    timeout = float(config['Timeout']) / 1000
    send_timer = utils.timer(timeout)
    logger = utils.setup_logger(send_ip_port, 'Sender')
    file = open(filename, "rb")
    seq_num = int(config['InitSeqNo'])
    window_size = int(config['SWSize'])
    next_frame_to_send = int(config['InitSeqNo'])

    logger.info("------------------------Sender------------------------")
    logger.info(f"Sender: {send_ip_port[0]}:{str(send_ip_port[1])}")
    logger.info(f"Receiver: {recv_ip_port[0]}:{str(recv_ip_port[1])}")
    logger.info(f"Sending file: {filename}")

    while True:
        data = file.read(data_size)
        if not data:
            break
        crc_num = utils.crc16xmodem(data)
        pdu = PDU.generate(seq_num, crc_num, data)
        packets.append(pdu)
        seq_num += 1

    num_packets = len(packets)

    logger.info(f'Packet size: {data_size} Bytes, Total packets: {num_packets}')
    logger.info("------------------------Sender------------------------\n")
    print(f'Packet size: {data_size} Bytes, Total packets:{num_packets}')

    t = threading.Thread(target=sender_receive, args=(sock,))
    t.start()
    overtime = False
    start = time.perf_counter()
    pre = start
    while ack_exp < len(packets):
        lock.acquire()
        while next_frame_to_send < ack_exp + window_size:
            send_count += 1
            if next_frame_to_send >= len(packets):
                break
            if overtime is False:
                if resend is False:
                    status = 'New'
                    logger.info(f"{send_count}, pdu_to_send={next_frame_to_send}"
                                f", status={status}, ackedNo={ack_exp}\n")
                else:
                    status = 'RT'
                    logger.info(f"{send_count}, pdu_to_send={next_frame_to_send}"
                                f", status=New, ackedNo={ack_exp}\n")
                    send_count += 1
                    logger.info(f"{send_count}, pdu_to_send={next_frame_to_send}"
                                f", status={status}, ackedNo={ack_exp}\n")
                    RT_COUNT += 1
            elif overtime is True:
                status = 'TO'
                logger.info(f"{send_count}, pdu_to_send={next_frame_to_send}"
                            f", status={status}, ackedNo={ack_exp}\n")
                TO_COUNT += 1

            send_timer.start(next_frame_to_send)
            udt.send(packets[next_frame_to_send], sock, recv_ip_port)
            next_frame_to_send += 1

        Total_COUNT = send_count
        overtime = False
        if send_timer.overtime(ack_exp):
            overtime = True
            next_frame_to_send = ack_exp

        if (time.perf_counter() - pre) > 1:
            pre = time.perf_counter()
            param = num_packets / scale
            i = int(next_frame_to_send / param + 1)
            a = '*' * i
            b = '.' * (scale - i)
            c = (i / scale) * 100
            dur = pre - start
            print("\rSending {:^3.0f}% [{}=>{}] Time: {:.2f} secs".format(c, a, b, dur), end='')
        lock.release()

    print("\rSend Over {:^3.0f}% [{}] Time: {:.2f} secs".format(100, '*' * scale, dur), end='')
    print("\n-------------------------Send succeed!-------------------------")
    udt.send(PDU.final_packet(), sock, recv_ip_port)
    end_time = time.time()
    Total_time = end_time - start_time
    logger.info(f"Total packets: {num_packets}")
    logger.info(f"Total time: {round(Total_time, 2)} seconds")
    logger.info(f"TO count: {TO_COUNT}")
    logger.info(f"RT count: {RT_COUNT}")
    logger.info("Success.")
    file.close()


def sender_receive(sock):
    global lock
    global ack_exp
    global num_packets
    global resend

    while True:
        ack, _ = udt.receive_ack(sock)
        if ack < 0:
            lock.acquire()
            ack_exp = -ack
            resend = True
            lock.release()
        elif ack >= ack_exp:
            lock.acquire()
            ack_exp = ack + 1
            resend_()
            lock.release()
        if ack_exp >= num_packets:
            break


































































































































































































def resend_():
    global resend
    if random.random() < error_rate:
        resend = True
    else:
        resend = False
