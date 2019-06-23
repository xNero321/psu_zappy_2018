#!/bin/env python3
import socket
from level1 import level
from sys import exit
from sys import stderr

class info_ia:
    map_size_x, map_size_y = 0, 0
    number = 0

def check_good_start(s):
    data = s.recv(4096).decode('utf-8')
    if data != "WELCOME\n":
        exit(84)

def check_return_team(s, arg):
    s.send(str.encode(arg.n + '\n'))
    data = s.recv(4096)
    try:
        if data.decode('utf-8') == 'ko\n':
            print('recv ko went team was send', file=stderr)
            exit(84)
    except:
        print('recv ko went team was send', file=stderr)
        exit(84)
    try:
        tab = data.decode('utf-8').split('\n')
        info_ia.number = int(tab[0])
        info_ia.map_size_x = int(tab[1].split(' ')[0])
        info_ia.map_size_x = int(tab[1].split(' ')[1])
    except:
        info_ia.number = int(data.decode('utf-8')[:-1])
        data = s.recv(4096)
        info_ia.map_size_x = int(data.split(' ')[0])
        info_ia.map_size_y = int(data.split(' ')[1][:-1])

def start_of_ia(s, arg):
    check_good_start(s)
    check_return_team(s, arg)
    level(s, info_ia)