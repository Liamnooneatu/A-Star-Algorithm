---
layout: single
title: "A* Pathfinding Algorithm"
toc: true
toc_label: "Contents"
toc_icon: "sitemap"
---

/**
 * @project  A* Pathfinding
 * @author   Liam Noone
 * @language C++
 * @heuristics Manhattan | Euclidean
 */

This is my Github pages for my A* Algorithm Project by Liam Noone.

## Project Overview

I was tasked with creating a project that implements the A* (A-Star) pathfinding algorithm in C++. A* is a search algorithm that finds the shortest path between two points on a grid by combining the actual cost of reaching a node with an estimated cost to the goal. The implementation supports two heuristic methods — Manhattan distance and Euclidean distance — and was tested across three distinct grid configurations.

---

## Terminal Output — Test Cases

**Test 1:**

![Test 1](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test1.png)

**Test 2:**

![Test 2](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test2.png)

**Test 3:**

![Test 3](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test3.png)

---

## Code Analysis

The project is split across three files: `Grid.h` defines the grid structure, `AStar.h` contains the full A* algorithm, and `main.cpp` handles test setup and output.

---

### Grid Representation

The grid is a 2D array where `0` is a free cell and `1` is a wall. The `Grid` class validates the input on construction — it rejects empty grids and grids with uneven row lengths, which prevents silent bugs during pathfinding.

```cpp
// 0 = free cell, 1 = blocked
Grid grid1({
    {0,0,0,0,0},
    {0,1,1,1,0},
    {0,0,0,1,0},
    {0,1,0,0,0},
    {0,0,0,0,0}
});
```

---

### The Heuristic — Lambda Function

The heuristic is implemented as an inline lambda inside the `solve()` function. It calculates the estimated cost from any cell to the goal using either Manhattan or Euclidean distance depending on which mode the solver was constructed with.

```cpp
auto heuristic = [&](Point p) -> int {
    const int dr = std::abs(p.r - goal.r);
    const int dc = std::abs(p.c - goal.c);
    if (heuristicType_ == HeuristicType::Manhattan) {
        return dr + dc;
    }
    return static_cast<int>(std::lround(std::sqrt(dr * dr + dc * dc)));
};
```

[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L53)

Manhattan adds the row and column differences. Euclidean calculates the straight-line distance using Pythagoras. The lambda captures `goal` and `heuristicType_` from the surrounding scope — this avoids passing them as parameters on every node visit.

---

### Open List — Priority Queue

A* always processes the most promising node first. This is handled by a min-heap priority queue sorted by `f` cost, with `g` cost as a tiebreaker. Lower `f` = closer to the goal = processed first.

```cpp
struct OpenNode {
    int f;  // total estimated cost (g + h)
    int g;  // actual cost from start
    Point p;
};

auto cmp = [](const OpenNode& a, const OpenNode& b) {
    if (a.f != b.f) return a.f > b.f;
    return a.g > b.g;
};

std::priority_queue<OpenNode, std::vector<OpenNode>, decltype(cmp)> open(cmp);
```

[View in AStar.h — lines 61–70](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L61-L70)

---

### Path Reconstruction

Once the goal is reached, the path is rebuilt by walking backwards through parent pointers stored at each cell, then reversing the result so it reads start → goal.

```cpp
Point cur = goal;
while (cur != start) {
    path.push_back(cur);
    cur = info[cur.r][cur.c].parent;
}
path.push_back(start);
std::reverse(path.begin(), path.end());
```

[View in AStar.h — lines 116–132](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L116-L132)

---

### Grid Output

The terminal output uses a character map to visualise the result. Free cells are `.`, walls are `#`, the path is `*`, and the start and goal are `S` and `G`.

```cpp
if (grid.isBlocked(r, c)) view[r][c] = '#';

for (const auto& p : path) {
    if (p != start && p != goal) view[p.r][p.c] = '*';
}

view[start.r][start.c] = 'S';
view[goal.r][goal.c]   = 'G';
```

