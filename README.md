---
layout: single
title: "A* Pathfinding Algorithm"
toc: true
toc_label: "Contents"
toc_icon: "sitemap"
---




This is my Github pages for my A* Algorithm Project by Liam Noone.


My Project Overview:
I was tasked with creating a project that implements the A* (A-Star) pathfinding algorithm in C++. A* is a search algorithm that finds the shortest path between two points on a grid by combining the actual cost of reaching a node with an estimated cost to the goal. 
The implementation supports two heuristic methods — Manhattan distance and Euclidean (which we will discuss later in depth on these) distance — and was tested across three distinct grid configurations to ensure compatability against set hurdles..


Terminal output results for my three test cases:

**Test1:**

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test1.png)

**Test2:**

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test2.png)
 
**Test3:**

 ![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/test3.png)

## Code Analysis









The project is split across three files: `Grid.h` defines the grid structure, `AStar.h` contains the full A* algorithm, and `main.cpp` handles test setup and output.

---

### Grid representation

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

### The heuristic — lambda function

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

[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L51)
viewable here via link

Manhattan adds the row and column differences. Euclidean calculates the straight-line distance using Pythagoras. The lambda captures `goal` and `heuristicType_` from the surrounding scope — this avoids passing them as parameters on every node visit.

---

### Open list — priority queue

A* always processes the most promising node first. This is handled by a min-heap priority queue sorted by `f` cost, with `g` cost as a tiebreaker. [View in AStar.h — lines 61–70](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L61-L70)
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


---

### Path reconstruction

`````cpp
Point cur = goal;
while (cur != start) {
    path.push_back(cur);
    cur = info[cur.r][cur.c].parent;
}
path.push_back(start);
std::reverse(path.begin(), path.end());
Once the goal is reached, the path is rebuilt by walking backwards through parent pointers stored at each cell, then reversing the result so it reads start to the actual goal (https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L116-L132).
`````
REPLACE WITH:
`````markdown
````cpp
Point cur = goal;
while (cur != start) {
    path.push_back(cur);
    cur = info[cur.r][cur.c].parent;
}
path.push_back(start);
std::reverse(path.begin(), path.end());
````
[View in AStar.h — lines 116–132](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L116-L132)
`````



---

### Grid output


