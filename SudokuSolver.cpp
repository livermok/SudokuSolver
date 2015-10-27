#include "SudokuSolver.h"


SudokuSolver::SudokuSolver()
{
}

//Simple Logic Cluster
void SudokuSolver::updateTruthsSimple()
{
}

int SudokuSolver::solveSimpleUniqueInRow()
{
	return 1;
}

int SudokuSolver::solveSimpleUniqueInColumn()
{
	return 1;
}

int SudokuSolver::solveSimpleUniqueInBox()
{
	return 1;
}

//Complex Logic Cluster
void SudokuSolver::updateTruthsImplicit()
{
}

void SudokuSolver::updateTruths()
{
}

int SudokuSolver::solveUniqueCellValue()
{
	return 1;
}

//Logical Jump
SudokuSolver SudokuSolver::guessOneCell()
{
	SudokuSolver temp;
	return temp;
}

SudokuSolver::~SudokuSolver()
{
}
