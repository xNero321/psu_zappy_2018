#!/bin/env python3
import socket
from sys import stderr
from sys import exit

def create_and_connect(port, ip):
    try:
        s = socket.socket()
        s.connect((ip, port))
        print('Connect to {} : {}'.format(ip, port))
        return s
    except:
        print("Can't connect to {} : {}".format(ip, port), file=stderr)
        exit(84);

def close_socket(s):
    s.close()