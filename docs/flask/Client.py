import socket
import queue
import json
import threading
from threading import Lock
import time

PAYLOAD = 4096

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
        self.outgoing_mutex = Lock()

    def connection_setup(self):
        self.s.connect((self.host, self.port))
        print("socket:{}\n host:{}\n port:{}\n".format(self.s, self.host, self.port))
        # SEND the handshake
        # self.to_outgoing_queue(str(self.port))
        # self.connection_send()

    def connection_send(self):
        while True:
            if not self.send_queue.empty():
                self.outgoing_mutex.acquire()
                message = self.send_queue.get()
                self.outgoing_mutex.release()
                # print(message)
                self.s.send(message.encode('ascii'))
                # print("sent to port {}".format(self.port))

    def send_to_queue(self, message):
        self.outgoing_mutex.acquire()
        self.send_queue.put(message)
        self.outgoing_mutex.release()
        # print("OUTGOING QUEUE {}".format(message))

    def connection_recv(self):
        while True:
            msg = self.s.recv(PAYLOAD)
            self.mutex.acquire()
            self.recv_queue.put(msg)
            self.mutex.release()
            # print("Received from server: " + msg.decode('ascii'))

    def get_queue(self):
        while True:
            if not self.recv_queue.empty():
                self.mutex.acquire()
                data = self.recv_queue.get()
                self.mutex.release()
                return data

    def clear_queue(self):
        self.mutex.acquire()
        self.outgoing_mutex.acquire()

        self.send_queue.queue.clear()
        self.recv_queue.queue.clear()

        self.mutex.release()
        self.outgoing_mutex.release()
        return

    @staticmethod
    def string_to_json(api_call, task_id, interface_type="GC", sender_id="0",
                       payload_total_fragments="0", payload_fragment_number="0",
                       payload_size="0", payload_content="Hello World"):
        msg = {"api_call":api_call,
               "task_id":task_id,
               "interface_type":interface_type,
               "sender_id":sender_id,
               "payload_total_fragments": payload_total_fragments,
               "payload_fragment_number": payload_fragment_number,
               "payload_size": payload_size,
               "payload_content": payload_content}

        return json.dumps(msg)


