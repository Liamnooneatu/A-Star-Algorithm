#include <iostream>
#include <string>
#include "Grid.h"
#include "AStar.h"
//Liam Noone
/*
 _      _
| |    (_)
| |     _  __ _ _ __ ___
| |    | |/ _` | '_ ` _ \
| |____| | (_| | | | | | |
|______|_|\__,_|_| |_| |_|
       
*/


// This function prints the grid and shows the blocked cells, the path from start to goal, and the start and goal positions.
static void printGrid(const Grid& grid, Point start, Point goal, const std::vector<Point>& path) { 
    std::vector<std::vector<char>> view(grid.rows(), std::vector<char>(grid.cols(), '.'));

    for (int r = 0; r < grid.rows(); ++r) {  // looks through each row of the grid abd searchs for a blocked cell.
		for (int c = 0; c < grid.cols(); ++c) { // if blocked cell is found it will be represented by a # in the view of the grid.
            if (grid.isBlocked(r, c)) view[r][c] = '#';
        }
    }

    // This checks the cells and searchs for a dot and if it is free it replaces with a * to show the path from start to goal.
	for (const auto& p : path) { 
        if (p != start && p != goal) view[p.r][p.c] = '*';
    }

    view[start.r][start.c] = 'S'; //Start position
	view[goal.r][goal.c] = 'G'; //Goal position

    for (int r = 0; r < grid.rows(); ++r) { // prints grid in the console.
        for (int c = 0; c < grid.cols(); ++c) {
            std::cout << view[r][c] << ' ';
        }
        std::cout << '\n';
    }
}

static void printPath(const std::vector<Point>& path) { // prints the path taken.
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

static void runTest(const std::string& name, const Grid& grid, Point start, Point goal) { // runs the actual test and prints the results.
    std::cout << "\n=== " << name << " ===\n";
    AStarSolver solver(/*allowDiagonal=*/false, AStarSolver::HeuristicType::Manhattan);

    // Runs the A* algorithm to find the path from start to goal on the given grid and stores the result in a variable called result.
	const auto result = solver.solve(grid, start, goal);

    if (!result.found) { // Prints this if no path is found.
        std::cout << "No path found.\n";
        printGrid(grid, start, goal, {});
        return;
    }

    std::cout << "Path found! Cost: " << result.totalCost << "\n";
    std::cout << "Path: ";
    printPath(result.path);

    // Prints the grid with a path from start to goal.
	std::cout << "\nGrid view:\n";
    printGrid(grid, start, goal, result.path); //prints the path/.
}

int main() {
    // Test 1
    Grid grid1({
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,1,0},
        {0,1,0,0,0},
        {0,0,0,0,0}
        });

    runTest("Test 1: Standard path", grid1, Point{ 0,0 }, Point{ 4,4 });

    // Test 2
    runTest("Test 2: Start == Goal", grid1, Point{ 2,2 }, Point{ 2,2 });

    // Test 3
    Grid grid2({
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,1,0,1,0},
        {0,1,0,1,1},
        {0,0,0,1,0}
        });
    runTest("Test 3: No path", grid2, Point{ 0,0 }, Point{ 4,4 });

    return 0;
}