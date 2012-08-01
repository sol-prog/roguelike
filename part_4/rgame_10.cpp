#include <ncurses.h>

#include "Screen.h"
#include "Frame.h"
#include "Character.h"
#include <cmath>

void game_loop(Frame &game_map, Frame &viewport, Character &main_char, int ch, Character &monster) {
	// Check if the user wishes to play the game
	if(ch == 'q' || ch =='Q') return;

	// Add the monsters to the game_map
	game_map.add(monster);

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

		// Other characters movements
		// Try to move left
		int pos = -1, score = game_map.height()*game_map.height() + game_map.width()*game_map.width(), dist = -1;
		if( game_map.target_position(monster.row(), monster.col() - 1)) {
			dist = std::pow(main_char.row() - monster.row(),2) + std::pow(main_char.col() - (monster.col() - 1),2);
			if(score > dist) {
				score = dist;
				pos = 0;
			}
		}
		// Try to move right
		if( game_map.target_position(monster.row(), monster.col() + 1)) {
			dist = std::pow(main_char.row() - monster.row(),2) + std::pow(main_char.col() - (monster.col() + 1),2);
			if(score > dist) {
				score = dist;
				pos = 1;
			}
		}
		// Try to move up
		if( game_map.target_position(monster.row() - 1, monster.col())) {
			dist = std::pow(main_char.row() - (monster.row() - 1),2) + std::pow(main_char.col() - monster.col(),2);
			if(score > dist) {
				score = dist;
				pos = 2;
			}
		}
		// Try to move down
		if( game_map.target_position(monster.row() + 1, monster.col())) {
			dist = std::pow(main_char.row() - (monster.row() + 1),2) + std::pow(main_char.col() - monster.col(),2);
			if(score > dist) {
				score = dist;
				pos = 3;
			}
		}

		switch(pos) {
			case 0:
				game_map.add(monster, monster.row(), monster.col() - 1);
				break;
			case 1:
				game_map.add(monster, monster.row(), monster.col() + 1);
				break;
			case 2:
				game_map.add(monster, monster.row() - 1, monster.col());
				break;
			case 3:
				game_map.add(monster, monster.row() + 1, monster.col());
				break;
		}
		viewport.center(main_char);
		viewport.refresh();
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

	// Add a dummy monster to the game (we start with a hard coded monster position 
	// relative to the main character position)
	Character monster('M', main_char.row() + 7, main_char.col() + 22);

	// Fill the game map with lakes, planes, mountains and snow using a Perlin noise function
	game_map.gen_Perlin(237);

	// Start the game loop
	game_loop(game_map, viewport, main_char, ch, monster);

	return 0;
}
