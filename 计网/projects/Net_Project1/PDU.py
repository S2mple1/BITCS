import struct
import zlib


# 定义帧（PDU）结构
class PDU:
    header_length = 9  # 头部长度

    def __init__(self, seq_num, data, final):
        self.seq_num = seq_num
        self.data = data
        self.checksum = self.calculate_checksum()
        self.final = 1 if final else 0

    def calculate_checksum(self):
        # 使用 CRC-CCITT 标准计算 checksum
        checksum = zlib.crc32(self.data) & 0xffffffff
        return checksum

    def to_bytes(self):
        # 将 PDU 转换为字节流
        pdu_format = f'!I{len(self.data)}sIB'  # 格式：seq_num(4 bytes) + data + checksum(4 bytes)
        return struct.pack(pdu_format, self.seq_num, self.data, self.checksum, self.final)

    @classmethod
    def from_bytes(cls, pdu_bytes):
        # 从字节流解析出 PDU
        seq_num, data, checksum, final = struct.unpack(f'!I{len(pdu_bytes) - 9}sIB', pdu_bytes)
        pdu = cls(seq_num, data, final)
        pdu.checksum = checksum
        return pdu
