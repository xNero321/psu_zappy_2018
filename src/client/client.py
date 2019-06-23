#!/bin/env python3
import argparse
import sys

sys.path.append('./src/client/')

import socket_connection
import zappy_ia

def main():
    args = arg_parsing()
    s = socket_connection.create_and_connect(args.p, args.m)
    zappy_ia.start_of_ia(s, args)
    socket_connection.close_socket(s)

def arg_parsing():
    parser = argparse.ArgumentParser(description='zappy ia')
    parser.add_argument('-p', type=int, required=True, help='the port number')
    parser.add_argument('-n', type=str, required=True, help='the name of the team')
    parser.add_argument('-m', type=str, default='localhost', help='the name of the machine; localhost by default')
    return parser.parse_args()

if __name__ == '__main__':
    main()