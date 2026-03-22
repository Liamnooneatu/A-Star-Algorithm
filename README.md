---
layout: single
title: "A* Pathfinding Algorithm"
toc: true
toc_label: "Contents"
toc_icon: "sitemap"
---

```cpp
/**
 * @file     AStar.h / main.cpp / Grid.h
 * @project  A* Pathfinding Algorithm
 * @author   Liam Noone
 * @language C++17
 * @heuristics Manhattan | Euclidean
 * @status   Complete — all 3 test cases passing
 */
```

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=flat-square&logo=cplusplus)
![GitHub Pages](https://img.shields.io/badge/Hosted-GitHub%20Pages-222?style=flat-square&logo=github)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)
![Heuristics](https://img.shields.io/badge/Heuristics-Manhattan%20%7C%20Euclidean-orange?style=flat-square)

---

## Project Overview

```cpp
// A* finds the shortest path on a 2D grid using:
//   f(n) = g(n) + h(n)
//   where g(n) = cost from start to current node
//         h(n) = heuristic estimate to goal
```

I was tasked with implementing the A* (A-Star) pathfinding algorithm in C++. A* is a best-first search algorithm that finds the shortest path between two points on a grid by combining the actual cost of reaching a node with a heuristic estimate to the goal. The implementation supports two heuristic methods — Manhattan distance and Euclidean distance — and was tested across three distinct grid configurations.

---

## File Structure

```
A-Star-Algorithm/
├── Grid.h       // Grid data structure — cell storage, bounds checking, wall detection
├── AStar.h      // A* solver — open list, heuristic, path reconstruction (197 lines)
└── main.cpp     // Test runner — grid setup, output, 3 test cases (103 lines)
```

---

## Terminal Output — Test Cases

<table>
  <tr>
    <td align="center"><strong>Test 1 — Standard Path</strong></td>
    <td align="center"><strong>Test 2 — Start Equals Goal</strong></td>
    <td align="center"><strong>Test 3 — No Path</strong></td>
  </tr>
  <tr>
    <td><img src="https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test1.png" width="360" height="400" style="object-fit:cover;"></td>
    <td><img src="https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test2.png" width="260" height="200" style="object-fit:cover;"></td>
    <td><img src="https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test3.png" width="260" height="200" style="object-fit:cover;"></td>
  </tr>
</table>

---

## Code Analysis

```cpp
// ============================================================
// SECTION 1 — Grid Representation
// FILE: Grid.h
// ============================================================
```

### Grid Representation

The grid is a 2D array where `0` is a free cell and `1` is a wall. The `Grid` class validates the input on construction — it rejects empty grids and grids with uneven row lengths, which prevents silent bugs during pathfinding.

```cpp
// 0 = free cell, 1 = blocked wall
Grid grid1({
    {0,0,0,0,0},
    {0,1,1,1,0},
    {0,0,0,1,0},
    {0,1,0,0,0},
    {0,0,0,0,0}
});
```

| Symbol | Meaning |
|--------|---------|
| `0` | Free cell — passable |
| `1` | Wall — blocked |
| `S` | Start position |
| `G` | Goal position |
| `*` | Path taken |
| `#` | Wall (terminal view) |

---

```cpp
// ============================================================
// SECTION 2 — Heuristic Lambda Function
// FILE: AStar.h  LINE: 53
// ============================================================
```

### The Heuristic — Lambda Function

```cpp
/**
 * @brief    Estimates cost from point p to goal
 * @param    p     Current grid point {row, col}
 * @returns  int   Heuristic cost estimate (h value)
 * @note     Switches between Manhattan and Euclidean
 *           based on heuristicType_ set at construction
 */
auto heuristic = [&](Point p) -> int {
    const int dr = std::abs(p.r - goal.r);
    const int dc = std::abs(p.c - goal.c);
    if (heuristicType_ == HeuristicType::Manhattan) {
        return dr + dc;                                         // O(1)
    }
    return static_cast<int>(std::lround(std::sqrt(dr * dr + dc * dc))); // O(1) but slower
};
```

[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/AStar.h#L53)

The lambda captures `goal` and `heuristicType_` from the surrounding scope — this avoids passing them as parameters on every node visit. Manhattan adds the row and column differences. Euclidean calculates the straight-line distance using Pythagoras.

**Complexity:** `O(1)` per node — called once per neighbour expansion.

---

```cpp
// ============================================================
// SECTION 3 — Open List (Priority Queue)
// FILE: AStar.h  LINES: 61-70
// ============================================================
```

### Open List — Priority Queue

A* always processes the most promising node first. This is handled by a min-heap priority queue sorted by `f` cost, with `g` cost as a tiebreaker. Lower `f` = closer to the goal = processed first.

```cpp
/**
 * @struct OpenNode
 * @brief  Node entry in the A* open list (min-heap)
 *
 * @field  f   Total estimated cost: f = g + h
 * @field  g   Actual cost from start to this node
 * @field  p   Grid position {row, col}
 */
struct OpenNode {
    int f;
    int g;
    Point p;
};

// Min-heap comparator — lowest f wins, g breaks ties
auto cmp = [](const OpenNode& a, const OpenNode& b) {
    if (a.f != b.f) return a.f > b.f;
    return a.g > b.g;
};

std::priority_queue<OpenNode, std::vector<OpenNode>, decltype(cmp)> open(cmp);
```

[View in AStar.h — lines 61–70](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/AStar.h#L61-L70)

**Complexity:** `O(log n)` per push/pop — where `n` is the number of nodes in the open list.

---

```cpp
// ============================================================
// SECTION 4 — Path Reconstruction
// FILE: AStar.h  LINES: 116-132
// ============================================================
```

### Path Reconstruction

Once the goal is reached, the path is rebuilt by following parent pointers backwards from goal to start, then reversing the result so it reads start → goal.

```cpp
/**
 * @brief  Reconstructs path from goal back to start
 *         using parent pointers stored per cell
 * @returns std::vector<Point>  Path from start -> goal
 */
Point cur = goal;
while (cur != start) {
    path.push_back(cur);
    cur = info[cur.r][cur.c].parent; // follow parent pointer
}
path.push_back(start);
std::reverse(path.begin(), path.end()); // reverse: goal->start becomes start->goal
```

[View in AStar.h — lines 116–132](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/AStar.h#L116-L132)

**Complexity:** `O(p)` — where `p` is the length of the final path.

---

```cpp
// ============================================================
// SECTION 5 — Grid Output / Terminal Visualisation
// FILE: main.cpp  LINES: 7-19
// ============================================================
```

### Grid Output

The terminal output uses a character map to visualise the result. Each cell is mapped to a display character before printing.

```cpp
// Character map: blocked -> '#', path -> '*', S/G -> start/goal
if (grid.isBlocked(r, c)) view[r][c] = '#';

for (const auto& p : path) {
    if (p != start && p != goal) view[p.r][p.c] = '*';
}

view[start.r][start.c] = 'S';
view[goal.r][goal.c]   = 'G';
```

[View in main.cpp — lines 7–19](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/main.cpp#L7-L19)

---

## Heuristic Comparison

```cpp
// ============================================================
// HEURISTIC REFERENCE TABLE
// ============================================================
```

### Manhattan vs Euclidean — At a Glance

| Feature | Manhattan | Euclidean |
|---|---|---|
| Formula | `\|dr\| + \|dc\|` | `sqrt(dr² + dc²)` |
| Movement type | 4-directional (up/down/left/right) | Works well with diagonals |
| Computation cost | `O(1)` — addition only | `O(1)` — but requires `sqrt()` |
| Best for | Standard grid pathfinding | Open areas, diagonal movement |
| Admissible on grids | Yes — never overestimates | Can slightly overestimate |
| Used in this project | Primary heuristic | Straight-line detection |

---

### Manhattan Distance

```cpp
// @heuristic Manhattan
// @formula  h = |dr| + |dc|
// @use      Primary heuristic — 4-directional grid movement
```

Manhattan distance measures the distance between two points along axes at right angles — like navigating city blocks where you can only move up, down, left, or right.

<img src="https://tse2.mm.bing.net/th/id/OIP.bXgaBczDZcXPA3qr91lsXwAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="Manhattan Distance" width="400">

**Advantages:** Lightweight, fast to compute, and well-suited to grid-based movement.

**Disadvantages:** On larger grids it can explore cells in suboptimal directions before correcting course. Higher memory usage and per-node overhead on complex grids.

[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/AStar.h#L53)

![Manhattan code screenshot](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20114240.png)

---

### Euclidean Distance

```cpp
// @heuristic Euclidean
// @formula  h = sqrt(dr² + dc²)
// @use      Straight-line distance detection
```

Euclidean distance measures the true straight-line distance between two points using Pythagoras' theorem. More geometrically accurate and performs better when diagonal movement is permitted.

<img src="https://tse2.mm.bing.net/th/id/OIP.HMw2dip3CqAMSZwbK2LiZQAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="Euclidean Distance" width="400">

**Advantages:** More precise on diagonal paths. Reduces unnecessary exploration in open areas.

**Disadvantages:** Requires `sqrt()` at every node — slower than Manhattan on purely grid-based movement.

[View in AStar.h — line 59](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/master/AStar.h#L59)

![Euclidean code screenshot](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20115546.png)

---

### Heuristic Alternatives

```cpp
// Alternatives considered:
//   - Dijkstra's Algorithm  -> no heuristic, explores all directions equally
//   - Breadth-First Search  -> unweighted only, no cost awareness
//   - RRT                   -> random sampling, not suited to discrete grids
```

A Rapidly-exploring Random Tree (RRT) is designed for high-dimensional continuous spaces such as robotic arm motion planning. For a discrete 2D grid it would be the wrong tool — it produces non-optimal paths, relies on random sampling rather than deterministic search, and is slower for simple grids. A* solves this problem efficiently and optimally without that overhead.

---

## Limitations & Reflections

```cpp
// @known-issues
// 1. Algorithm logic in AStar.h instead of AStar.cpp (unconventional)
// 2. Test grids are hardcoded — no file or user input support
// 3. Manhattan may over-explore on large sparse grids
```

**Code structure:** The core algorithm logic lives in `AStar.h` (197 lines) rather than in `main.cpp` (103 lines). While this is unconventional — most C++ projects keep implementation logic out of header files — it did not cause any compilation or runtime issues. In production this would be refactored so `AStar.h` holds only declarations and a separate `AStar.cpp` holds the implementation.

**Hardcoding:** The grid configurations for all three test cases are hardcoded. This is acceptable for demonstration purposes but would need to be replaced with file-based or user-driven input for a more flexible system.

**Scalability:** Manhattan distance can explore unnecessary nodes on larger grids. Improvements could include weighted A* (to trade optimality for speed) or a more informed heuristic for specific grid shapes.

---

## A.I Usage Disclosure

```cpp
// @ai-tools
//   Claude  (claude.ai)  -> code generation
//   ChatGPT (openai.com) -> research: heuristic comparison, RRT analysis
// @note  All code reviewed, tested and validated by author before submission
```

**Claude (claude.ai)** assisted with code generation. Claude structured the implementation by placing the core algorithm in `AStar.h` rather than `main.cpp`, which differs from conventional C++ practice but did not affect correctness.

**ChatGPT** was used for research — specifically to compare Manhattan and Euclidean distance against alternative approaches such as RRT. I also conducted independent research using the sources listed below.

---

## S.T.A.R Write-Up

```cpp
// ============================================================
// PROJECT REFLECTION — S.T.A.R FORMAT
// ============================================================
```

### Situation
Pathfinding is a core problem in computer science with applications in game AI, robotics, and GPS navigation. I was tasked with implementing an efficient grid-based pathfinding solution in C++ that could find the shortest route between two points while avoiding obstacles.

### Task
My goal was to implement the A* algorithm that could navigate a 2D grid from a start point to an end point, avoid blocked cells, and be validated against three distinct test configurations.

### Action
I implemented A* using an open list and closed list. At each step the node with the lowest `f(n) = g(n) + h(n)` is selected, where `g(n)` is the actual cost from start and `h(n)` is the heuristic estimate to goal. I implemented both Manhattan and Euclidean distance as heuristic options and designed three test grids to validate the solution.

### Result
All three test cases produced correct output. The algorithm found the shortest path in Test 1 and Test 2, and correctly reported no valid path in Test 3. The implementation is functional and demonstrates a solid understanding of heuristic search in C++.

---

## References

```cpp
// @references
```

- [StackOverflow — RRT in C++](https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c)
- [Wikipedia — Euclidean Algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm)
- [Wikipedia — Heuristic (Computer Science)](https://en.wikipedia.org/wiki/Heuristic_(computer_science))
- [GeeksForGeeks — A* Search Algorithm](https://www.geeksforgeeks.org/dsa/a-search-algorithm/)
- [ML Journey — Manhattan vs Euclidean Distance](https://mljourney.com/manhattan-distance-vs-euclidean-distance-key-differences/)
- [Tarodev — A* Pathfinding (YouTube)](https://www.youtube.com/watch?v=i0x5fj4PqP4)
- [Computerphile — A* Explained (YouTube)](https://www.youtube.com/watch?v=ySN5Wnu88nE)
- [ChatGPT](https://chatgpt.com)
- [Claude](https://claude.ai)
