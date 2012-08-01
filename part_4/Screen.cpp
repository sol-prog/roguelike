#include "Screen.h"

// Initialize the ncurses library
Screen::Screen() {
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	// Aquire the screen dimensions
	getmaxyx(stdscr, _height, _width);
}

// Clear ncurses
Screen::~Screen() {
	endwin();
}

// Print a message on the screen
void Screen::add(const char *message) {
	printw(message);
}

// Get the screen height
int Screen::height() {
	return _height;
}

// Get the screen width
int Screen::width() {
	return _width;
}

// Don't wait for the user to press a key
void Screen::zerodelay() {
	nodelay(stdscr, TRUE);
}

// Wait for the user to press a key (this is the default when ncurses starts)
void Screen::delay() {
	nodelay(stdscr, FALSE);
}