#!/bin/env python3
import socket_gestion
from time import sleep
import move_to_ia

def require_obj(inventory, level):
    if level == 1 and inventory['linemate'] >= 1:
            return False
    if level == 2 and inventory['linemate'] >= 1 and inventory['deraumere'] >= 1 and inventory['sibur'] >= 1:
        return False
    if level == 3 and inventory['linemate'] >= 2 and inventory['sibur'] >= 1 and inventory['phiras'] >= 2:
        return False
    return True

def choose_direction(lvl, inventory):
    if lvl == 1:
        return 'linemate'
    if lvl == 2:
        if inventory['linemate'] >= 1:
            if inventory['deraumere'] >= 1:
                return 'sibur'
            else:
                return 'deraumere'
        else:
            return 'linemate'
    if lvl == 3:
        if inventory['linemate'] >= 2:
            if inventory['sibur'] >= 1:
                return 'phiras'
            else:
                return 'sibur'
        else:
            return 'linemate'
    return "Food"

def change_direction(s, direction):
    if direction == 1:
        socket_gestion.turn_left(s)
    elif direction == 3:
        socket_gestion.turn_right(s)
    elif direction == 4:
        socket_gestion.go_forward(s)
        socket_gestion.turn_left(s)
    elif direction == 8:
        socket_gestion.go_forward(s)
        socket_gestion.turn_right(s)
    elif direction == 9:
        socket_gestion.go_forward(s)
        socket_gestion.go_forward(s)
        socket_gestion.turn_left(s)
    elif direction == 15:
        socket_gestion.go_forward(s)
        socket_gestion.go_forward(s)
        socket_gestion.turn_right(s)

def check_player_nb(lvl, map):
    if lvl == 2 or lvl == 3:
        if 'player player' in map[0]:
            return True
    if lvl == 4 or lvl == 5:
        if 'player player player' in map[0]:
            return True
    if lvl == 6 or lvl == 7:
        if 'player player player player' in map[0]:
            return True
    return False

def go_get_rock(s, lvl, map, inventory, info_ia):
    objectif = False
    direction = 0
    i = 0
    while objectif == False:
        if i > info_ia.map_size_x:
            i = 0
            socket_gestion.turn_left(s)
        socket_gestion.go_forward(s)
        socket_gestion.take_object(s, choose_direction(lvl, inventory))
        socket_gestion.take_object(s, 'food')
        inventory = socket_gestion.get_inventory(s)
        map = socket_gestion.get_look(s)
        if require_obj(inventory, lvl) == False or socket_gestion.check_if_broadcast_ok(lvl):
            objectif = True
            break
        for i, m in enumerate(map):
            if choose_direction(lvl, inventory) in m:
                direction = i
                break
        change_direction(s, direction)
        i += 1

def drop_all_inquentation(s, lvl, info_ia):
    for obj in socket_gestion.get_look(s)[0].split(' '):
        socket_gestion.take_object(s, obj)
    if lvl == 1:
        socket_gestion.drop_object(s, 'linemate')
    if lvl == 2:
        socket_gestion.drop_object(s, 'linemate')
        socket_gestion.drop_object(s, 'deraumere')
        socket_gestion.drop_object(s, 'sibur')
    if lvl == 3:
        socket_gestion.drop_object(s, 'linemate')
        socket_gestion.drop_object(s, 'linemate')
        socket_gestion.drop_object(s, 'sibur')
        socket_gestion.drop_object(s, 'phiras')
        socket_gestion.drop_object(s, 'phiras')
    if lvl != 1:
        socket_gestion.broadcast(s, 'player:{}|level:{}'.format(info_ia.number, lvl))
        print('Waiting other player')
        map = socket_gestion.get_look(s)
        while not check_player_nb(lvl, map):
            map = socket_gestion.get_look(s)
            socket_gestion.broadcast(s, 'player:{}|level:{}'.format(info_ia.number, lvl))
    sleep(1)

def level(s, info_ia):
    my_map = socket_gestion.get_look(s)
    inventory = socket_gestion.get_inventory(s)
    lvl = 1
    while 1:
        go_get_rock(s, lvl, my_map, inventory, info_ia)
        if lvl != 8:
            if require_obj(socket_gestion.get_inventory(s), lvl):
                move_to_ia.move_to_ia(s, lvl)
            else:
                drop_all_inquentation(s, lvl, info_ia)
                print('Start inquentation')
                if not socket_gestion.start_inquentation(s):
                    print('Echec inquentaion, manque de chevre a sacrifier')
                    s.recv(4096)
            lvl = socket_gestion.get_lvl(s, level)
            print('Success pass the level {}'.format(lvl))
            my_map = socket_gestion.get_look(s)
            inventory = socket_gestion.get_inventory(s)