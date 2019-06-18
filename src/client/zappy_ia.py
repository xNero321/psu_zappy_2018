#!/bin/env python3

import socket

def start_of_ia(s):
    print(s.recv(4096))
    input()