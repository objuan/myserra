
import logging
import locale
import re
locale.getpreferredencoding()
from .ws_service import *
#from .runtime_service import _CustomLog

__all__ = ['CustomLog']

class CustomLog(logging.StreamHandler):
    def __init__(self):
        logging.StreamHandler.__init__(self)
        #self.log = _CustomLog()

    def emit(self, record):
        ansi_escape = re.compile(r'''
            \x1B  # ESC
            (?:   # 7-bit C1 Fe (except CSI)
                [@-Z\\-_]
            |     # or [ for CSI, followed by a control sequence
                \[
                [0-?]*  # Parameter bytes
                [ -/]*  # Intermediate bytes
                [@-~]   # Final byte
            )
            ''', re.VERBOSE)

        msg = self.format(record)
        #print(str(ansi_escape.sub('', msg)))
        #print(GetLog())
        if (GetLog()):
            GetLog().fire(ansi_escape.sub('', msg))
        #print(">>")