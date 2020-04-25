#pragma once

class Puzzle
{
private:
	//Directional Constants
	const int UP = 1;
	const int DOWN = 2;
	const int LEFT = 3;
	const int RIGHT = 4;

	//Puzzle Size Constants
	int ROWS{ 0 };
	int COLS{ 0 };

	//Color Constants
	const int GREEN = 10;
	const int RED = 12;
	const int WHITE = 15;

	//Max puzzle size.
	int puzzle[5][5] = { 0 };

	// Set width of tiles
	int tileWidth = 5;

	// Number of moves to solve the puzzle
	int Moves{ 0 };

public:
	Puzzle();
	void setDimensions(int _side);
	void make();
	void print() const;
	void swap(int _ROW, int _COL, int _direction);
	bool slide();
	bool slide(int _direction);
	void shuffle();
	bool winCheck() const;
	void updateScreen(int r, int c) const;
	int checkTileLocation(int r, int c) const;
	int attempts();
	void write();
	void read() const;

	~Puzzle();
};

