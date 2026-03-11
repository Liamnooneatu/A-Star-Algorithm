#pragma once
#include <vector>
#include <stdexcept>
//Liam Noone
/*
 _      _
| |    (_)
| |     _  __ _ _ __ ___
| |    | |/ _` | '_ ` _ \
| |____| | (_| | | | | | |
|______|_|\__,_|_| |_| |_|


*/

// 0 = free cell, 1 = blocked path
class Grid {
public:
    using Matrix = std::vector<std::vector<int>>; //simplified

    // The constructor takes the 2D array and moves it into the class
    explicit Grid(Matrix cells) 
        : cells_(std::move(cells))
    {
        // Check if the grid is empty or if the first row is empty
		if (cells_.empty() || cells_[0].empty()) { 
            throw std::invalid_argument("Grid cannot be empty.");
        }

        // Get the number of columns from the first row
		const auto cols = cells_[0].size(); 
        for (const auto& row : cells_) {
            if (row.size() != cols) {
				throw std::invalid_argument("Grid rows must all have the same length."); // Check if all rows have the same number of columns
            }
        }
    }
    // Return the number of columns in the grid and rows in the gird
	int rows() const { return static_cast<int>(cells_.size()); } 
	int cols() const { return static_cast<int>(cells_[0].size()); } 

    // Check if the given row and column indices are within the bounds of the grid
	bool inBounds(int r, int c) const {
        return r >= 0 && r < rows() && c >= 0 && c < cols();
    }

    // Check if the cell at the given row and column indices is blocked (i.e., has a value of 1)
	bool isBlocked(int r, int c) const { 
        return cells_[r][c] != 0;
    }

	int at(int r, int c) const { return cells_[r][c]; } // Return the value of the cell at the given row and column indices

private:
	Matrix cells_; // The 2D array representing the grid, where each cell can be free (0) or blocked (1)
};