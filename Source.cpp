#include <iostream>
#include <Windows.h>
#include "Puzzle.h"
//#include "PrintXY.h"
using namespace std;

int main()
{
	Puzzle puzzle;
	puzzle.make();
	puzzle.shuffle();
	puzzle.print();

	while (!puzzle.winCheck())
	{
		puzzle.slide();
	}
	puzzle.write();
	
	return 0;
}