The terminal output uses a character map to visualise the result. Free cells are `.`, walls are `#`, the path is `*`, and the start and goal are `S` and `G` (https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/main.cpp#L7-L19).

````markdown
```cpp
if (grid.isBlocked(r, c)) view[r][c] = '#';
for (const auto& p : path) {
    if (p != start && p != goal) view[p.r][p.c] = '*';
}
view[start.r][start.c] = 'S';
view[goal.r][goal.c]   = 'G';
```
[View in main.cpp — lines 7–19](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/main.cpp#L7-L19)
````








 
**Heuristic path method:**

This is the method i used in my Astar algorithm it is easy and lightweight to run compared to other methods.

Advantages: It excels in short sized testing. 


**Disadvantages:**

But falls short in larger algorithims as it will It will find the path but wastes time exploring cells that are going in the wrong direction.
With a heuristic, the algorithm has a sense of direction — it knows which cells are roughly closer to the goal and explores those first.

High Memory in larger models as data is stored in nodes and can 

Overhead of Heuristic Calculation while Calculating heuristics especially complex ones adds extra sometimes uneeded computation power being used at each node.



**Heuristic alternatives** Dijkstra's Algorithm, Breadth-First Search (BFS), Rapidly-exploring Random Tree (RRT).



**Manhattan:**

Manhattan distance measures the distance between two points along axes at right angles.

<img src="https://tse2.mm.bing.net/th/id/OIP.bXgaBczDZcXPA3qr91lsXwAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">

Here is an exmaple of how this works and is used in my code

````markdown
[View in AStar.h — line 53](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L53)
````

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20114240.png)

This code has an inline function (lambada function) in C++, thta gets a small function that takes a point and return distance to the goal.
it then measures the difference between rows and columns (dr & dc). From that we use the **Manhattan** heuristic type to get the distance.




**Euclidean:**

While Euclidean distance measures the straight-line distance between them.

<img src="https://tse2.mm.bing.net/th/id/OIP.HMw2dip3CqAMSZwbK2LiZQAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">

````markdown
[View in AStar.h — line 59](https://github.com/Liamnooneatu/A-Star-Algorithm/blob/main/AStar.h#L59)
````

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20115546.png)

In my code i am using Euclidean for straight line detection.






Why have i been using Manhattan and Euclidean and not something else like and RRT(Rapidly-exploring Random Tree):
When i asked ChatGPT this is what it said "The reason someone might use Manhattan Distance or Euclidean Distance instead of something like Rapidly-exploring Random Tree (RRT) usually comes down to the type of problem being solved."
In summary it told me that RRT would be too much and would be too overpowered for the gird finding i am using 

**Limitations & Reflections**
Code structure: The core algorithm logic lives in AStar.h (197 lines) rather than in main.cpp (103 lines). While this is unconventional — most C++ projects keep implementation logic out of header files — it did not cause any compilation or runtime issues across the three tests. In a production context, this would be refactored so that AStar.h contains only declarations and a separate AStar.cpp holds the implementation.


Hardcoding: The grid configurations for all three test cases are hardcoded. This is acceptable for demonstration purposes but would need to be replaced with file-based or user-driven input for a more flexible system.


Scalability: Manhattan distance can explore unnecessary nodes on larger grids. Improvements could include weighted A* (to trade optimality for speed) or a more informed heuristic for specific grid shapes.

**"RRT would:**
**Produce non-optimal paths**
**Require random sampling**
**Be slower for simple grids"**


**A.I Usage Disclosure**

I used two AI tools during this project, for my code i recieved assistance and guidance from Claude 4.5 and Chatgpt 5.0,

Claude (claude.ai) assisted with code generation. Claude structured the implementation by placing the core algorithm in AStar.h rather than main.cpp, which differs from conventional C++ practice but did not affect correctness.
I used Claude for the code which it performed in a different method compared to what we would originally use. To keep a code neat and tidy a programmer would originally keep the main could in main.cpp instead of keeping my code in the header file which is what cluade decided to do. my AStar.h is 197 lines long while my manin is only 103 lines long, this has not seemed to have caused promblems when running the code so far but it is unsightly for an outside user to read the code.

All code was reviewed, tested, and validated by me before submission.


I used ChatGPT  for research specifically for research between Manhatten & Euclidean or a RRT which i researched online also and wanted to originally perform this as a second method to research search method differances (https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c). 
I also conducted independent research using the sources listed below.de was reviewed, tested, and validated by me before submission.

<img src="https://upload.wikimedia.org/wikipedia/commons/1/13/ChatGPT-Logo.png" alt="My Image" width="400">

<img src="https://cdn.mos.cms.futurecdn.net/SKg6HNSWUodnkPkLAJ8fA.jpg" alt="My Image" width="400">


Hardcoding disatvantages 


## S.T.A.R Write-Up

### Situation
Pathfinding is a core problem in computer science with applications in AI, robotics, and GPS navigation. I was tasked with implementing an creating an efficient grid-based pathfinding solution in C++ usinng manhatten and eucildean that could find the shortest route between two points while avoiding obstacles.

### Task
My goal was to implement the A* algorithm that could navigate a 2D grid from a start point to an end point, avoid blocked points, and be validated against distinct test configurations (3).

### Action
I implemented A* using an open list and closed list. At each step the node with the lowest `f(n) = g(n) + h(n)` is selected, where `g(n)` is the actual cost from start and `h(n)` is the heuristic estimate to goal. I implemented both Manhattan and Euclidean distance as heuristic options and designed three test grids to validate the solution.

### Result
All three test cases produced correct output. The algorithm found the shortest path in Test 1 and Test 2, and correctly reported no valid path in Test 3. The implementation is functional and demonstrates a solid understanding of heuristic search in C++.


````markdown
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
````

---
