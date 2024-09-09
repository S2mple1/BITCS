import socket
from datetime import datetime
import packet
import crc16
import UDT
import sys
import time

import utils

config = utils.read_config('config.ini')

error_rate = float(config['ErrorRate']) / 100
lost_rate = float(config['LostRate']) / 100


def receive(sock, filename, IP_PORT):
    UDTER = UDT.UDT(lost_rate, error_rate)
    file = open(filename, "wb")
    log_filename = IP_PORT[0] + "_" + str(IP_PORT[1]) + "_" + "Receiver_" + datetime.now().strftime(
        "%Y%m%d%H%M%S") + ".txt"
    log_file = open(log_filename, "a+")
    log_file.write("-------------------------------\n")
    frame_expected = int(config['InitSeqNo'])
    log_file.write("Receiving %s...\n" % filename)
    while True:
        pdu, addr = UDTER.recv(sock)

        print(pdu)
        if not pdu:
            break
        seq_num, crc_num, data = packet.extract(pdu)

        print('Got PDU',seq_num)

        crc_expected = crc16.crc16xmodem(data)
        if crc_expected != crc_num:
            log_file.write("%s: Receive PDU=%d,STATUS=DataErr,FRAME_EXPECTED=%d from %s\n" % (
                time.ctime(), seq_num, frame_expected, str(addr)))
            print("data with error")
            continue

        if seq_num == frame_expected:
            # print('Got expected packet')
            log_file.write("%s: Receive PDU=%d,STATUS=OK,FRAME_EXPECTED=%d from %s\n" % (
                time.ctime(), seq_num, frame_expected, str(addr)))
            print('Sending ACK', frame_expected)
            UDTER.sendack(frame_expected, sock, addr)
            frame_expected += 1
            file.write(data)

        else:
            # print('Got unexpected packet')
            log_file.write("%s: Receive PDU=%d,STATUS=NoErr,FRAME_EXPECTED=%d from %s\n" % (
                time.ctime(), seq_num, frame_expected, str(addr)))
            print('Sending ACK', frame_expected-1)
            UDTER.sendack(frame_expected - 1, sock, addr)

    print("over")
    log_file.write("Receive succeed\n")
    log_file.write("-------------------------------\n\n\n")
    log_file.close()
    file.close()
