#include <ncurses.h>

#include "Screen.h"
#include "Frame.h"
#include "Character.h"

void game_loop(Frame &game_map, Frame &viewport, Character &main_char, int ch) {
	// Check if the user wishes to play the game
	if(ch == 'q' || ch =='Q') return;

	// Show the main character on the screen
	game_map.add(main_char);
	viewport.center(main_char);
	viewport.refresh();

	while(1) {
		ch = getch();

		// Main character movements
		if(ch == KEY_LEFT) {
			game_map.add(main_char, main_char.row(), main_char.col() - 1);
			viewport.center(main_char);
			viewport.refresh();
		}
		else if(ch == KEY_RIGHT) {
			game_map.add(main_char, main_char.row(), main_char.col() + 1);
			viewport.center(main_char);
			viewport.refresh();
		}
		else if(ch == KEY_UP) {
			game_map.add(main_char, main_char.row() - 1, main_char.col());
			viewport.center(main_char);
			viewport.refresh();
		}
		else if(ch == KEY_DOWN) {
			game_map.add(main_char, main_char.row() + 1, main_char.col());
			viewport.center(main_char);
			viewport.refresh();
		}
		else if(ch == 'q' || ch == 'Q') {
			break;
		}
	}
}


// Entry function for game
int main() {

	// Initialize ncurses
	Screen scr;

	// Print a welcome message on screen
	scr.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");

	// Wait until the user press a key
	int ch = getch();

	// Create an ncurses window to store the game map. This will be twice the size
	// of the screen and it will be positioned at (0,0) in screen coordinates
	Frame game_map(2*scr.height(), 2*scr.width(), 0, 0);

	// Create an ncurses subwindow of the game map. This will have the size 
	// of the user screen and it will be initially postioned at (0, 0)
	Frame viewport(game_map, scr.height(), scr.width(), 0, 0);

	// Initialize the main character. We are going to put this in the middle of 
	// the game map (for now)
	Character main_char('@', game_map.height()/2, game_map.width()/2);

	// Fill the game map with lakes, planes, mountains and snow using a Perlin noise function
	game_map.gen_Perlin(237);

	// Start the game loop
	game_loop(game_map, viewport, main_char, ch);

	return 0;
}
