#!/usr/bin/env python
# qjump python file
import time
import sys
import click
import os
from pathlib import Path
import subprocess


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
        key = line.split(" ")[0].strip()
        path = line.split(" ")[1].strip()
        
        # ensure unique key names 
        if(key in ret.keys()):
            print("ERROR! Duplicate key names in .qjump_save not allowed!")
            sys.exit(1)

        # ensure path exists
        if(valid_path(path) == False):
            print("ERROR! Path invalid!")
            sys.exit(1)

        # add to dict
        ret[key] = path
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

    # jump
    try:
        dest = key_to_path_map[key]
    except: 
        print("key doesn't exist!")
        sys.exit(1)
    os.chdir(dest)
    os.system('open -a Terminal .')
#    subprocess.run("open -a Terminal", shell=True)


# main function
if __name__ == '__main__':
    qjump()

'''
Python can't change the user's directory only the working directory. The only way around this is to create a new terminal window pop up which is not ideal. Might need to switch to bash to do this, but would need to do a simplified version. 

https://www.cyberciti.biz/faq/unix-howto-read-line-by-line-from-file/
'''
