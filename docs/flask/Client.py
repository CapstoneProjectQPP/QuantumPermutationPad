import socket
import re
import queue
import json
import threading
import time
import logging 

from threading import Lock
from GI_interface import Logger

logger = Logger.init(None, logging.DEBUG)
PAYLOAD = 4096
delim ='.(?={"api_call": "ENCRYPT", "task_id": "\d", "interface_type": "GI", "sender_id": "0",)'
encoding = 'utf-8'

"""
Steps:
Get the user interaction
Make sure connection is established between CLI and Co(\{(?:(?>[^{}"'\/]+)|(?>"(?:(?>[^\\"]+)|\\.)*")|(?>'(?:(?>[^\\']+)|\\.)*')|(?>\/\/.*\n)|(?>\/\*.*?\*\/)|(?-1))*\})re
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
        logger.debug("socket:{}\n host:{}\n port:{}\n".format(self.s, self.host, self.port))
        # SEND the handshake
        # self.to_outgoing_queue(str(self.port))
        # self.connection_send()

    def connection_send(self):
        while True:
            if not self.send_queue.empty():
                self.outgoing_mutex.acquire()
                message = self.send_queue.get()
                self.outgoing_mutex.release()
                self.s.send(message.encode(encoding))
                self.s.send('\n'.encode(encoding))
    def send_to_queue(self, message):
        # self.outgoing_mutex.acquire()
        self.send_queue.put(message)
        # self.outgoing_mutex.release()
        # logger.debug("OUTGOING QUEUE {}".format(message))

    def connection_recv(self):
        decoded_msg = None
        data = b''
        regex_group = None
        while True:
            data  += self.s.recv(PAYLOAD)
            logger.debug('data'.center(40, '_') + '\n')
            logger.debug(data)
            recv_msg = data.decode(encoding)
            if recv_msg != '\n':
                try:
                    decoded_msg = json.loads(recv_msg)
                except json.decoder.JSONDecodeError:
                    logger.debug('recv msg'.center(40, '_') + '\n' + recv_msg + '\n')
                    delim = r"(\{(?:(?>[^{}\"'\/]+)|(?>\"(?:(?>[^\\\\\"]+)|\\\\.)*\")|(?>'(?:(?>[^\\\\']+)|\\\\.)*')|(?>\/\/.*\\n)|(?>\/\*.*?\*\/)|)*\})"
                    pattern = re.compile(delim, re.M | re.S | re.I)
                    logger.debug('delim'.center(40,'_') + '\n' + delim + '\n')

                    for msg in re.finditer(pattern, recv_msg):
                        msg = msg.group(0)
                        logger.debug('msg'.center(40, '_') + '\n' + msg + '\n')
                        try:
                            decoded_msg = json.loads(msg)
                        except json.decoder.JSONDecodeError:
                           data = msg.encode(encoding)
                        else:
                            self.recv_queue.put(msg.encode(encoding))
                            data = b''
                else:
                    self.recv_queue.put(recv_msg.encode(encoding))
                    data = b''
            else:
                continue

    def get_queue(self):
        while True:
            if not self.recv_queue.empty():
                # self.mutex.acquire()
                data = self.recv_queue.get()
                # self.mutex.release()
                return data

    def clear_queue(self):
        # self.mutex.acquire()
        # self.outgoing_mutex.acquire()
        self.send_queue.queue.clear()
        self.recv_queue.queue.clear()
        # self.mutex.release()
        # self.outgoing_mutex.release()
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
               "payload_frag_number": payload_fragment_number,
               "payload_size": payload_size,
               "payload_content": payload_content}

        return json.dumps(msg)


