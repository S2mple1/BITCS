import PDU
import utils

config = utils.read_config('config.ini')


class Receiver:
    def __init__(self):
        self.error_rate = float(config['ErrorRate']) / 100
        self.lost_rate = float(config['LostRate']) / 100
        self.data_size = int(config['DataSize'])

    def receive(self, sock, filename, IP_PORT):
        udt = utils.UDP(self.lost_rate, self.error_rate, self.data_size)
        logger = utils.setup_logger(IP_PORT, 'Receiver')
        file = open(filename, "wb")
        logger.info("------------------------Receiver------------------------")
        frame_expected = int(config['InitSeqNo'])
        logger.info(f"Receiver: {IP_PORT[0]}:{str(IP_PORT[1])}")
        logger.info(f"Receiving file: {filename}")
        logger.info("------------------------Receiver------------------------\n")
        recv_count = 0

        while True:
            recv_count += 1
            pdu, addr = udt.receive(sock)

            if not pdu:
                break
            seq_num, crc_num, data = PDU.split(pdu)

            print('\nPDU:', seq_num)

            crc_expected = utils.crc16xmodem(data)
            if crc_expected != crc_num:
                logger.info(f"{recv_count}, pdu_exp={seq_num}, pdu_recv={frame_expected}, status=DataErr\n")
                print("DataErr data")
                udt.send_nak(-frame_expected, sock, addr)
                continue

            if seq_num == frame_expected:
                print('Correct data')
                logger.info(f"{recv_count}, pdu_exp={seq_num}, pdu_recv={frame_expected}, status=OK\n")
                print('ACK:', frame_expected)
                udt.send_ack(frame_expected, sock, addr)
                frame_expected += 1
                file.write(data)

            else:
                print('NoErr data')
                logger.info(f"{recv_count}, pdu_exp={seq_num}, pdu_recv={frame_expected}, status=NoErr\n")
                print('ACK:', frame_expected-1)
                udt.send_ack(frame_expected - 1, sock, addr)

        print("\n-------------------------Receive succeed!-------------------------")
        logger.info("Success.")
        file.close()
