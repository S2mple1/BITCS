import os

import sender
import receiver
import socket
import sys
import threading
import utils


def main():
    # IP = input("Please input the IP: ")
    # PORT = eval(input("Please input the Port: "))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # IP_PORT = (IP, PORT)

    # sock.bind(IP_PORT)‘

    config = utils.read_config('config.ini')

    Sender_IP = config['SenderHost']
    Sender_PORT = int(config['SenderPort'])
    Sender_IP_PORT = (Sender_IP, Sender_PORT)

    Receiver_IP = config['ReceiverHost']
    Receiver_PORT = int(config['ReceiverPort'])
    Receiver_IP_PORT = (Receiver_IP, Receiver_PORT)

    while True:
        option = input("1.Send file\n2.Receive file\n3.Exit\nPlease input option number:")
        if option == "1":
            sock.bind(Sender_IP_PORT)
            lock = threading.Lock()
            lock.acquire()
            while True:
                filename = input("Please input the filepath you want to send: ")
                if os.path.exists(filename):
                    break
                else:
                    print("File not found, please input again.")
                    continue
            # RECEIVER_IP = input("Please input the Receiver's IP: ")
            # RECEIVER_PORT = eval(input("Please input the Receiver's Port: "))
            # RECEIVER_IP_PORT = (RECEIVER_IP, RECEIVER_PORT)
            lock.release()

            send_thread = threading.Thread(target=sender.send, args=(sock, filename, Sender_IP_PORT, Receiver_IP_PORT))
            send_thread.start()
            send_thread.join()

        elif option == "2":
            sock.bind(Receiver_IP_PORT)
            lock = threading.Lock()
            lock.acquire()
            filename = input("Please input the filepath you want to save: ")
            lock.release()
            receive_thread = threading.Thread(target=receiver.receive, args=(sock, filename, Receiver_IP_PORT))
            receive_thread.start()
            receive_thread.join()
        elif option == "3":
            sock.close()
            break
        else:
            print("Invalid option, please input again.")
            continue


if __name__ == '__main__':
    main()
