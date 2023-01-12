from robot.libraries.BuiltIn import BuiltIn
import robot.api.logger as logger
import subprocess as sb
import threading
import os
class E2E:
    def simpleAdding_api(self, a: int, b: int) -> int:
        logger.info("Adding started")
        return a + b
    def compareStrings_api(self, a: str, b: str) -> bool:
        logger.info("Comparing strings")
        return a == b
    def encryptionAesTest_api(self, plaintext: str, key: str ) -> str:
        logger.info("Encrypting string")
        # os.chdir("..")
        os.chdir("..")
        print(os.getcwd())
        sb.check_call("cd C++", shell=True)
        
        #clean the project and make it
        print("cleaning the project and make it")
        sb.call("make clean", shell=True)
        sb.call("make", shell=True)
        #set up timer
        t = threading.Timer(50, self.timeout)
        #run the program
        print("running the program")

        proc = sb.Popen("./bin/qpp.exe", shell=True, stdin=sb.PIPE, stdout=sb.PIPE,
            stderr=sb.PIPE)

        #give the program the inputs,(assume here inputs are command line inputs)
        proc.stdin.write(plaintext.encode("utf-8"))
        out, err = proc.communicate(key.encode("utf-8"))
        #cancel the timer
        t.cancel()
        #check the output by first decode the output
        out = out.decode("utf-8")
        err = err.decode("utf-8")
        return out

    def timeout():
        print('timeout')
        exit(3)
    