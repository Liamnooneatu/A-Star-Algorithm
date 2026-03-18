This is my github pages.


**Heuristic path method:**

It will find the path but wastes time exploring cells that are going in the wrong direction.
With a heuristic, the algorithm has a sense of direction — it knows which cells are roughly closer to the goal and explores those first.



**Heuristic alternatives** Dijkstra's Algorithm, Breadth-First Search (BFS), Rapidly-exploring Random Tree (RRT).



**Manhattan:**

Manhattan distance measures the distance between two points along axes at right angles.

<img src="https://tse2.mm.bing.net/th/id/OIP.bXgaBczDZcXPA3qr91lsXwAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">

Here is an exmaple of how this works and is used in my code

https://github.com/Liamnooneatu/A-Star-Algorithm/blob/bde480daadf8f51d7cb8b3a9aaeee3f4c94917f9/AStar.h#L87

![My Photo](https://raw.githubusercontent.com/Liamnooneatu/A-Star-Algorithm/blob/main/Screenshot%202026-03-18%20114240.png)

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

**"RRT would:**
**Produce non-optimal paths**
**Require random sampling**
**Be slower for simple grids"**


**A.I Usage**
For my code i recieved assistance and guidance from Claude 4.5 and Chatgpt 5.0, i used chatgpt for research between manhatten + euclidean or a RRT which i researched online also and wanted to originally perform this as a second method to research search method differances (https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c). I used Claude for the code which it performed in a different method compared to what we would originally use. To keep a code neat and tidy a programmer would originally keep the main could in main.cpp instead of keeping my code in the header file which is what cluade decided to do. my AStar.h is 197 lines long while my manin is only 103 lines long, this has not seemed to have caused promblems when running the code so far but it is unsightly for an outside user to read the code.

<img src="https://upload.wikimedia.org/wikipedia/commons/1/13/ChatGPT-Logo.png" alt="My Image" width="400">

<img src="https://cdn.mos.cms.futurecdn.net/SKg6HNSWUodnkPkLAJ8fA.jpg" alt="My Image" width="400">


Github Pages created using the S.T.A.R method.
1. Situation
2. Task
3. Action
4. Result


**References:** 
https://stackoverflow.com/questions/36026464/rrt-algorithm-in-c
https://en.wikipedia.org/wiki/Euclidean_algorithm
https://www.youtube.com/watch?v=i0x5fj4PqP4
https://www.youtube.com/watch?v=ySN5Wnu88nE
https://www.geeksforgeeks.org/dsa/a-search-algorithm/
https://chatgpt.com
https://claude.ai
https://en.wikipedia.org/wiki/Heuristic_(computer_science)
https://mljourney.com/manhattan-distance-vs-euclidean-distance-key-differences/
