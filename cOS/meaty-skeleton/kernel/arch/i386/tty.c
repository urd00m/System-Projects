#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	// newline check
        if(c == '\n') { //new line support
                terminal_row++;
                terminal_column = 0;
                return;
        }
        
        //update entry 
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void buffer_scroll() {
        size_t j = 0; 
        for(size_t i = VGA_WIDTH; i < VGA_HEIGHT*VGA_WIDTH; i++) {
                terminal_buffer[j] = terminal_buffer[i];
                j++;
        }
        for(; j < VGA_HEIGHT*VGA_WIDTH; j++) {
                terminal_buffer[j] = vga_entry(' ', VGA_COLOR_GREEN); 
        }
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (uc != '\n' && ++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}
	
	//check for scrolling
        if(terminal_row == VGA_HEIGHT) {
                //shift buffer up by one
                buffer_scroll();
                terminal_row--;
        }
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
