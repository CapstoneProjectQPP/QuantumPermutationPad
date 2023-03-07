#! /usr/bin/env python3
# importing the required modules
import os
import argparse, logging


LOG_FILE = "test.log"


class Logger:
    def init(file, level) -> None:

        # to format the log messages that are printed to terminal
        logging.basicConfig(
            format="%(levelname)s : %(name)s : %(funcName)s[line %(lineno)s] : %(message)s"
        )

        # create logger instance
        log = logging.getLogger(__name__)

        # set log level
        log.setLevel(level)

        # format the .log file messages
        if file != None:
            file_handler = logging.FileHandler(file)
            formatter = logging.Formatter(
                "%(asctime)s : %(levelname)s : Module %(module)s : %(funcName)s[line %(lineno)s] : %(name)s : %(message)s"
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

    def test_vector_gen(self, args):
        self.logger.info("Being Testvector generation")
        self.logger.debug(
            "The vector length is {} and the number of vectors is {}".format(
                args[0], args[1]
            )
        )
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
        self.logger.info("Begin comparison between decrypted results and plaintext")

        self.logger.info("Finished comparison between decrypted results and plaintext")
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
        global LOG_FILE

        # parse the arguments from standard input
        args = self.parser.parse_args()

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

        QPP_commands = Commands(logger)

        test_vectors = QPP_commands.test_vector_gen(args.vector)

        if args.encryption:
            qpp_cipher = QPP_commands.encrypt(test_vectors, "QPP")
            if args.AES:
                aes_cipher = QPP_commands.encrypt(test_vectors, "AES")

        if args.cipher_text:
            QPP_commands.cipher_text_gen(test_vectors)

        if args.decryption:
            qpp_results = QPP_commands.decrypt(qpp_cipher, "QPP")
            if args.AES:
                aes_results = QPP_commands.decrypt(aes_cipher, "AES")
        
        QPP_commands.compare_results(qpp_results, test_vectors)
        QPP_commands.compare_results(aes_results, test_vectors)

if __name__ == "__main__":
    parser = QPP_parser()
    parser.UserInput()
