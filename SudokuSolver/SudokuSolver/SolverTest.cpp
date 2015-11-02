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
	

	//Test for unique cell value
	SudokuSolver testPuzzle2 = SudokuSolver();
	testPuzzle2.convertStringToPuzzle("000010000 000020000 000030000 000000000 456000790 000000000 000000000 000000000 000000000");
	testPuzzle2.printPuzzle();
	std::cout << std::endl;
	testPuzzle2.updateTruthsSimple();
	testPuzzle2.solveUniqueCellValue();
	testPuzzle2.printPuzzle();
	std::cout << std::endl;

	//Test Implicit truth function
	SudokuSolver testPuzzle3 = SudokuSolver();
	testPuzzle3.convertStringToPuzzle("004000000 003000000 002000000 010000000 000000000 000000000 000000000 000000000 000000000");
	testPuzzle3.printPuzzle();
	std::cout << std::endl;
	testPuzzle3.updateTruthsSimple();
	testPuzzle3.printTruthTableLayer(1);
	std::cout << std::endl;
	testPuzzle3.updateTruthsImplicit();
	testPuzzle3.printTruthTableLayer(1);

	SudokuSolver testPuzzle4 = SudokuSolver();
	testPuzzle4.convertStringToPuzzle("400800002 000002400 706000180 000580030 008000900 050037000 037000501 004600000 800005007");
	testPuzzle4.printPuzzle();
	testPuzzle4.updateTruthsSimple();
	do{
		cellsSolved = 0;
		cellsSolved += testPuzzle4.solveSimpleUniqueInBox();
		cellsSolved += testPuzzle4.solveSimpleUniqueInRow();
		cellsSolved += testPuzzle4.solveSimpleUniqueInColumn();
		std::cout << cellsSolved << std::endl;
	} while (cellsSolved > 0);
	testPuzzle4.printPuzzle();

	do{
		testPuzzle4.updateTruthsImplicit();
		testPuzzle4.solveUniqueCellValue();
		cellsSolved = 0;
		cellsSolved += testPuzzle4.solveSimpleUniqueInBox();
		cellsSolved += testPuzzle4.solveSimpleUniqueInRow();
		cellsSolved += testPuzzle4.solveSimpleUniqueInColumn();
		std::cout << cellsSolved << std::endl;
	} while (cellsSolved > 0);
	testPuzzle4.printPuzzle();
}
