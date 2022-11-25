#!/usr/bin/env python
# qjump python file
import time
import sys
import click
import os
from pathlib import Path


'''
    Utility Helper Functions
'''
def valid_path(path):
    return os.path.exists(path)

'''
    File Helper Functions
'''
def get_qbin_path():
    return os.path.dirname(os.path.realpath(__file__))

def read_qfile():
    # open qfile
    try:
        qbin_path = get_qbin_path()
        qfile = open(qbin_path + "/.qjump_save", "r+")
    except FileNotFoundError as e: # if the file doesn't exist
        return {}
    
    ret = {}
    line = qfile.readline()
    while(len(line) > 0):
        print(line)
        print(line.split(" ")[1])
        # ensure unique key names 
        if(line.split(" ")[0] in ret.keys()):
            print("ERROR! Duplicate key names in .qjump_save not allowed!")
            sys.exit(1)

        # ensure path exists
        if(valid_path(line.split(" ")[1]) == False):
            print("ERROR! Path invalid!")
            sys.exit(1)

        # add to dict
        ret[line.split(" ")[0]] = line.split(" ")[1] 
        line = qfile.readline()

    # close qfile
    qfile.close()
    return ret 

def write_qfile():
    # open qfile
    qfile = open(".qjump_save", "w+")
    # TODO
    qfile.close()


# TODOS
# TODO file readers / format
# TODO create new keys
# TODO modify old keys
# TODO JUMP 







# qjump command
@click.command(short_help="quick jump command, ability to jump easily")
@click.argument("key")
def qjump(key):
    '''Ability to jump to any special location {NAME}. Allows for custom paths. To create a path use the "-s/--set {PATH}" and the argument {NAME} is the key for that path. You can also change paths for a specific key with -m/--modify"

    Example Usage: "qjump TEMP_KEY" or "qjump TEMP_KEY_2 --set ~/test/test/"
    '''
    # read file
    key_to_path_map = read_qfile()

    for key in key_to_path_map.keys():
        print(f"{key} {key_to_path_map[key]}")

# main function
if __name__ == '__main__':
    qjump()
