from robot.libraries.BuiltIn import BuiltIn
import robot.api.logger as logger


class E2E:
    def simpleAdding_api(self, a: int, b: int) -> int:
        logger.info("Adding started")
        return a + b
    def compareStrings_api(self, a: str, b: str) -> bool:
        logger.info("Comparing strings")
        return a == b