[View in main.cpp — lines 7–19](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/main.cpp#L7-L19)

---

## Heuristic Comparison

### Manhattan Distance

Manhattan distance measures the distance between two points along axes at right angles — like navigating city blocks where you can only move up, down, left, or right.

<img src="https://tse2.mm.bing.net/th/id/OIP.bXgaBczDZcXPA3qr91lsXwAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="Manhattan Distance" width="400">

**Formula:** `h = |dr| + |dc|`

**Advantages:** Lightweight, fast to compute, and well-suited to grid-based movement.

**Disadvantages:** On larger grids it can explore cells moving in suboptimal directions before correcting course, leading to unnecessary node visits. Also carries higher memory usage as data is stored across many nodes, and adds overhead at each node when calculating the heuristic.

[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L53)

![Manhattan code screenshot](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20114240.png)

---

### Euclidean Distance

Euclidean distance measures the straight-line distance between two points using Pythagoras' theorem. It is more geometrically accurate and performs better when diagonal movement is permitted.

<img src="https://tse2.mm.bing.net/th/id/OIP.HMw2dip3CqAMSZwbK2LiZQAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="Euclidean Distance" width="400">

**Formula:** `h = sqrt(dr² + dc²)`

**Advantages:** More precise than Manhattan on diagonal paths. Reduces unnecessary exploration in open grid areas.

**Disadvantages:** Involves a square root calculation at every node, which adds overhead compared to Manhattan on purely grid-based movement.

[View in AStar.h — line 59](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L59)

![Euclidean code screenshot](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20115546.png)

---

### Heuristic Alternatives

Other algorithms that could solve pathfinding include Dijkstra's Algorithm, Breadth-First Search (BFS), and Rapidly-exploring Random Tree (RRT).

A Rapidly-exploring Random Tree (RRT) is designed for high-dimensional continuous spaces such as robotic arm motion planning. For a discrete 2D grid, RRT would be the wrong tool — it produces non-optimal paths, relies on random sampling rather than deterministic search, and is slower for simple grids. A* solves this problem efficiently and optimally without that overhead.

---

## Limitations & Reflections

**Code structure:** The core algorithm logic lives in `AStar.h` (197 lines) rather than in `main.cpp` (103 lines). While this is unconventional — most C++ projects keep implementation logic out of header files — it did not cause any compilation or runtime issues across the three tests. In a production context, this would be refactored so that `AStar.h` contains only declarations and a separate `AStar.cpp` holds the implementation.

**Hardcoding:** The grid configurations for all three test cases are hardcoded. This is acceptable for demonstration purposes but would need to be replaced with file-based or user-driven input for a more flexible system.

**Scalability:** Manhattan distance can explore unnecessary nodes on larger grids. Improvements could include weighted A* (to trade optimality for speed) or a more informed heuristic for specific grid shapes.

---

## A.I Usage Disclosure

I used two AI tools during this project:

**Claude (claude.ai)** assisted with code generation. Claude structured the implementation by placing the core algorithm in `AStar.h` rather than `main.cpp`, which differs from conventional C++ practice but did not affect correctness. All code was reviewed, tested, and validated by me before submission.

**ChatGPT** was used for research — specifically to compare Manhattan and Euclidean distance against alternative approaches such as RRT, and to better understand when each method is appropriate. I also conducted independent research using the sources listed below.

---

## S.T.A.R Write-Up

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

- [StackOverflow — RRT in C++](https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c)
- [Wikipedia — Euclidean Algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm)
- [Wikipedia — Heuristic (Computer Science)](https://en.wikipedia.org/wiki/Heuristic_(computer_science))
- [GeeksForGeeks — A* Search Algorithm](https://www.geeksforgeeks.org/dsa/a-search-algorithm/)
- [ML Journey — Manhattan vs Euclidean Distance](https://mljourney.com/manhattan-distance-vs-euclidean-distance-key-differences/)
- [Tarodev — A* Pathfinding (YouTube)](https://www.youtube.com/watch?v=i0x5fj4PqP4)
- [Computerphile — A* Explained (YouTube)](https://www.youtube.com/watch?v=ySN5Wnu88nE)
- [ChatGPT](https://chatgpt.com)
- [Claude](https://claude.ai)
