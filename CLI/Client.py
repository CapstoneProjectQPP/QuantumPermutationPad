import socket
import queue
import json
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
        msg = self.string_to_json("REQUEST_HANDSHAKE", "0")
        self.connection_send(msg)
        self.connection_send('\n')

    def connection_send(self, message):
        print(message)
        if message != 'q':
            self.s.send(message.encode('ascii'))
            print("sent")

    def connection_recv(self):
        while True:
            s = self.s.recv(1024)
            self.mutex.acquire()
            self.recv_queue.put(s)
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


    @staticmethod
    def string_to_json(api_call, task_id, interface_type = "GC", sender_id = "0", payload_total_fragments = "0",
                       payload_fragment_number = "0", payload_size = "0", payload_content = "Hello World"):
        msg = {"api_call":api_call,
               "task_id":task_id,
               "interface_type":interface_type,
               "sender_id":sender_id,
               "payload_total_fragments": payload_total_fragments,
               "payload_fragment_number": payload_fragment_number,
               "payload_size": payload_size,
               "payload_content": payload_content}

        return json.dumps(msg)


