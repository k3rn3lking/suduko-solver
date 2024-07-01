# Sudoku Solver

This Sudoku solver was created by Dhruv Sharma (b23ci1016). It is a simple Sudoku solver written in C. It allows you to input a Sudoku puzzle and it will output the solution, if one exists.

## How to Use

1. **Compile**: Compile the program using a C compiler. For example, if you're using GCC, you can compile it with:
    ```sh
    gcc `pkg-config --cflags gtk+-3.0` -o sudoku_solver sudoku_solver.c `pkg-config --libs gtk+-3.0`
    ```

2. **Input**: Write numbers with space and use '0' to represent empty cells, and separate numbers with spaces. For example:
    ```text
    5 3 0 0 7 0 0 0 0
    6 0 0 1 9 5 0 0 0
    0 9 8 0 0 0 0 6 0
    8 0 0 0 6 0 0 0 3
    4 0 0 8 0 3 0 0 1
    7 0 0 0 2 0 0 0 6
    0 6 0 0 0 0 2 8 0
    0 0 0 4 1 9 0 0 5
    0 0 0 0 8 0 0 7 9
    ```

3. **Run**: Run the program and specify the input file as a command-line argument:
    ```sh
    ./sudoku_solver
    ```

4. **Output**: The program will output the solved Sudoku puzzle if a solution exists. If no solution is found, it will indicate that the puzzle is unsolvable.

## Notes

- This solver uses a backtracking algorithm to find the solution to the Sudoku puzzle.
- Make sure the input Sudoku puzzle is in a valid format, with 9 rows and 9 columns, and contains only numbers from 0 to 9.

