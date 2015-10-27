#include "SudokuPuzzle.h"

int main()
{
	SudokuPuzzle testPuzzle = SudokuPuzzle();
	testPuzzle.convertStringToPuzzle("000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000 000000000");
	testPuzzle.printPuzzle();
	testPuzzle.setCell(0,0,1);
	std::cout << testPuzzle.getCell(0, 0) << std::endl;
	std::cout << testPuzzle.getBox(4, 2) << std::endl;
	std::cout << std::endl;
	//Setign all cell values to their box value
	for (int row = 0; row < 9; row++){
		for (int column = 0; column < 9; column++)
		{
			testPuzzle.setCell(row, column, testPuzzle.getBox(row, column));
		}
	}
	testPuzzle.printPuzzle();
	std::cout << std::endl;
	//Setting all cell values to the value returned by getBoxTopRow
	for (int row = 0; row < 9; row++){
		for (int column = 0; column < 9; column++)
		{
			testPuzzle.setCell(row, column, testPuzzle.getBoxTopRow(row, column));
		}
	}
	testPuzzle.printPuzzle();
	std::cout << std::endl;
	//Setting all cell values to the value returned by getBoxLeftColumn
	for (int row = 0; row < 9; row++){
		for (int column = 0; column < 9; column++)
		{
			testPuzzle.setCell(row, column, testPuzzle.getBoxLeftColumn(row, column));
		}
	}
	testPuzzle.printPuzzle();
}
