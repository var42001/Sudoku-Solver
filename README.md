# Sudoku Solver
# Introduction
The program which checks for solutions for 9x9 Sudoku puzzles.
Written completely in C++, this program takes in input from the user or from a file containing the values. 
It then validates the puzzle and then displays whether it is a valid solution or not.

The program will require the user to input the Sudoku puzzle into it. There are two ways to do this.
The user can either input the values manually one-by-one when the program is running.
The user can write all the values into a file, seperated by whitespaces. The file can have any name or extension. 

#How It Works

The program starts.
The values in all the cells are checked to see if they are in the range 1-9. If not, the puzzle is invalid.
Every row is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
Every column is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
Every 3x3 grid is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
If all the criteria have been satisfied, the solution is valid.
The program stops.

