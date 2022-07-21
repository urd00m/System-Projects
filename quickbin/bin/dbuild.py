#!/usr/bin/env python 
# lbuild python file
import click
import os
from pathlib import Path
import sys

author = "Alan Wang"
username = "urd00m"

### .gitignore creation ###
def create_gitignore(name):
    f = open(f"{name}/.gitignore", "w")
    f.write("*.out\n*.o\n*.bin\n*.iso\n*.so\n*.swp\n*.gch\n*~\n.DS_Store\n*.dSYM")
    f.close()
### END


'''
    build a c project directory TOOD licenses
'''
def build_c_project(name):
    # build folders 
    os.system(f"mkdir {name}")
    os.system(f"mkdir {name}/includes")
    os.system(f"mkdir {name}/src")
    os.system(f"mkdir {name}/test")
    os.system(f"mkdir {name}/scripts")
    os.system(f"mkdir {name}/lib")

    # init git
    os.system(f"git init {name}/")

    # README creation
    f = open(f"{name}/README.md", "w")
    f.write(f"# {name}\n")
    f.write(f"\n\n#### by {author} github: {username}\n")
    f.close()

    # .gitignore creation
    create_gitignore(name) 

    # main.c creation
    f = open(f"{name}/src/main.c", "w")
    f.write(f"/*\n\tmain c file\n*/\n")
    f.write("#include <stdint.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n")
    f.write("int main(void) {\n\n\treturn 0;\n}\n")
    f.close()
            
    # Makefile creation
    f = open(f"{name}/Makefile", "w")
    f.write("CC=gcc\nCFLAGS=-Wall -g\nINC=./includes\nLIBS=-I$(INC) -L./lib\n\n")
    f.write("all: main.out\n\n")
    f.write("main.out: src/main.c\n")
    f.write("\t$(CC) $^ $(CFLAGS) $(LIBS) -o $@\n\n")
    f.write("clean:\n")
    f.write("\ttouch clean.o\n\ttouch clean.out\n\trm *.o\n\trm *.out\n")


'''
    build a cpp project directory TODO licenses
'''
def build_cpp_project(name):
    # build folders 
    os.system(f"mkdir {name}")
    os.system(f"mkdir {name}/includes")
    os.system(f"mkdir {name}/src")
    os.system(f"mkdir {name}/test")
    os.system(f"mkdir {name}/scripts")
    os.system(f"mkdir {name}/lib")

    # init git
    os.system(f"git init {name}/")

    # README creation
    f = open(f"{name}/README.md", "w")
    f.write(f"# {name}\n")
    f.write(f"\n\n#### by {author} github: {username}\n")
    f.close()

    # .gitignore creation
    create_gitignore(name) 

    # main.c creation
    f = open(f"{name}/src/main.cpp", "w")
    f.write(f"/*\n\tmain c file\n*/\n")
    f.write("#include <stdint.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\nusing namespace std;\n\n")
    f.write("int main(void) {\n\n\treturn 0;\n}\n")
    f.close()
            
    # Makefile creation
    f = open(f"{name}/Makefile", "w")
    f.write("CC=g++\nCFLAGS=-Wall -g\nINC=./includes\nLIBS=-I$(INC) -L./lib\n\n")
    f.write("all: main.out\n\n")
    f.write("main.out: src/main.cpp\n")
    f.write("\t$(CC) $^ $(CFLAGS) $(LIBS) -o $@\n\n")
    f.write("clean:\n")
    f.write("\ttouch clean.o\n\ttouch clean.out\n\trm *.o\n\trm *.out\n")


'''
    build Leetcode contest directory 
'''
def build_leet_project(name):
    # build contest items
    os.system(f"mkdir weekly{name}")
    os.system(f"touch weekly{name}/q1.cpp")
    os.system(f"touch weekly{name}/q2.cpp")
    os.system(f"touch weekly{name}/q3.cpp")
    os.system(f"touch weekly{name}/q4.cpp")

    # build README
    f = open(f"weekly{name}/README.md", "w")
    f.write(f"# Weekly{name} contest\n\n\n")
    f.write(f"\n\n#### by {author} github: {username}\n")
    f.close()
    
    
# Main Function
@click.command(short_help="directory builder for various project types")
@click.argument("project_name")
@click.argument("project_type")
def dbuild(project_name, project_type):
    '''Create a project with name {PROJECT_NAME} and of {PROJECT_TYPE}. Note for Leetcode contest directory, put weekly number (ex. 302) for {PROJECT_NAME}, weekly is automatically attached!

    Accept project types are c/cpp/py/leet
    '''
    project_type = project_type.strip() 
    if(project_type == "c"):
        build_c_project(project_name)
    elif(project_type == "cpp"):
        build_cpp_project(project_name)
    elif(project_type == "py"):
        pass
    elif(project_type == "leet"):
        build_leet_project(project_name) 
    else:
        click.echo("PROJECT TYPE NOT DEFINED, ONLY c/cpp/py/leet")
        sys.exit(1)

if __name__ == '__main__':
    dbuild()
