#!/usr/bin/env python3
from sys import stdout
import time
import sys
from cloud import *

class Recipe:
    name=""
    description=""
    N=0
    P=0
    K=0
    Ca=0
    Mg=0
    S=0
    Zn=0
    Mn=0
    Fe=0
    B=0
    Cu=0
    Mo=0
    Si=0
    Cl=0
    Na=0

    def __init__(self):
        pass

class HuettRecipe(Recipe):
   
    def __init__(self):
        self.name="Huett"
        self.description="Huett per insalate"
        self.N=116
        self.P=22
        self.K=201
        self.Ca=70
        self.Mg=20
        self.S=26
        self.Zn=0.15
        self.Mn=0.22
        self.Fe=2.50
        self.B=0.21
        self.Cu=0.03
        self.Mo=0.01
        self.Si=0
        self.Cl=0
        self.Na=0
    