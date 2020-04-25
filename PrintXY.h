#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>

//Getting current console handle
HANDLE currentConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <class T>
void printXY(T output, int x, int y);

template <class T>
void printXY(T output, int x, int y, int tileWidth);

template<class T>
inline void printXY(T output, int x, int y)
{
	//Ensuring coordinates are valid.
	if (x >= 0 && y >= 0) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD originalCoordinates;
		COORD newCoordinates;

		GetConsoleScreenBufferInfo(currentConsole, &csbi);

		//Getting original cursor location.
		originalCoordinates.X = csbi.dwCursorPosition.X;
		originalCoordinates.Y = csbi.dwCursorPosition.Y;

		//Getting newCoordinates from parameters.
		newCoordinates.X = x;
		newCoordinates.Y = y;

		SetConsoleCursorPosition(currentConsole, newCoordinates);
		std::cout << output;
		SetConsoleCursorPosition(currentConsole, originalCoordinates);
	}
	else
	{
		std::cout << "Invalid coordinates." << std::endl;
	}
}

template<class T>
inline void printXY(T output, int x, int y, int tileWidth)
{
	//Ensuring coordinates are valid.
	if (x >= 0 && y >= 0) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD originalCoordinates;
		COORD newCoordinates;

		GetConsoleScreenBufferInfo(currentConsole, &csbi);

		//Getting original cursor location.
		originalCoordinates.X = csbi.dwCursorPosition.X;
		originalCoordinates.Y = csbi.dwCursorPosition.Y;

		//Getting newCoordinates from parameters.
		newCoordinates.X = x;
		newCoordinates.Y = y;

		SetConsoleCursorPosition(currentConsole, newCoordinates);
		std::cout << std::left << std::setw(tileWidth) << output;
		SetConsoleCursorPosition(currentConsole, originalCoordinates);
	}
	else
	{
		std::cout << "Invalid coordinates." << std::endl;
	}
}
