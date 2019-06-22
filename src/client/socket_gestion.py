#!/bin/env python3
import socket

def get_look(s):
    s.send('Look\n'.encode())
    result = s.recv(4096).decode('utf-8').replace('[', '').replace(']', '').replace('\n', '').split(',')
    return result

def get_inventory(s):
    s.send('Inventory\n'.encode())
    result = [x for x in s.recv(4096).decode('utf-8').replace('[', '').replace(']', '').replace('\n', '').split(',')]
    print(result)
    final = {}
    for x in result:
        final[x.split(' ')[1]] = int(x.split(' ')[2])
    return final

def go_forward(s):
    s.send('Forward\n'.encode())
    s.recv(4096)

def take_object(s, item):
    s.send(('Take ' + item + '\n').encode())
    s.recv(4096)

def drop_object(s, item):
    s.send(('Set ' + item + '\n').encode())
    s.recv(4096)

def turn_right(s):
    s.send('Right\n'.encode())
    s.recv(4096)

def turn_left(s):
    s.send('Left\n'.encode())
    s.recv(4096)

def start_inquentation(s):
    s.send('Incantation\n'.encode())
    result = s.recv(4096).decode('utf_8')
    if result == 'ko\n':
        return False
    return True