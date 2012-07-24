#include "Character.h"

// Create a character
Character::Character(char symbol, int row_0, int col_0) {
	_symbol = symbol;
	_row = row_0;
	_col = col_0;
}

// Change the character position
void Character::pos(int row_0, int col_0) {
	_row = row_0;
	_col = col_0;
}

// Get character's row (y) position
int Character::row() {
	return _row;
}

// Get character's row (x) position
int Character::col() {
	return _col;
}

// Get the symbol of the character
char Character::symbol() {
	return _symbol;
}
