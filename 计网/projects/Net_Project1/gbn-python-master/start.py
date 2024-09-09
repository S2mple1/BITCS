import os
import Sender
import Receiver
import socket
import threading
import utils


config = utils.read_config('config.ini')

Sender_ip = config['SenderHost']
Sender_port = int(config['SenderPort'])
Sender_ip_port = (Sender_ip, Sender_port)

Receiver_ip = config['ReceiverHost']
Receiver_port = int(config['ReceiverPort'])
Receiver_ip_PORT = (Receiver_ip, Receiver_port)

print('-' * 25 + '\n' + 'Server for GBN started' + '\n' + '-' * 25)

while True:
    choose = input("1.Send file\n2.Receive file\n3.Exit\nPlease input an option number(1, 2 or 3):")
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    if choose == "1":
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(Sender_ip_port)
        lock = threading.Lock()
        lock.acquire()
        while True:
            all_files = os.listdir()
            non_dir_files = [file for file in all_files if os.path.isfile(file)]
            print("Files in current directory: ")
            for file in non_dir_files:
                print("\t"+file)
            filename = input("Input the file name to be sent: ")
            if os.path.exists(filename):
                break
            else:
                print("File not found, please input again.")
                continue
        lock.release()
        send_thread = threading.Thread(target=Sender.send, args=(sock, filename, Sender_ip_port, Receiver_ip_PORT))
        send_thread.start()
        send_thread.join()

    elif choose == "2":
        sock.bind(Receiver_ip_PORT)
        lock = threading.Lock()
        lock.acquire()
        filename = input("Input the file name to be saved as: ")
        lock.release()
        receiver = Receiver.Receiver()
        receive_thread = threading.Thread(target=receiver.receive, args=(sock, filename, Receiver_ip_PORT))
        receive_thread.start()
        receive_thread.join()

    elif choose == "3":
        sock.close()
        break
    else:
        print("Invalid option, please input again.")
        continue
