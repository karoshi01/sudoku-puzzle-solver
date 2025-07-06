# soduku-pozzule-solver
a Sudoku solver is a program designed to automatically complete a partially filled 9x9 Sudoku puzzle while adhering to the game’s core rules: each number from 1 to 9 must appear exactly once in every row, column, and 3x3 subgrid. This particular solver is implemented in C and uses a well-known algorithm called **backtracking** to find the solution. The user is prompted to enter the values of the puzzle manually, with `0` indicating empty cells. The solver then scans the grid to find an empty cell and tries placing digits from 1 to 9 in it. For each digit, it checks if the placement is valid—i.e., the number doesn’t already exist in the same row, column, or 3x3 subgrid—using a validation function. If the placement is valid, it temporarily assigns the number to the cell and proceeds recursively to solve the rest of the puzzle. If it reaches a point where no valid number can be placed, it backtracks by undoing the last placement and tries the next possible number. This trial-and-error process continues until the entire grid is filled correctly or the algorithm concludes that no solution exists. Once solved, the program neatly prints both the original and completed puzzles. This approach demonstrates how recursion and constraint-based logic can be effectively used to solve complex problems like Sudoku.



#include <stdio.h>

int checkRules(int i, int j, int value, int sudokuP[9][9])
{
	for (int c = 0; c < 9; c++)
	{
		if (c != j && value == sudokuP[i][c])
			return 0;
	}
	for (int r = 0; r < 9; r++)
	{
		if (r != i && value == sudokuP[r][j])
			return 0;
	}
	int startRow = (i / 3) * 3;
	int startCol = (j / 3) * 3;
	for (int row = startRow; row < startRow + 3; row++)
	{
		for (int col = startCol; col < startCol + 3; col++)
		{
			if ((row != i || col != j) && value == sudokuP[row][col])
				return 0;
		}
	}
	return 1;
}

int solveSudoku(int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				for (int value = 1; value <= 9; value++)
				{
					if (checkRules(i, j, value, sudoku))
					{
						sudoku[i][j] = value;
						if (solveSudoku(sudoku))
							return 1;
						sudoku[i][j] = 0;
					}
				}
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	int sudoku[9][9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("give the value of the cell[%d][%d] : ", i, j);
			scanf("%d", &sudoku[i][j]);
		}
	}
	printf("\n\n -> given sudoku puzzle is D: <- \n");
	for (int row = 0; row < 9; row++)
	{
		if (row % 3 == 0)
			printf("+-------+-------+-------+\n");
		for (int col = 0; col < 9; col++)
		{
			if (col % 3 == 0)
				printf("| ");
			if (sudoku[row][col] == 0)
				printf(". ");
			else
				printf("%d ", sudoku[row][col]);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
	if (solveSudoku(sudoku))
	{
		printf("\n\n -> solved sudoku puzzle :D <- \n");
		for (int row = 0; row < 9; row++)
		{
			if (row % 3 == 0)
				printf("+-------+-------+-------+\n");
			for (int col = 0; col < 9; col++)
			{
				if (col % 3 == 0)
					printf("| ");
				printf("%d ", sudoku[row][col]);
			}
			printf("|\n");
		}
		printf("+-------+-------+-------+\n");
	}
	return 0;
}
