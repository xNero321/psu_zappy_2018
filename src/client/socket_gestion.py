#!/bin/env python3
import socket

broadcast_list = []

def get_look(s):
    s.send('Look\n'.encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')
    result = result.replace('[', '').replace(']', '').replace('\n', '').split(',')
    return result

def get_inventory(s):
    try:
        s.send('Inventory\n'.encode())
        result = s.recv(4096).decode('utf-8')
        while result.startswith('message'):
            manage_broadcast(result)
            result = s.recv(4096).decode('utf-8')
        while result.startswith('[ player'):
            result = s.recv(4096).decode('utf-8')
        result = [x for x in result.replace('[', '').replace(']', '').replace('\n', '').split(',')]
        final = {}
        for x in result:
            final[x.split(' ')[1]] = int(x.split(' ')[2])
        return final
    except:
        return []

def go_forward(s):
    s.send('Forward\n'.encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')

def take_object(s, item):
    s.send(('Take ' + item + '\n').encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')

def drop_object(s, item):
    s.send(('Set ' + item + '\n').encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')

def turn_right(s):
    s.send('Right\n'.encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')

def turn_left(s):
    s.send('Left\n'.encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')

def start_inquentation(s):
    s.send('Incantation\n'.encode())
    result = s.recv(4096).decode('utf-8')
    while result.startswith('message'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')
    if result == 'ko\n':
        return False
    return True

def broadcast(s, string):
    print('Send broadcast ' + string)
    s.send(('Broadcast ' + string + '\n').encode())
    s.recv(4096)

def get_lvl(s, lvl):
    result = s.recv(4096).decode('utf-8')
    while not result.startswith('Current'):
        manage_broadcast(result)
        result = s.recv(4096).decode('utf-8')
    if result.startswith('Current'):
        return int(result.split(':')[1].replace("']", ''))
    return lvl

def check_broadcast():
    return broadcast_list

def check_if_broadcast_ok(lvl):
    for m in broadcast_list:
        if int(m.split(', ')[1].split('|')[1].split(':')[1]) == lvl:
            return True
    return False

def manage_broadcast(string):
    if not string.startswith('message'):
        return
    player_id = int(string.split(', ')[1].split('|')[0].split(':')[1])
    if 'remove' in string.split(', ')[1].split('|')[1]:
        for m in broadcast_list:
            if player_id == int(m.split(', ')[1].split('|')[0].split(':')[1]):
                broadcast_list.remove(m)
    else:
        for m in broadcast_list:
            if player_id == int(m.split(', ')[1].split('|')[0].split(':')[1]):
                broadcast_list.remove(m)
        broadcast_list.append(string)