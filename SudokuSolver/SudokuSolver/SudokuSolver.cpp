#include "SudokuSolver.h"
#include "iostream"

SudokuSolver::SudokuSolver()
{
	
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			for (int number = 1; number <= 9; number++)
			{
				puzzleTruthTable[row][column][number] = true;
			}
		}
	}
}

//Simple Logic Cluster
void SudokuSolver::updateTruthsSimple()
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			if (puzzle[row][column] >= 1 && puzzle[row][column] <= 9)
			{
				int cellValue = puzzle[row][column];
				//Eliminate as possibility for row and column and all other in cell
				for (int i = 0; i < 9; i++)
				{
					puzzleTruthTable[row][i][cellValue] = false;
					puzzleTruthTable[i][column][cellValue] = false;
					puzzleTruthTable[row][column][ i +1 ] = false;
				}
				//Eliminae as a possibility for the box
				for (int i = getBoxTopRow(row, column);
					i < getBoxTopRow(row, column) + 3; i++)
				{
					for (int j = getBoxLeftColumn(row, column); 
						j < getBoxLeftColumn(row, column) + 3; j++)
					{
						puzzleTruthTable[i][j][cellValue] = false;
					}
				}
			}
		}
	}
}


int SudokuSolver::solveSimpleUniqueInRow()
{
	int cellsSolved = 0;
	for (int number = 1; number <= 9; number++)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				if (puzzleTruthTable[row][column][number])
				{
					int count = 0;
					for (int i = 0; i < 9; i++)
					{
						if (puzzleTruthTable[row][i][number])
						{
							count++;
						}
					}
					if (count == 1)
					{
						puzzle[row][column] = number;
						updateTruthsSimple();
						cellsSolved++;
					}
				}
			}
		}
	}
	return cellsSolved;
}

int SudokuSolver::solveSimpleUniqueInColumn()
{
	int cellsSolved = 0;
	for (int number = 1; number <= 9; number++)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				if (puzzleTruthTable[row][column][number])
				{
					int count = 0;
					for (int i = 0; i < 9; i++)
					{
						if (puzzleTruthTable[i][column][number])
						{
							count++;
						}
					}
					if (count == 1)
					{
						puzzle[row][column] = number;
						updateTruthsSimple();
						cellsSolved++;
					}
				}
			}
		}
	}
	return cellsSolved;
}

int SudokuSolver::solveSimpleUniqueInBox()
{
	int cellsSolved = 0;
	for (int number = 1; number <= 9; number++)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				if (puzzleTruthTable[row][column][number])
				{
					int count = 0;
					for (int i = getBoxTopRow(row, column); i < getBoxTopRow(row, column) + 3; i++)
					{
						for (int j = getBoxLeftColumn(row, column); j < getBoxLeftColumn(row, column) + 3; j++)
						{
							if (puzzleTruthTable[i][j][number])
							{
								count++;
							}
						}
					}
					if (count == 1)
					{
						puzzle[row][column] = number;
						updateTruthsSimple();
						cellsSolved++;
					}
				}
			}
		}
	}
	return cellsSolved;
}

//Complex Logic Cluster
void SudokuSolver::updateTruthsImplicit()
{
}

void SudokuSolver::updateTruthsComplex()
{
}

int SudokuSolver::solveUniqueCellValue()
{
	int cellsSolved = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			int count = 0;
			for (int number = 1; number <= 9; number++)
			{
				if (puzzleTruthTable[row][column][number])
					count++;
			}
			if (count == 1){
				for (int number = 1; number <= 9; number++)
				{
					if (puzzleTruthTable[row][column][number])
					{
						puzzle[row][column] = number;
						updateTruthsSimple();
					}
				}
			}
		}
	}
	return 1;
}

//Logical Jump
SudokuSolver SudokuSolver::guessOneCell()
{
	SudokuSolver temp;
	return temp;
}

void SudokuSolver::printTruthTableLayer(int number)
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			if (puzzleTruthTable[row][column][number])
				std::cout << number << " ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
}

SudokuSolver::~SudokuSolver()
{
}
