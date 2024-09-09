import unittest
import socket
import threading
import Receiver


class TestSender(unittest.TestCase):
    def test_receive(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        Receiver_IP_PORT = ('localhost', 12346)
        sock.bind(Receiver_IP_PORT)
        filename = 'recv_test.txt'
        receiver = Receiver.Receiver()
        receive_thread = threading.Thread(target=receiver.receive, args=(sock, filename, Receiver_IP_PORT))
        receive_thread.start()
        receive_thread.join()


if __name__ == "__main__":
    unittest.main()
