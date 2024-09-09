import utils


class PDU:
    def __init__(self, seq_num, data=b''):
        self.seq = seq_num
        self.data = data
        self.crc = utils.crc16xmodem(data)


def generate(seq_num, crc_num, data=b''):
    seq_bytes = seq_num.to_bytes(4, byteorder='big', signed=True)
    crc_bytes = crc_num.to_bytes(4, byteorder='big', signed=True)
    return seq_bytes + crc_bytes + data


def final_packet():
    return b''


def split(packet):
    seq_num = int.from_bytes(packet[0:4], byteorder='big', signed=True)
    crc_num = int.from_bytes(packet[4:8], byteorder='big', signed=True)
    return seq_num, crc_num, packet[8:]
