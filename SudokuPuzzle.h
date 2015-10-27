#pragma once

#include <string>
#include <iostream>
#include <assert.h>

class SudokuPuzzle
{
protected:
	int puzzle[9][9];
public:
	SudokuPuzzle();

	void convertStringToPuzzle(std::string);
	void printPuzzle();
	bool setCell(int row, int column, int val);
	int getCell(int row, int column);
	int getBox(int row, int column);
	int getBoxTopRow(int row, int column);
	int getBoxTopRow(int box);
	int getBoxLeftColumn(int row, int column);
	int getBoxLeftColumn(int box);

	~SudokuPuzzle();
};

