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

Code Anaylisis:




code




code





code





code







code






 
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

https://github.com/Liamnooneatu/A-Star-Algorithm/blob/bde480daadf8f51d7cb8b3a9aaeee3f4c94917f9/AStar.h#L87

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/main/Screenshot%202026-03-18%20114240.png)

This code has an inline function (lambada function) in C++, thta gets a small function that takes a point and return distance to the goal.
it then measures the difference between rows and columns (dr & dc). From that we use the **Manhattan** heuristic type to get the distance.




**Euclidean:**

While Euclidean distance measures the straight-line distance between them.

<img src="https://tse2.mm.bing.net/th/id/OIP.HMw2dip3CqAMSZwbK2LiZQAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">

https://github.com/Liamnooneatu/A-Star-Algorithm/blob/bde480daadf8f51d7cb8b3a9aaeee3f4c94917f9/AStar.h#L35

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


**Github Pages created using the S.T.A.R method.**

**1. Situation**

**2. Task**

**3. Action**

**4. Result**


**References:** 

StackOverflow: https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c

Wikipedia Euclidean algorithm: https://en.wikipedia.org/wiki/Euclidean_algorithm

Tarodev youtube video: https://www.youtube.com/watch?v=i0x5fj4PqP4

Useful computerphile video: https://www.youtube.com/watch?v=ySN5Wnu88nE

Geeks for Geeks search algorithm: https://www.geeksforgeeks.org/dsa/a-search-algorithm/

ChatGPT: https://chatgpt.com

Claude: https://claude.ai

Wikipedia Heuristic: https://en.wikipedia.org/wiki/Heuristic_(computer_science)

M1 Journey: https://mljourney.com/manhattan-distance-vs-euclidean-distance-key-differences/
