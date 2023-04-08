#! /usr/bin/env python3
# importing the required modules
import argparse
import logging
import random
from Client import *
import json
import threading
LOG_FILE = "test.log"

cv = threading.Condition()

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


class GI:
    @staticmethod
    def Encrypt():
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

    def test_vector_gen(self, args):
        self.logger.info("Being Testvector generation")
        vec_len = args[0]
        vec_num = args[1]
        test_list = [""] * vec_num

        for ii in range(vec_num):
            test_list[ii] = Commands.random_string(vec_len)

        self.logger.debug(
            "The vector length is {} and the number of vectors is {}".format(
                args[0], args[1]
            )
        )
        self.logger.debug("Test vectors {}".format(test_list))
        self.logger.info("Finished Testvector generation")
        return [100, 100]

    def cipher_text_gen(self, args):
        self.logger.info("Being Ciphertext generation")
        self.logger.debug(
            "The vector length is {} and the number of vectors is {}".format(
                args[0], args[1]
            )
        )
        self.logger.info("Finished Ciphertext generation")
        return [100, 100]

    def encrypt(self, args, type="QPP"):
        self.logger.info("Begin {} Encryption".format(type))

        self.logger.info("Finished {} Encryption".format(type))
        return

    def decrypt(self, args, type="QPP"):
        self.logger.info("Begin {} Deryption".format(type))

        self.logger.info("Finished {} Decryption".format(type))
        return

    def compare_results(self, results, tests):
        self.logger.info("Begin comparison between results and plaintext")

        self.logger.info("Finished comparison between results and plaintext")
        return



class QPP_parser:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(
            description="QPP testbed Commandline Interface"
        )

        # Creating arguments for commandline parser
        self.parser.add_argument(
            "-aes",
            "--AES",
            action="store_true",
            help="Run test with AES in addition to QPP",
        )

        self.parser.add_argument(
            "-e",
            "--encryption",
            action="store_true",
            help="Run an encryption test",
        )

        self.parser.add_argument(
            "-d",
            "--decryption",
            action="store_true",
            help="Run a decryption test, using ciphertexts with .aes or .qpp file extensions",
        )

        self.parser.add_argument(
            "-c",
            "--cipher-text",
            action="store_true",
            help="Generate cipher-texts in directory",
        )

        self.parser.add_argument(
            "-l",
            "--logging",
            action="store_true",
            help="Print log into a test.log file",
        )

        self.parser.add_argument(
            "-v",
            "--verbose",
            action="store_true",
            help="Show Debug messages in logs",
        )

        self.parser.add_argument(
            "-p",
            "--vector",
            type=int,
            nargs=2,
            metavar=("test_len", "test_num"),
            default=(150, 200),
            help="Specifiy number of elements and number of vectors",
        )

        return

    def UserInput(self) -> bool:
        task_id = 0
        global LOG_FILE
        #setup connection to Core Complex
        print("CLIENT")
        
        client = Client(64999,'127.0.0.1','CLI')
        client.connection_setup()
        
        print("THREAD CREATE")
        
        # multithreading
        incoming_t = threading.Thread(target=client.connection_recv, args=())
        print("THREAD OUT")
        outgoing_t = threading.Thread(target=client.connection_send, args=())
        print("THREAD MSG")
        print_msg_t = threading.Thread(target=client.print_outgoing_queue, args=())
        
        print("THREAD INCOME")
        
        incoming_t.start()
        print("THREAD OUTGO")
        outgoing_t.start()
        print("THREAD START")
        print_msg_t.start()

        print("THREAD START")
        # parse the arguments from standard input
        while True:
            userinput = input("-> ")
            args = self.parser.parse_args([userinput])
            print(args)

            if args.verbose:
                log_level = logging.DEBUG
            else:
                log_level = logging.ERROR

            if not args.logging:
                LOG_FILE = None

            # configure logging to user preference
            logger = Logger.init(LOG_FILE, log_level)

            logger.debug("DEBUG_IN_PROGRAM")
            logger.info("INFO_IN_PROGRAM")
            logger.warning("WARNING_IN_PROGRAM")
            logger.error("ERROR_IN_PROGRAM")
            logger.critical("CRITICAL_IN_PROGRAM")

            commands = Commands(logger)

            # test_vectors = QPP_commands.test_vector_gen(args.vector)



            if args.encryption:
                # qpp_cipher = QPP_commands.encrypt(test_vectors, "QPP")
                # if args.AES:
                #     aes_cipher = QPP_commands.encrypt(test_vectors, "AES")
                print("Send encryption")
                #{"api_call":"REQUEST_HANDSHAKE","task_id":"2","interface_type":"T1","sender_id":"1"}\n
                task_id += 1
                msg = client.string_to_json("ENCRYPT",task_id, "GC", 0, 0, 0, 0, "Hello World")
                # client.connection_send(msg)
                # client.connection_send('\n')
                
                # recv = client.get_recv_message()
                # while recv == None:
                #     recv = client.get_recv_message()
                #     continue
                # print(recv)
                #send the encryption data to the CoreComplex
                
                client.to_outgoing_queue(msg)

            elif args.cipher_text:
                print("Hi")

            elif args.decryption:
                print("Decryption")


                #{"api_call":"REQUEST_HANDSHAKE","task_id":"2","interface_type":"T1","sender_id":"1"}\n
                task_id += 1
                msg = client.string_to_json("DECRYPT",task_id, "GC", 0, 0, 0, 0, "Hello World")
                
                client.to_outgoing_queue(msg)

                #recieve the decryption data from the CoreComplex

            # QPP_commands.compare_results(qpp_results, test_vectors)
            # QPP_commands.compare_results(aes_results, test_vectors)
            
        producer_t.join()


if __name__ == "__main__":
    parser = QPP_parser()
    parser.UserInput()