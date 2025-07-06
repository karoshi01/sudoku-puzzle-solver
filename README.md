# soduku-pozzule-solver
This is a C program that solves any valid 9x9 Sudoku puzzle using a backtracking algorithm. The program takes the puzzle input from the user (with 0 representing empty cells), applies Sudoku rules to validate placements, and attempts to solve the puzzle recursively. If a solution exists, it prints the completed board in a formatted, readable grid.
Accepts full puzzle input from the user via the console
     Validates input using standard Sudoku rules:
        No repeated numbers in any row
        No repeated numbers in any column
        No repeated numbers in any 3×3 subgrid
    Uses recursion and backtracking to explore all valid configurations
    Prints the original and solved puzzle in a clean, readable format
    Demonstrates how constraint satisfaction problems can be solved with recursion

How It Works
    User Input:
    The user is prompted to enter the values for each cell in the 9x9 grid. 0 is used to represent empty cells.
    Validation (checkRules function):
    Before placing any number in an empty cell, the program checks:
        Is the number already in the current row?
        Is the number already in the current column?
        Is the number already in the current 3x3 box?
    Backtracking (solveSudoku function):
        The program attempts to place numbers 1 to 9 in each empty cell.
        If a number is valid, it is placed temporarily.
        The solver then moves to the next empty cell recursively.
        If a dead end is reached, it backtracks and tries a new number.
        This continues until the board is fully filled or deemed unsolvable.
    Output:
    If a solution is found, the program prints the solved puzzle with borders and formatting. Otherwise, it notifies that no solution exists.
