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

/*
Looks for two cells in the same row, column or box (elements) where either 
the only possible location for a pair of numbers is a pair of cells
or the only possible solution to a pair of cells is a pair of values
*/
void SudokuSolver::updateTruthsPair()
{
	//Search for only possible locations
	//If only in one element then eliminate other possibilities from the cell
	//If in two elements eliminate from non-deliminating element as well
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			for (int number = 1; number < 10; number++)
			{
				if (puzzleTruthTable[row][column][number])
				{
					int inRow = 0;
					int inColumn = 0;
					int inBox = 0;
					for (int i = 0; i < 9; i++)
					{
						if (puzzleTruthTable[i][column][number])
						{
							inRow++;
						}
						if (puzzleTruthTable[row][i][number])
						{
							inColumn++;
						}
					}
					for (int j = getBoxTopRow(row, column); j < getBoxTopRow(row, column) + 3; j++)
					{
						for (int k = getBoxLeftColumn(row, column); k < getBoxLeftColumn(row, column) + 3; k++)
						{
							if (puzzleTruthTable[j][k][number])
							{
								inBox++;
							}
						}
					}
					//Pair discriminated by box
					if (inBox == 2)
					{
						int pairRow = 0;
						int pairColumn = 0;
						int numberCount = 0;
						for (int m = number + 1; m < 10; m++)
						{
							numberCount = 0;
							if (puzzleTruthTable[row][column][m])
							{
								for (int j = getBoxTopRow(row, column); j < getBoxTopRow(row, column) + 3; j++)
								{
									for (int k = getBoxLeftColumn(row, column); k < getBoxLeftColumn(row, column) + 3; k++)
									{
										if (puzzleTruthTable[j][k][m])
										{
											numberCount++;
											pairRow = j;
											pairColumn = k;
										}
									}
								}
								//Qualifies as a pair
								if (numberCount == 2 && puzzleTruthTable[pairRow][pairColumn][number])
								{
									for (int z = 1; z < 10; z++)
									{
										puzzleTruthTable[row][column][z] = false;
										puzzleTruthTable[pairRow][pairColumn][z] = false;
									}
									puzzleTruthTable[row][column][number] = true;
									puzzleTruthTable[pairRow][pairColumn][number] = true;
									puzzleTruthTable[row][column][m] = true;
									puzzleTruthTable[pairRow][pairColumn][m] = true;

									//check if in two elements
									if (pairRow == row)
									{
										for (int z = 0; z < getBoxLeftColumn(row, column); z++)
										{
											puzzleTruthTable[row][z][number] = false;
											puzzleTruthTable[row][z][m] = false;
										}
										for (int z = getBoxLeftColumn(row, column) + 3; z < 9; z++)
										{
											puzzleTruthTable[row][z][number] = false;
											puzzleTruthTable[row][z][m] = false;
										}
									}
									else if (pairColumn == column)
									{
										for (int z = 0; z < getBoxTopRow(row, column) + 3; z++)
										{
											puzzleTruthTable[z][column][number] = false;
											puzzleTruthTable[z][column][m] = false;
										}
										for (int z = getBoxTopRow(row, column) + 3; z < 9; z++)
										{
											puzzleTruthTable[z][column][number] = false;
											puzzleTruthTable[z][column][m] = false;
										}
									}
								}
							}
						}
					}

					//Pair discriminated by row 
					if (inRow == 2)
					{
						int pairColumn = 0;
						int numberCount = 0;
						for (int m = number + 1; m < 10; m++)
						{
							numberCount = 0;
							if (puzzleTruthTable[row][column][m])
							{
								for (int j = 0; j < 9; j++)
								{
									if (puzzleTruthTable[row][j][number])
									{
										numberCount++;
										pairColumn = j;
									}
								}
								//Qualifies as a pair
								if (numberCount == 2 && puzzleTruthTable[row][pairColumn][number])
								{
									for (int z = 1; z < 10; z++)
									{
										puzzleTruthTable[row][column][z] = false;
										puzzleTruthTable[row][pairColumn][z] = false;
									}
									//check if in two elements
									if (getBox(row, column) == getBox(row, pairColumn))
									{
										for (int x = getBoxTopRow(row, column); x < getBoxTopRow(row, column) + 3; x++)
										{
											for (int z = getBoxLeftColumn(row, column); z < getBoxLeftColumn(row, column) + 3; z++)
											{
												puzzleTruthTable[x][z][number] = false;
												puzzleTruthTable[x][z][m] = false;
											}
										}
									}
									puzzleTruthTable[row][column][number] = true;
									puzzleTruthTable[row][pairColumn][number] = true;
									puzzleTruthTable[row][column][m] = true;
									puzzleTruthTable[row][pairColumn][m] = true;
								}
							}

						}
					}

					//Pair discriminated by column
					if (inColumn == 2)
					{
						int pairRow = 0;
						int numberCount = 0;
						for (int m = number + 1; m < 10; m++)
						{
							numberCount = 0;
							if (puzzleTruthTable[row][column][m])
							{
								for (int j = 0; j < 9; j++)
								{
									if (puzzleTruthTable[j][column][number])
									{
										numberCount++;
										pairRow = j;
									}
								}
								//Qualifies as pair
								if (numberCount == 2 && puzzleTruthTable[pairRow][column][number])
								{
									for (int z = 1; z < 10; z++)
									{
										puzzleTruthTable[row][column][z] = false;
										puzzleTruthTable[pairRow][column][z] = false;
									}
									//check if in two elements
									if (getBox(row, column) == getBox(pairRow, column))
									{
										for (int x = getBoxTopRow(row, column); x < getBoxTopRow(row, column) + 3; x++)
										{
											for (int z = getBoxLeftColumn(row, column); z < getBoxLeftColumn(row, column) + 3; z++)
											{
												puzzleTruthTable[x][z][number] = false;
												puzzleTruthTable[x][z][m] = false;
											}
										}
									}
									puzzleTruthTable[row][column][number] = true;
									puzzleTruthTable[pairRow][column][number] = true;
									puzzleTruthTable[row][column][m] = true;
									puzzleTruthTable[pairRow][column][m] = true;
								}
							}
						}
					}
				}
			}
		}
	}

	//***********NEED to finish below here
	//Search for only possible solutions
	//Eliminate values from the rest of the cells in the element that the pair belongs to
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
