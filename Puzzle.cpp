#include "Puzzle.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <string>
#include "PrintXY.h"
using namespace std;

Puzzle::Puzzle()
{
	cout << " Choose the puzzle size:" << endl;
	cout << " 1- (3X3)" << endl;
	cout << " 2- (4X4)" << endl;
	cout << " 3- (5X5)" << endl;
	cout << " 4- Scores" << endl;
	bool input{ true };
	while (input)
	{
		char ch = _getch();
		ch -= '0';    // converting char to int
		switch (ch)
		{
		case 1:
		case 2:
		case 3:
			setDimensions(ch+2);
			input = false;
			break;
		case 4:
			read();
			break;
		default:
			cout << "Wrong input!  ";
			break;
		}
	}
}

void Puzzle::setDimensions(int _side)
{
	cout << "This is setDImensions() function " << endl;
	this->ROWS = _side;
	this->COLS = _side;
}

void Puzzle::make()
{
	system("cls");
	int count{ 1 };
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			puzzle[r][c] = count;
			count++;
			if (r == ROWS - 1 && c == COLS - 1)
			{
				puzzle[r][c] = 0;
			}
		}
	}
}

void Puzzle::print() const
{
	system("cls");
	int count{ 1 };
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			// Set color
			if (checkTileLocation(r, c) == 1)
			{
				SetConsoleTextAttribute(currentConsole, GREEN);
			}
			else if (checkTileLocation(r, c) == -1)
			{
				SetConsoleTextAttribute(currentConsole, RED);
			}
			else
			{
				SetConsoleTextAttribute(currentConsole, WHITE);
			}
			
			// Print with selected color
			cout << left << setw(tileWidth) << puzzle[r][c];
		}
		cout << endl;
	}
	// Setting color and inserting number of moves below the puzzle 
	SetConsoleTextAttribute(currentConsole, WHITE);
	printXY("------------------------------", 0, ROWS);
	printXY("Moves: ", 0, ROWS+1);
}

void Puzzle::swap(int _ROW, int _COL, int _direction)
{
	int temp{ 0 };
	if (_direction == UP)
	{
		temp = puzzle[_ROW][_COL];
		puzzle[_ROW][_COL] = puzzle[_ROW - 1][_COL];
		puzzle[_ROW - 1][_COL] = temp;
	}
	else if (_direction == DOWN)
	{
		temp = puzzle[_ROW][_COL];
		puzzle[_ROW][_COL] = puzzle[_ROW + 1][_COL];
		puzzle[_ROW + 1][_COL] = temp;
	}
	else if (_direction == LEFT)
	{
		temp = puzzle[_ROW][_COL];
		puzzle[_ROW][_COL] = puzzle[_ROW][_COL - 1];
		puzzle[_ROW][_COL - 1] = temp;
	}
	else if (_direction == RIGHT)
	{
		temp = puzzle[_ROW][_COL];
		puzzle[_ROW][_COL] = puzzle[_ROW][_COL + 1];
		puzzle[_ROW][_COL + 1] = temp;
	}
}

bool Puzzle::slide()
{
	int zeroRow{ 0 };
	int zeroCol{ 0 };
	// finding the position of zero or * tile
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (puzzle[r][c] == 0) {
				zeroRow = r;
				zeroCol = c;
				break;
			}
		}
	}

	char userinput = _getch();

	switch (userinput)
	{
	case 'w':
	case 'W':
		if (zeroRow - 1 < 0)
		{
			return false;
		}
		swap(zeroRow, zeroCol, UP);
		updateScreen(zeroRow-1, zeroCol);
		updateScreen(zeroRow, zeroCol);
		break;

	case 's':
	case 'S':
		if (zeroRow + 1 >= ROWS)
		{
			return false;
		}
		swap(zeroRow, zeroCol, DOWN);
		updateScreen(zeroRow + 1, zeroCol);
		updateScreen(zeroRow, zeroCol);
		break;

	case 'a':
	case 'A':
		if (zeroCol - 1 < 0)
		{
			return false;
		}
		swap(zeroRow, zeroCol, LEFT);
		updateScreen(zeroRow, zeroCol - 1);
		updateScreen(zeroRow, zeroCol);
		break;

	case 'd':
	case 'D':
		if (zeroCol + 1 >= COLS)
		{
			return false;
		}
		swap(zeroRow, zeroCol, RIGHT);
		updateScreen(zeroRow, zeroCol + 1);
		updateScreen(zeroRow, zeroCol);
		break;

	default:
		printXY("wrong input", 0, ROWS + 2);
		//cerr << "wrong input" << endl;
		return false;
	}
	Moves++;
	printXY(attempts(), 8, ROWS+1);
	return true;
}

