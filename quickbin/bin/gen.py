#!/usr/bin/env python
import click
import sys 
import os
import json            			                                   
from pathlib import Path


@click.command(short_help="Easily generate programming files")
@click.argument("name")
@click.option("-g", "--cpp", "cpp", is_flag=True, help="c++ code") 
@click.option("-c", is_flag=True, help="c code")
@click.option("-p", "python", is_flag=True, help="python code")
@click.option("-j", "java", is_flag=True, help="java code")
@click.option("-o", "--other", "other", default=None, help="other code")
@click.option("--overwrite", is_flag=True, help="overwrite contents")
@click.option("-f", "--filler", is_flag=True, help="fill it up with code template")
@click.option("-e", "--emacs", is_flag=True, help="Also open emacs editor")
def gen(name, cpp, c, python, java, other, overwrite, filler, emacs):
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
            f.write("#include <stdint.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n")
            f.write("int main(void) {\n\n\treturn 0;\n}\n")

        f.close()

        # Open emacs
        if(emacs == True):
            os.system(f"emacs {name}.cpp")

            
    if(c == True): # TODO
        f = open(name+".c", "w")

        # Template check
        if(filler == True):
            f.write(f"/*\n\t{name} c file\n*/\n")
            f.write("#include <stdint.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n")
            f.write("int main(void) {\n\n\treturn 0;\n}\n")
        
        f.close()

        # Open emacs
        if(emacs == True):
            os.system(f"emacs {name}.c")

            
    if(python == True):
        f = open(name+".py", "w")

        # Template check
        if(filler == True):
            f.write(f"# {name} python file\n") # TODO MORE IMPORTS
            f.write("import time\nimport sys\nimport numpy as np\nimport sympy as sp\nimport matplotlib.pyplot as plt\n\n")
            f.write("# Main Function\ndef main():\n    pass\n\n")
            f.write("if __name__ == '__main__':\n    main()\n")

        f.close()

        # Open emacs
        if(emacs == True):
            os.system(f"emacs {name}.py")

            
    if(java == True): # TODO 
        f = open(name+".java", "w")

        # Template check
        if(filler == True):
            f.write(f"/*\n\t{name} java file\n*/\n")
            f.write("import java.io.*;\nimport java.util.*;\n\n")
            f.write("public class {%s} { \n"%(name,))
            f.write("\tpublic static void main(String args[]) throws IOException {\n")
            f.write("\t\t;\n")
            f.write("\t}\n")
            f.write("}\n")
            
        f.close()
        
        # Open emacs
        if(emacs == True):
            os.system(f"emacs {name}.java")

            
    if(other != None): # TODO 
        f = open(f"{name}.{other}", "w")
        f.close()
        
        # Open emacs
        if(emacs == True):
            os.system(f"emacs {name}.{other}")

if __name__ == '__main__':
    gen()
