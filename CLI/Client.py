import socket
import queue
from threading import Lock
"""
Steps:
Get the user interaction
Make sure connection is established between CLI and Core
Send some message
Separate send message and listening into 2 threads
"""


class Client:

    def __init__(self, port, host, name):
        self.s = socket.socket()
        self.port = port
        self.host = host
        self.name = name
        self.recv_queue = queue.Queue()
        self.send_queue = queue.Queue()
        self.mutex = Lock()

    def connection_setup(self):
        self.s.connect((self.host, self.port))

        # SEND the handshake
        self.connection_send()

    def connection_send(self,
                        message='{"api_call":"REQUEST_HANDSHAKE","task_id":"2","interface_type":"T1","sender_id":"1"}\n'):
        print(message)
        if message != 'q':
            self.s.send(message.encode('ascii'))
            print("sent")

    def connection_recv(self):
        while True:
            s = self.s.recv(1024)
            self.mutex.acquire()
            self.recv_buffer.put(s)
            self.mutex.release()
            print("Received from server: "+s)

    def get_recv_message(self):
        self.mutex.acquire()
        if not self.recv_queue.empty():
            data = self.recv_queue.get()
            self.mutex.release()
            return data

        else:
            self.mutex.release()
            return 'Empty Queue'
        



