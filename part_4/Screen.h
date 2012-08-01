#include <ncurses.h>

#ifndef SCREEN_H
#define SCREEN_H

class Screen {
	int _height, _width;
public:
	// Initialize the ncurses library
	Screen();
	// Clear ncurses
	~Screen();
	// Print a message on the screen
	void add(const char *message);
	// Get the screen height and width
	int height();
	int width();
	// Don't wait for the user to press a key (non-blocking I/O)
	void zerodelay();
	// Wait for the user to press a key (blocking I/O this is the default when ncurses starts)
	void delay();	
};

#endif