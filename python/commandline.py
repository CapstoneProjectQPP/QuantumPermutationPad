# importing the required modules
import os
import argparse, logging

LOG_FILE = "test.log"

class Logger():
    def init(file, level) -> None:
        # create logger
        log = logging.getLogger(__name__)
        
        # set log level
        log.setLevel(level)
        
        if file != None:
            file_handler = logging.FileHandler(file)
            formatter = logging.Formatter('%(asctime)s : %(levelname)s : %(name)s : %(message)s')
            file_handler.setFormatter(formatter)
            log.addHandler(file_handler)
        
        return log

class QPP_commands():
    
    @classmethod
    def test_vector_gen(cls, args):
        return
    
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

        

class QPP_parser():

    def __init__(self) -> None:
        self.parser = argparse.ArgumentParser(description="QPP testbed Commandline Interface")
             
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
            "--run-AES",
            action="store_true",
            help="Run test with AES in addition to QPP",
        )

        self.parser.add_argument(
            "-e",
            "--encryption-only",
            action="store_true",
            help="Only run an encryption test",
        )

        self.parser.add_argument(
            "-d",
            "--decryption_only",
            action="store_true",
            help="Only run a decryption test, using ciphertexts with .aes or .qpp file extensions",
        )

        self.parser.add_argument(
            "-ct",
            "--cipher-text",
            action="store_true",
            help="Keep all generated cipher-texts in directory after encryption test",
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
            "--vector",
            type=int,
            nargs=2,
            metavar=("test_len","test_num"),
            help="Specifiy number of elements and number of vectors",
        )
        
        
        return

    def UserInput(self) -> bool:
        
        log_file = None
        
        # parse the arguments from standard input
        args = self.parser.parse_args()
        print(args)

        if args.verbose:
            log_level = logging.DEBUG
        else:
            log_level = logging.ERROR
        
        if args.logging:
            log_file = LOG_FILE
        else:
            log_file = None    
        
        # configure logging to user preference
        logger = Logger.init(log_file, log_level)
        
        # logging.debug("These are the arguments {}".format(args))
        # logging.info("These are the arguments {}".format(args))
        
        logger.debug("DEBUG_IN_PROGRAM")
        logger.info("INFO_IN_PROGRAM")
        logger.warning("WARNING_IN_PROGRAM")
        logger.error("ERROR_IN_PROGRAM")
        logger.critical("CRITICAL_IN_PROGRAM")
        
        QPP_commands.test_vector_gen(args.vector)


if __name__ == "__main__":
    parser = QPP_parser()
    parser.UserInput()
    