#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in a cell
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Check if 'num' is not already present in the current row, current column, and current 3x3 subgrid
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num || grid[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row = -1, col = -1;
    bool isEmpty = true;
    
    // Find the first empty cell in the grid
    for (int i = 0; i < N && isEmpty; i++) {
        for (int j = 0; j < N && isEmpty; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
            }
        }
    }
    
    // If no empty cell is found, the puzzle is solved
    if (isEmpty) {
        return true;
    }
    
    // Try filling the empty cell with a valid number
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            
            // Recursively solve the puzzle
            if (solveSudoku(grid)) {
                return true;
            }
            
            // If no solution is found, backtrack and try the next number
            grid[row][col] = 0;
        }
    }
    
    // No valid number can be placed, so return false to trigger backtracking
    return false;
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N));
    
    // Input the Sudoku grid (0 represents empty cells)
    cout << "Enter the Sudoku puzzle (9x9 grid):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
