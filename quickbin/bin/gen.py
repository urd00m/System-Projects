#!/usr/bin/env python
import click
import sys 
import os
import json            			                                   
from pathlib import Path

@click.command(short_help="Easily generate programming files")
@click.argument("name")
@click.option("--cpp", "cpp", is_flag=True, help="c++ code") 
@click.option("-c", is_flag=True, help="c code")
@click.option("-p", "python", is_flag=True, help="python code")
@click.option("-j", "java", is_flag=True, help="java code")
@click.option("-o", "--other", "other", default=None, help="other code")
@click.option("--overwrite", is_flag=True, help="overwrite contents")
@click.option("-f", "--filler", is_flag=True, help="fill it up with code template")
def gen(name, cpp, c, python, java, other, overwrite, filler):
    # overwite check
    if(overwrite == False):
        error = False
        if(cpp == True and os.path.exists("./"+name+".cpp")):
            error = True
        elif(c == True and os.path.exists("./"+name+".c")):
             error = True
        elif(python == True and os.path.exists("./"+name+".py")):
            error = True
        elif(java == True and os.path.exists("./"+name+".java")):
            error = True
        elif(other != None and os.path.exists(f"./{name}.{other}")):
            error = True

        # Check error 
        if error == True:
            click.echo("ERROR FILE ALREADY EXISTS! Add --overwrite if you wish to overwrite the file(s)")
            sys.exit(1)
       
    # Build files 
    if(cpp == True):  
        f = open(name+".cpp", "w")

        # Template check
        if(filler == True):
            f.write(f"/*\n\t{name} cpp file\n*/\n")
            f.write("#include <stdio.h>\n") # TODO MAYBE MORE
            f.write("int main(void) {\n\n\treturn 0;\n}\n")

        f.close()
    if(c == True): # TODO
        pass
    if(python == True):
        f = open(name+".py", "w")

        # Template check
        if(filler == True):
            f.write(f"# {name} python file\n") # TODO MORE IMPORTS
            f.write("import time\nimport sys\nimport numpy as np\nimport sympy as sp\nimport matplotlib.pyplot as plt\n\n")
            f.write("# Main Function\ndef main():\n    pass\n\n")
            f.write("if __name__ == '__main__':\n    main()\n")

        f.close()
    if(java == True): # TODO 
        pass
    if(other != None): # TODO 
        pass 

if __name__ == '__main__':
    gen()
