#include "SudokuSolver.h"
#include "SudokuPuzzle.h"
#include <iostream>

int main()
{
	SudokuSolver testPuzzle = SudokuSolver();
	testPuzzle.convertStringToPuzzle("000000008 050497600 060002500 100900407 070000060 506004003 004300090 003215080 700000000");
	testPuzzle.printPuzzle();
	std::cout << std::endl;
	testPuzzle.updateTruthsSimple();
	testPuzzle.printTruthTableLayer(1);
	std::cout << std::endl;
	int cellsSolved;
	do{
		cellsSolved = 0;
		cellsSolved += testPuzzle.solveSimpleUniqueInBox();
		cellsSolved += testPuzzle.solveSimpleUniqueInRow();
		cellsSolved += testPuzzle.solveSimpleUniqueInColumn();
		std::cout << cellsSolved << std::endl;
	} while (cellsSolved > 0);

	std::cout << std::endl;
	testPuzzle.printPuzzle();
	std::cout << std::endl;
	testPuzzle.printTruthTableLayer(9);
}
