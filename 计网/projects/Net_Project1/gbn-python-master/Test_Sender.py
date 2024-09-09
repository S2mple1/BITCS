import unittest
import socket
import threading
import Sender


class TestSender(unittest.TestCase):
    def test_send(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        Sender_IP_PORT = ('localhost', 12345)
        Receiver_IP_PORT = ('localhost', 12346)
        sock.bind(Sender_IP_PORT)
        filename = 'test.txt'
        send_thread = threading.Thread(target=Sender.send, args=(sock, filename, Sender_IP_PORT, Receiver_IP_PORT))
        send_thread.start()
        send_thread.join()


if __name__ == "__main__":
    unittest.main()
