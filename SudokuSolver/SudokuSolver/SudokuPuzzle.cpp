#include "SudokuPuzzle.h"
#include <stdlib.h>
#include <string>

SudokuPuzzle::SudokuPuzzle()
{
	convertStringToPuzzle("000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000");
}

void SudokuPuzzle::convertStringToPuzzle(std::string puzzleAsString)
{
	assert(puzzleAsString.length() > 81);
	int charIndex = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			while (charIndex < puzzleAsString.length() && !(puzzleAsString.at(charIndex) >= '0' && puzzleAsString.at(charIndex) <= '9'))
			{
				charIndex++;
			}
			if (puzzleAsString.at(charIndex) >= '0' &&
				puzzleAsString.at(charIndex) <= '9')
			{
				puzzle[row][column] = puzzleAsString.at(charIndex) - '0';
				charIndex++;
			}
			else
				exit(0);
		}
	}
}

void SudokuPuzzle::printPuzzle()
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			std::cout << puzzle[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

bool SudokuPuzzle::setCell(int row, int column, int val)
{
	assert(val >= 0 && val <= 9);
	assert(row >= 0 && row < 9);
	assert(column >= 0 && column < 9);
	if (puzzle[row][column] >= 0 && puzzle[row][column] <= 9){
		puzzle[row][column] = val;
		return true;
	}
	else
		return false;
	
}

int SudokuPuzzle::getCell(int row, int column)
{
	return puzzle[row][column];
}

int SudokuPuzzle::getBox(int row, int column)
{
	return column / 3 + 3 * (row / 3);
}

int SudokuPuzzle::getBoxTopRow(int row, int column)
{
	return getBoxTopRow(getBox(row, column));
}

int SudokuPuzzle::getBoxTopRow(int box)
{
	switch (box)
	{
	case 0:
		return 0;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 3;
		break;
	case 6:
		return 6;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return 6;
		break;
	default:
		return -1;
	}
}

int SudokuPuzzle::getBoxLeftColumn(int row, int column)
{
	return getBoxLeftColumn(getBox(row, column));
}

int SudokuPuzzle::getBoxLeftColumn(int box)
{
	switch (box)
	{
	case 0:
		return 0;
		break;
	case 1:
		return 3;
		break;
	case 2:
		return 6;
		break;
	case 3:
		return 0;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 6;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 3;
		break;
	case 8:
		return 6;
		break;
	default:
		return -1;
	}
}

SudokuPuzzle::~SudokuPuzzle()
{
}
