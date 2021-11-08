# cOS 
 
Basic OS to learn more about OS developement. Tutorial is followed from OS DEV here: https://wiki.osdev.org/Creating_an_Operating_System

## SimpleOS
This is a basic OS that can boot and has all the skeleton set up for the OS. This OS can only display characters on the screen with a VGA
text mode buffer. The implemenation that comes with the OS Dev Wiki doesn't come with new line support and doesn't come with scrolling 
features. The current implementation that exists in the simpleOS directory has both implemented now. It can boot and demonstrate text 
begin displayed on the screen with newlines and scrolling.  
Features:  
* Boot process 
* Stack setup 
* Basic skeleton 
* VGA text buffer 
* Text being displayed 
* Text scrolling
* New line support
 

#### Usage
**Building:**
1. `make all` to compile 
2. `make check` to check your iso file format
3. `make test` to test and see the file run 

**Make Clean:**
`make clean` will remove all object, bin, and iso files. 

