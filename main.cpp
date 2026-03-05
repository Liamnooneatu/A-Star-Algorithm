#include <iostream>
#include <string>

#include "Grid.h"
#include "AStar.h"

static void printGrid(const Grid& grid, Point start, Point goal, const std::vector<Point>& path) {
    std::vector<std::vector<char>> view(grid.rows(), std::vector<char>(grid.cols(), '.'));

    for (int r = 0; r < grid.rows(); ++r) {
        for (int c = 0; c < grid.cols(); ++c) {
            if (grid.isBlocked(r, c)) view[r][c] = '#';
        }
    }

    for (const auto& p : path) {
        if (p != start && p != goal) view[p.r][p.c] = '*';
    }

    view[start.r][start.c] = 'S';
    view[goal.r][goal.c] = 'G';

    for (int r = 0; r < grid.rows(); ++r) {
        for (int c = 0; c < grid.cols(); ++c) {
            std::cout << view[r][c] << ' ';
        }
        std::cout << '\n';
    }
}

static void printPath(const std::vector<Point>& path) {
    if (path.empty()) {
        std::cout << "(empty)\n";
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << "(" << path[i].r << "," << path[i].c << ")";
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << "\n";
}

static void runTest(const std::string& name, const Grid& grid, Point start, Point goal) {
    std::cout << "\n=== " << name << " ===\n";
    AStarSolver solver(/*allowDiagonal=*/false, AStarSolver::HeuristicType::Manhattan);

    const auto result = solver.solve(grid, start, goal);

    if (!result.found) {
        std::cout << "No path found.\n";
        printGrid(grid, start, goal, {});
        return;
    }

    std::cout << "Path found! Cost: " << result.totalCost << "\n";
    std::cout << "Path: ";
    printPath(result.path);

    std::cout << "\nGrid view:\n";
    printGrid(grid, start, goal, result.path);
}

int main() {
    // Test 1: Your original grid
    Grid grid1({
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,1,0},
        {0,1,0,0,0},
        {0,0,0,0,0}
        });

    runTest("Test 1: Standard path", grid1, Point{ 0,0 }, Point{ 4,4 });

    // Test 2: Start equals goal
    runTest("Test 2: Start == Goal", grid1, Point{ 2,2 }, Point{ 2,2 });

    // Test 3: No possible path (block a corridor)
    Grid grid2({
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,1,0,1,0},
        {0,1,0,1,0},
        {0,0,0,1,0}
        });
    runTest("Test 3: No path", grid2, Point{ 0,0 }, Point{ 4,4 });

    return 0;
}