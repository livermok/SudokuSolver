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

/*
Looks for boxes where a number has multiple possible locations but 
these locations are unique to either a row or column thereby implying
that that value may not occur else where in that row or column respectively.
*/
void SudokuSolver::updateTruthsImplicit()
{
	for (int box = 0; box < 9; box++)
	{
		for (int number = 1; number <= 9; number++)
		{
			//Looks for unique Row
			int rowPossibilities = 0;
			int implicitRow = 0;
			for (int row = getBoxTopRow(box); row < getBoxTopRow(box) + 3; row++)
			{
				int presenceInRow = 0;
				for (int column = getBoxLeftColumn(box); column < getBoxLeftColumn(box) + 3; column++)
				{
					if (puzzleTruthTable[row][column][number] == true)
						presenceInRow++;
				}
				if (presenceInRow > 0){
					rowPossibilities++;
					implicitRow = row;
				}
			}
			if (rowPossibilities == 1)
			{
				//Removes possibilities in row left of the box
				for (int i = 0; i < getBoxLeftColumn(box); i++)
				{
					puzzleTruthTable[implicitRow][i][number] = false;
				}
				//Removes possibilities in row right of the box
				for (int i = getBoxLeftColumn(box) + 3; i < 9; i++)
				{
					puzzleTruthTable[implicitRow][i][number] = false;
				}
			}
			
			//Looks for unique columns
			int columnPossibilities = 0;
			int implicitColumn = 0;
			for (int column = getBoxLeftColumn(box); column < getBoxLeftColumn(box) + 3; column++)
			{
				
				int presenceInColumn = 0;
				for (int row = getBoxTopRow(box); row < getBoxTopRow(box) + 3; row++)
				{
					if (puzzleTruthTable[row][column][number] == true)
						presenceInColumn++;
				}
				if (presenceInColumn > 0){
					columnPossibilities++;
					implicitColumn = column;
				}
			}
			if (columnPossibilities == 1)
			{
				//Removes possibilities in column above the box
				for (int i = 0; i < getBoxTopRow(box); i++)
				{
					puzzleTruthTable[i][implicitColumn][number] = false;
				}
				//Removes possibilities in column below the box
				for (int i = getBoxTopRow(box) + 3; i < 9; i++)
				{
					puzzleTruthTable[i][implicitColumn][number] = false;
				}
			}
		}
	}
}

//Place holder for more complicated logical conclusions if found
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
						cellsSolved++;
					}
				}
			}
		}
	}
	return cellsSolved;
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
