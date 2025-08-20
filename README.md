# sudoku-pozzule-solver
A Sudoku solver is a program designed to automatically complete a partially filled 9x9 Sudoku puzzle while adhering to the game’s core rules:

Each number from 1 to 9 must appear exactly once in every row, column, and 3x3 subgrid.
This solver is implemented in C using the backtracking algorithm.

🔹 How It Works : 
The user provides the puzzle manually .
The solver scans the grid for the next empty cell.
For each empty cell, it tries placing digits 1–9.
Before placement, it checks validity with a constraint function ensuring the number doesn’t already exist in the same row, column, or 3x3 block.
If valid, it recursively continues solving the rest of the puzzle.
If no number works, the algorithm backtracks (undoes the last step) and tries another possibility.
This continues until the grid is solved or the algorithm concludes no solution exists.

🔹 Features :
Solves any valid Sudoku puzzle (easy → expert).
Uses backtracking recursion for correctness.
Input/Output handled via WinAPI GUI:
Solved cells are highlighted in green.


🔹 Tech Stack :
Language: C (WinAPI)
Algorithm: Backtracking recursion
GUI: Custom Windows API interface

🔹 Demo

<img width="538" height="773" alt="image" src="https://github.com/user-attachments/assets/91ba5204-7c49-4555-a2ed-e4be3c781779" />
<img width="535" height="768" alt="image" src="https://github.com/user-attachments/assets/4363542c-6f51-4a4d-ba67-ff991081a4db" />
<img width="538" height="769" alt="image" src="https://github.com/user-attachments/assets/2265d4da-236f-4a45-b488-31b3c1e38c78" />


