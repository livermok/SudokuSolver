#include "SudokuSolver.h"
#include "SudokuPuzzle.h"

int main()
{
	SudokuSolver testPuzzle = SudokuSolver();
	testPuzzle.convertStringToPuzzle("001000000 000000000 000000000 010000000 000000000 000000000 000100000 000000100 000000000");
	testPuzzle.printPuzzle();
	testPuzzle.printTruthTableLayer(1);
	testPuzzle.updateTruthsSimple();
	testPuzzle.printTruthTableLayer(1);
}
