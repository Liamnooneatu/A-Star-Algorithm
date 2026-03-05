#pragma once
#include "Grid.h"

#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

struct Point {
    int r = 0;
    int c = 0;

    bool operator==(const Point& other) const { return r == other.r && c == other.c; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

class AStarSolver {
public:
    enum class HeuristicType { Manhattan, Euclidean };

    struct Result {
        bool found = false;
        std::vector<Point> path; // start -> goal (inclusive)
        int totalCost = 0;
    };

    explicit AStarSolver(bool allowDiagonal = false, HeuristicType h = HeuristicType::Manhattan)
        : allowDiagonal_(allowDiagonal), heuristicType_(h)
    {
    }

    Result solve(const Grid& grid, Point start, Point goal) const {
        Result res{};

        if (!grid.inBounds(start.r, start.c) || !grid.inBounds(goal.r, goal.c)) {
            return res;
        }
        if (grid.isBlocked(start.r, start.c) || grid.isBlocked(goal.r, goal.c)) {
            return res;
        }
        if (start == goal) {
            res.found = true;
            res.path = { start };
            res.totalCost = 0;
            return res;
        }

        const int R = grid.rows();
        const int C = grid.cols();
        const int INF = std::numeric_limits<int>::max() / 4;

        std::vector<std::vector<CellInfo>> info(R, std::vector<CellInfo>(C));
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                info[r][c].g = INF;
                info[r][c].f = INF;
                info[r][c].parent = Point{ -1, -1 };
                info[r][c].closed = false;
            }
        }

        auto heuristic = [&](Point p) -> int {
            const int dr = std::abs(p.r - goal.r);
            const int dc = std::abs(p.c - goal.c);
            if (heuristicType_ == HeuristicType::Manhattan) {
                return dr + dc;
            }
            return static_cast<int>(std::lround(std::sqrt(dr * dr + dc * dc)));
            };

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

private:
    struct CellInfo {
        int g = 0;
        int f = 0;
        Point parent{ -1, -1 };
        bool closed = false;
    };

    bool allowDiagonal_;
    HeuristicType heuristicType_;

    static std::vector<Point> reconstructPath(
        const std::vector<std::vector<CellInfo>>& info,
        Point start,
        Point goal
    ) {
        std::vector<Point> path;

        Point cur = goal;
        if (cur.r < 0 || cur.c < 0) return {};
        if (info[cur.r][cur.c].parent.r == -1) return {};

        while (cur != start) {
            path.push_back(cur);
            cur = info[cur.r][cur.c].parent;

            // Safety break
            if (cur.r == -1) return {};
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
    }
};