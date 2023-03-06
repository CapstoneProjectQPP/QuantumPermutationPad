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


class QPP_commands:
    @classmethod
    def test_vector_gen(cls, args, logger):
        logger.debug("The vector length is {} and the number of vectors is {}".format(args[0],args[1]))
        return [100, 100]
    
    @classmethod
    def cipher_text_gen(cls, args, logger):
        logger.debug("The vector length is {} and the number of vectors is {}".format(args[0],args[1]))
        return [100, 100]

    @classmethod
    def qpp_encrypt(cls, args):
        return

    @classmethod
    def qpp_decrypt(cls, args):
        return

    @classmethod
    def aes_encrypt(cls, args):
        return

    @classmethod
    def aes_decrypt(cls, args):
        return


class QPP_parser:
    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(
            description="QPP testbed Commandline Interface"
        )

        # Creating arguments for commandline parser

        # parser.add_argument(
        #     "-t",
        #     "--test-type",
        #     tyoe=str,
        #     nargs=1,
        #     metavar="test_type",
        #     help="Specifiy type of test to run",
        # )

        # by default, don't run and compare QPP with AES
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
        
        
        
        self.logger = None
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

        logger.info("Begin test vector generation")
        test_vectors = QPP_commands.test_vector_gen(args.vector, logger)
        logger.info("Finished test vector generation")
        
        if args.encryption:
            logger.info("Begin QPP encryption")
            qpp_cipher = QPP_commands.qpp_encrypt(test_vectors)
            logger.info("Finsihed QPP encryption")
            if args.AES:
                logger.info("Begin AES encryption")
                aes_cipher = QPP_commands.aes_encrypt(test_vectors)
                logger.info("Finished AES encryption")
                
        
        if args.cipher_text:
            logger.info("Begin Ciphertext generation")
            QPP_commands.cipher_text_gen(test_vectors, logger)
            logger.info("Finished Ciphertext generation")
        
        if args.decryption:
            logger.info("Begin QPP encryption")
            qpp_results = QPP_commands.qpp_decrypt(qpp_cipher)
            logger.info("Finsihed QPP encryption")
            if args.AES:
                logger.info("Begin AES encryption")
                aes_results = QPP_commands.aes_decrypt(aes_cipher)
                logger.info("Finished AES encryption")


if __name__ == "__main__":
    parser = QPP_parser()
    parser.UserInput()
