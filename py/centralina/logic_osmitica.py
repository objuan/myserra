
from django.db import models
from django.utils.translation import gettext_lazy as _
from enum import Enum
from pyfirmata2 import  INPUT,OUTPUT
from .ws_service import GetConn,GetEvent
import json
import logging

logger = logging.getLogger(__name__)

class Logic_Osmotica:
    pass