bool Puzzle::slide(int _direction)
{
	// This gets direction as integer and is used for shuffling the tiles
	int zeroRow{ 0 };
	int zeroCol{ 0 };

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (puzzle[r][c] == 0) {
				zeroRow = r;
				zeroCol = c;
				break;
			}
		}
	}
	
	switch (_direction)
	{
	case 1:
		if (zeroRow - 1 < 0)
		{
			return false;
		}
		swap(zeroRow, zeroCol, UP);
		break;

	case 2:
		if (zeroRow + 1 >= ROWS)
		{
			return false;
		}
		swap(zeroRow, zeroCol, DOWN);
		break;

	case 3:
		if (zeroCol - 1 < 0)
		{
			return false;
		}
		swap(zeroRow, zeroCol, LEFT);
		break;

	case 4:
		if (zeroCol + 1 >= COLS)
		{
			return false;
		}
		swap(zeroRow, zeroCol, RIGHT);
		break;

	default:
		cout << "wrong input" << endl;
		return false;
	}

	return true;
}

void Puzzle::shuffle()
{
	int direction;
	int counter = 1;

	srand(time(NULL));

	while (counter <= 10000) {
		direction = rand() % 4 + 1;
		// If slide in the direction is valid counter goes up
		if (slide(direction)) {
			counter++;
		}
	}
}

bool Puzzle::winCheck() const
{
	int counter = 1;
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (puzzle[r][c] != counter)
			{
				if (r == ROWS-1 && c == COLS-1 && puzzle[r][c] == 0)
				{
					cout << "------  Solved  -----" << endl;
					return true;
				}
				return false;
			}
			counter++;
		}
	}
}

void Puzzle::updateScreen(int r, int c) const
{
	// Set color
	if (checkTileLocation(r, c) == 1) {
		SetConsoleTextAttribute(currentConsole, GREEN); // the tile is in correct location
	}
	else if (checkTileLocation(r, c) == -1)
	{
		SetConsoleTextAttribute(currentConsole, RED);  // the tile is not in the correct location
	}

	// Print with the selected color
	if (puzzle[r][c] != 0) {
		printXY(puzzle[r][c], c*tileWidth, r, tileWidth);  // the specific movement (change) in the array will be printed
	}
	else
	{
		printXY("*", c*tileWidth, r, tileWidth);
	}

	SetConsoleTextAttribute(currentConsole, WHITE);
}

int Puzzle::checkTileLocation(int r, int c) const
{
	//If tile is a blank space, return 0.
	if (puzzle[r][c] == 0) {
		return 0;
	}

	//If tile is in its correct location, return 1.
	else if (puzzle[r][c] == ((r * COLS) + (c + 1))) {
		return 1;
	}

	//If tile is in incorrect location, return -1.
	else {
		return -1;
	}
	return 0;
}

int Puzzle::attempts()
{
	return Moves;
}

void Puzzle::write()
{
	ofstream ofile("records.txt", ios_base::app);
	if (ofile.is_open())
	{
		cout << "Please, insert your name :" << endl;
		string name;
		getline(cin, name);
		ofile << name << " score is : " << attempts() << endl;

	}
	else
	{
	cerr << " Could not open file" << endl;
	}
}

void Puzzle::read() const
{
	ifstream ifile("records.txt");
	if (ifile.is_open())
	{
		while (!ifile.eof())
		{
			cout << "------------------------------" << endl;
			string name;
			getline(ifile, name);
			cout << name << endl;
		}
	}
	else
	{
		cerr << " Could not open file" << endl;
	}
}

Puzzle::~Puzzle()
{
}
