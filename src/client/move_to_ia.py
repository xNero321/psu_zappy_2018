#!/bin/env python3
import socket_gestion

def get_info_direction(s, lvl, player_id):
    direction = -1
    for m in socket_gestion.check_broadcast():
        if player_id == -1:
            if int(m.split(', ')[1].split('|')[1].split(':')[1]) == lvl:
                player_id = int(m.split(', ')[1].split('|')[0].split(':')[1])
                direction = int(m.split(', ')[0].split(' ')[1])
        else:
            if int(m.split(', ')[1].split('|')[1].split(':')[1]) == lvl and int(m.split(', ')[1].split('|')[0].split(':')[1]) == player_id:
                direction = int(m.split(', ')[0].split(' ')[1])
    return player_id, direction

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

def move_to_ia(s, lvl):
    print('Move to another player to incentation')
    player_id, direction = get_info_direction(s, lvl, -1)
    while direction != 0 and not check_player_nb(lvl, socket_gestion.get_look(s)):
        print(direction)
        if direction == 1:
            socket_gestion.go_forward(s)
        if direction == 2:
            socket_gestion.go_forward(s)
            socket_gestion.turn_left(s)
            socket_gestion.go_forward(s)
        if direction == 3:
            socket_gestion.turn_left(s)
            socket_gestion.go_forward(s)
        if direction == 4:
            socket_gestion.turn_left(s)
            socket_gestion.go_forward(s)
            socket_gestion.turn_left(s)
            socket_gestion.go_forward(s)
        if direction == 5:
            socket_gestion.turn_left(s)
            socket_gestion.turn_left(s)
            socket_gestion.go_forward(s)
        if direction == 6:
            socket_gestion.turn_right(s)
            socket_gestion.go_forward(s)
            socket_gestion.turn_right(s)
            socket_gestion.go_forward(s)
        if direction == 7:
            socket_gestion.turn_right(s)
            socket_gestion.go_forward(s)
        if direction == 8:
            socket_gestion.go_forward(s)
            socket_gestion.turn_right(s)
            socket_gestion.go_forward(s)
        player_id, direction = get_info_direction(s, lvl, player_id)
    print(socket_gestion.get_look(s))
