#!/bin/env python3
import socket
from sys import exit

class info_ia:
    map_size_x, map_size_y = 0, 0
    number = 0

def check_good_start(s):
    data = s.recv(4096).decode('utf-8')
    if data != "WELCOME\n":
        exit(84)

def start_of_ia(s, arg):
    check_good_start(s)
    s.send(str.encode(arg.n))
    info_ia.number = int(s.recv(4096).decode('utf-8'))
    print(str(info_ia.number))