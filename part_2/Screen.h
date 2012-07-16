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
};

#endif