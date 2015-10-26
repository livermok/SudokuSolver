#pragma once

#include "SudokuPuzzle.h"

class SudokuSolver : public SudokuSolver
{
protected:
	bool puzzleTruthTable[9][9][10];
public:
	SudokuSolver();

	//Simple Logic Cluster
	void updateTruthsSimple();
	int solveSimpleUniqueInRow();
	int solveSimpleUniqueInColumn();
	int solveSimpleUniqueInBox();
	
	//Complex Logic Cluster
	void updateTruthsImplicit();
	void updateTruths();
	int solveUniqueCellValue();
	
	//Logical Jump
	SudokuSolver guessOneCell();

	~SudokuSolver();
};

