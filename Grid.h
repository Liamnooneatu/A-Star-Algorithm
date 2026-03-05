#pragma once
#include <vector>
#include <stdexcept>

class Grid {
public:
    using Matrix = std::vector<std::vector<int>>; // 0 = free, 1 = blocked

    explicit Grid(Matrix cells)
        : cells_(std::move(cells))
    {
        if (cells_.empty() || cells_[0].empty()) {
            throw std::invalid_argument("Grid cannot be empty.");
        }
        const auto cols = cells_[0].size();
        for (const auto& row : cells_) {
            if (row.size() != cols) {
                throw std::invalid_argument("Grid rows must all have the same length.");
            }
        }
    }

    int rows() const { return static_cast<int>(cells_.size()); }
    int cols() const { return static_cast<int>(cells_[0].size()); }

    bool inBounds(int r, int c) const {
        return r >= 0 && r < rows() && c >= 0 && c < cols();
    }

    bool isBlocked(int r, int c) const {
        return cells_[r][c] != 0;
    }

    int at(int r, int c) const { return cells_[r][c]; }

private:
    Matrix cells_;
};