#pragma once

#include "SudokuPuzzle.h"

class SudokuSolver : public SudokuPuzzle
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
	void updateTruthsComplex();
	int solveUniqueCellValue();
	
	//Logical Jump
	SudokuSolver guessOneCell();

	//Print tables
	void printTruthTableLayer(int number);

	~SudokuSolver();
};

