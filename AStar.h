#pragma once
#include "Grid.h"
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
//Liam Noone
/*
 _      _
| |    (_)
| |     _  __ _ _ __ ___
| |    | |/ _` | '_ ` _ \
| |____| | (_| | | | | | |
|______|_|\__,_|_| |_| |_|


*/

struct Point { // Represents a point in the grid with row and column indices
    int r = 0;
    int c = 0;

    bool operator==(const Point& other) const { return r == other.r && c == other.c; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

class AStarSolver { // Implements the A* pathfinding algorithm on a grid
public:

    // Manhattan distance measures the distance between two points along axes at right angles.
    // While Euclidean distance measures the straight-line distance between them.
    // Enum to specify the type of heuristic to use (Manhattan or Euclidean)

	enum class HeuristicType { Manhattan, Euclidean }; 

	struct Result { // This function represents the result of the A* search path taken, including whether a path was found, the path itself, and the total moves made.
        bool found = false;
        std::vector<Point> path; // start -> goal (inclusive)
        int totalCost = 0;
    };

	// Constructor for the AStarSolver class, which initializes the solver with options for allowing diagonal movement and choosing the heuristic type.
	explicit AStarSolver(bool allowDiagonal = false, HeuristicType h = HeuristicType::Manhattan)
        : allowDiagonal_(allowDiagonal), heuristicType_(h)
    {
    }

    // This function uses the a star tofind the shortest path from a start point to a goal point on a given grid. 
    // It returns a Result struct containing information about whether a path was found, the path itself, and the total cost of the path.
	Result solve(const Grid& grid, Point start, Point goal) const {
        Result res{};

        if (!grid.inBounds(start.r, start.c) || !grid.inBounds(goal.r, goal.c)) { // makes sure the goal is in the grid
            return res;
        }
		if (grid.isBlocked(start.r, start.c) || grid.isBlocked(goal.r, goal.c)) { //makes sure the goal is not blocked
            return res;
        }
        if (start == goal) { // if the start point could ever end up on the same point as the endpoint
            res.found = true;
            res.path = { start };
            res.totalCost = 0;
            return res;
        }

        const int R = grid.rows(); 
        const int C = grid.cols();
        const int INF = std::numeric_limits<int>::max() / 4; // set to a large number for larger grids.


        // This 2D vector stores information about each cell in the grid and measures the cost of each move to make it and the total end cost.
        // The parent cell for path reconstruction, and whether the cell has been closed (processed).
		std::vector<std::vector<CellInfo>> info(R, std::vector<CellInfo>(C)); 
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                info[r][c].g = INF;
                info[r][c].f = INF;
                info[r][c].parent = Point{ -1, -1 };
                info[r][c].closed = false;
            }
        }
        // This Lambda function calculates the Heuristic cost from a given point to the goal using either Manhattan or Euclidean distance based on the heuristic type that was used.
		auto heuristic = [&](Point p) -> int { 
            const int dr = std::abs(p.r - goal.r);
            const int dc = std::abs(p.c - goal.c);
            if (heuristicType_ == HeuristicType::Manhattan) {
                return dr + dc;
            }
            return static_cast<int>(std::lround(std::sqrt(dr * dr + dc * dc)));
            };

        // This struct represents a node in the open set of the A* algorithm, containing the f-cost, g-cost, and the point itself.
		struct OpenNode { 
            int f;
            int g;
            Point p;
        };

        // min-heap by f, tie-break by g
        auto cmp = [](const OpenNode& a, const OpenNode& b) {
            if (a.f != b.f) return a.f > b.f;
            return a.g > b.g;
            };
        std::priority_queue<OpenNode, std::vector<OpenNode>, decltype(cmp)> open(cmp);

        info[start.r][start.c].g = 0;
        info[start.r][start.c].f = heuristic(start);
        info[start.r][start.c].parent = start;
        open.push(OpenNode{ info[start.r][start.c].f, 0, start });

        const std::vector<Point> dirs4 = { {-1,0},{1,0},{0,-1},{0,1} };
        const std::vector<Point> dirs8 = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1} };
        const auto& dirs = allowDiagonal_ ? dirs8 : dirs4;

        while (!open.empty()) { 
            const auto current = open.top();
            open.pop();

            const Point u = current.p;

            // Skip stale nodes
            if (info[u.r][u.c].closed) continue;

            info[u.r][u.c].closed = true;
            
            if (u == goal) {
                res.found = true;
                res.totalCost = info[goal.r][goal.c].g;
                res.path = reconstructPath(info, start, goal);
                return res;
            }

            for (const auto& d : dirs) {
                const Point v{ u.r + d.r, u.c + d.c };

                if (!grid.inBounds(v.r, v.c)) continue;
                if (grid.isBlocked(v.r, v.c)) continue;
                if (info[v.r][v.c].closed) continue;

                const int stepCost = 1; // unweighted grid
                const int tentativeG = info[u.r][u.c].g + stepCost;

                if (tentativeG < info[v.r][v.c].g) {
                    info[v.r][v.c].g = tentativeG;
                    info[v.r][v.c].f = tentativeG + heuristic(v);
                    info[v.r][v.c].parent = u;

                    open.push(OpenNode{ info[v.r][v.c].f, info[v.r][v.c].g, v });
                }
            }
        }

        return res; // no path
    }



    // This struct stores information about each cell in the grid, including the g-cost (cost from start to current cell)
    // f-cost is the cost estimate, parent cell for path reconstruction, and whether the cell has been closed (processed).
private: 
    struct CellInfo { 
        int g = 0; //starting cell
		int f = 0; //f = g + h, where h is the heuristic cost to the goal
        Point parent{ -1, -1 };
        bool closed = false;
    };

    bool allowDiagonal_; //allows diagonal movement if set to true. if not it can only move up,down right or left.
    HeuristicType heuristicType_;

    // This function constructs a path from the goal locaition from the back to the start using the parent pointers stored in the CellInfo struct. 
    // The path is returned a point of vectors.
	static std::vector<Point> reconstructPath( 
        const std::vector<std::vector<CellInfo>>& info,
        Point start,
        Point goal
    ) {
        std::vector<Point> path;

        Point cur = goal; // starts at the end
        if (cur.r < 0 || cur.c < 0) return {};
        if (info[cur.r][cur.c].parent.r == -1) return {};

        while (cur != start) { // if not at the start point keep going back
            path.push_back(cur);
			cur = info[cur.r][cur.c].parent; // move to the parent cell

            // Safety break
            if (cur.r == -1) return {};
        }

		path.push_back(start); // vector is currently the goal -> start, so add the start at the end
		std::reverse(path.begin(), path.end()); // this revereses the path so that is goes from the start to the end now
        return path;
    }
};