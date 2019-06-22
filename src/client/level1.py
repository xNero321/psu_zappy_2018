#!/bin/env python3
import socket_gestion

def require_obj(inventory, level):
    if level == 1:
        if inventory['linemate'] >= 1:
            return False
    return True

def choose_direction(lvl, inventory):
        if lvl == 1:
            return 'linemate'

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

def go_get_rock(s, lvl, map, inventory):
    objectif = False
    direction = 0
    while objectif == False:
        socket_gestion.go_forward(s)
        socket_gestion.take_object(s, choose_direction(lvl, inventory))
        socket_gestion.take_object(s, 'food')
        inventory = socket_gestion.get_inventory(s)
        map = socket_gestion.get_look(s)
        if require_obj(inventory, lvl) == False:
            objectif = True
            break
        for i, m in enumerate(map):
            if choose_direction(lvl, inventory) in m:
                direction = i
                break
        change_direction(s, direction)

def drop_all_inquentation(s, lvl):
    if lvl == 1:
        socket_gestion.drop_object(s, 'linemate')

def level1(s, info_ia):
    map = socket_gestion.get_look(s)
    inventory = socket_gestion.get_inventory(s)
    lvl = 1
    while 1:
        while require_obj(inventory, lvl):
            go_get_rock(s, lvl, map, inventory)
            map = socket_gestion.get_look(s)
            inventory = socket_gestion.get_inventory(s)
        if lvl != 8:
            print('Start inquentation')
            drop_all_inquentation(s, lvl)
            if socket_gestion.start_inquentation(s):
                lvl += 1
                print('Success pass the level')
            else:
                print('Echec inquentaion, manque de chevre a sacrifier')