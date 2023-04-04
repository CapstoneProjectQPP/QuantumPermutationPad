from Client import *
import random
import logging
import sys
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
        for vector in str_list:
            msg = client.string_to_json("ENCRYPT", str(task_id), "GI", "0", "0", "0", str(sys.getsizeof(vector)), vector)
            client.to_outgoing_queue(msg)
            client.connection_send()
        return

    @staticmethod
    def ReceivedEncrypt():
        return

    @staticmethod
    def Decrypt():
        return

    @staticmethod
    def ReceivedDecrypt():
        return

