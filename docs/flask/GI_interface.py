import re
from Client import *
import random
import logging
import sys
import json
import time
LOG_FILE = "out.log"


class Logger:
    def init(file, level) -> None:

        # to format the log messages that are printed to terminal
        logging.basicConfig(
            format="%(levelname)s : %(name)s : %(funcName)s[line %(lineno)s]"
                   + ": %(message)s"
        )

        # create logger instance
        log = logging.getLogger(__name__)

        # set log level
        log.setLevel(level)

        # format the .log file messages
        if file is not None:
            file_handler = logging.FileHandler(file)
            formatter = logging.Formatter(
                "%(asctime)s : %(levelname)s : Module %(module)s"
                + ": %(funcName)s[line %(lineno)s] : %(name)s : %(message)s"
            )
            file_handler.setFormatter(formatter)
            log.addHandler(file_handler)

        return log


class Commands:
    def __init__(self, logger) -> None:
        self.logger = logger
        return

    @staticmethod
    def random_string(len):
        random_string = ""
        for ii in range(len):
            random_int = random.randint(33, 126)
            random_string += chr(random_int)
        return random_string

    @staticmethod
    def test_vector_gen(args):
        vec_len = args[0]
        vec_num = args[1]
        test_list = [""] * vec_num
        for ii in range(vec_num):
            test_list[ii] = Commands.random_string(vec_len)
        return test_list


class GI:
    @staticmethod
    def Encrypt(task_id, str_list, client):
#       logger = Logger.init(LOG_FILE, logging.DEBUG)
        ii = 1
        for vector in str_list:
            msg = client.string_to_json("ENCRYPT", str(task_id), "GI", "0",
                                        len(str_list), ii,
                                        str(sys.getsizeof(str_list)), vector)
            client.send_to_queue(msg)
            ii += 1
        return

    @staticmethod
    def ReceivedEncrypt(task_id, client):
        ii = 1
        cipher_list = []
        while True:
            data = client.get_queue()
            recv_msg = data.decode('ascii')
            try:
                decoded_msg = json.loads(recv_msg)
            except json.decoder.JSONDecodeError:
                delim ='.(?={"api_call": "ENCRYPT", "task_id": "\d", "interface_type": "GI", "sender_id": "0",)'
                recv_msg = re.split(delim, recv_msg)
                last_msg = recv_msg[-1]
                for msg in recv_msg:
                    if msg != last_msg:
                        msg = msg + "}"
                    decoded_msg = json.loads(msg)
                    cipher_list.append(decoded_msg.get('payload_content'))
            else:
                cipher_list.append(decoded_msg.get('payload_content'))

            if decoded_msg.get('payload_total_fragments') == \
               decoded_msg.get('payload_fragment_number'):
                return cipher_list
            ii += 1

    @staticmethod
    def Decrypt(task_id, str_list, client):
        ii = 1
        for vector in str_list:
            msg = client.string_to_json("DECRYPT", str(task_id), "GI", "0",
                                        len(str_list), ii,
                                        str(sys.getsizeof(str_list)), vector)
            client.send_to_queue(msg)
            ii += 1
        return

    @staticmethod
    def ReceivedDecrypt(task_id, client):
        ii = 1
        cipher_list = []
        while True:
            data = client.get_queue()
            recv_msg = data.decode('ascii')
            try:
                decoded_msg = json.loads(recv_msg)
            except json.decoder.JSONDecodeError:
                delim ='.(?={"api_call": "DECRYPT", "task_id": "\d", "interface_type": "GI", "sender_id": "0",)'
                recv_msg = re.split(delim, recv_msg)
                last_msg = recv_msg[-1]
                for msg in recv_msg:
                    if msg != last_msg:
                        msg = msg + "}"
                    decoded_msg = json.loads(msg)
                    cipher_list.append(decoded_msg.get('payload_content'))
            else:
                cipher_list.append(decoded_msg.get('payload_content'))

            if decoded_msg.get('payload_total_fragments') == \
               decoded_msg.get('payload_fragment_number'):
                return cipher_list
            ii += 1

