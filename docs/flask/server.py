#! /usr/bin/env python3

import socket
import sys
import time


def server_program():
    # get the hostname
    host = socket.gethostname()
    port = int(sys.argv[1])  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    print("Listening on port:{}...".format(port))
    # configure how many client the server can listen simultaneously
    server_socket.listen(1)
    conn, address = server_socket.accept()  # accept new connection
    print("Connection from: " + str(address))
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(1024).decode()
        if not data:
            # if data is not received break
            break
#        print("from connected user: " + str(data))
        conn.send(data.encode())

    conn.close()  # close the connection


if __name__ == '__main__':
    server_program()
