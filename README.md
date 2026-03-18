This is my github pages.


**Heuristic path method:**

It will find the path but wastes time exploring cells that are going in the wrong direction.
With a heuristic, the algorithm has a sense of direction — it knows which cells are roughly closer to the goal and explores those first.



**Heuristic alternatives** Dijkstra's Algorithm, Breadth-First Search (BFS), Rapidly-exploring Random Tree (RRT).



**Manhattan:**

Manhattan distance measures the distance between two points along axes at right angles.

<img src="https://tse2.mm.bing.net/th/id/OIP.bXgaBczDZcXPA3qr91lsXwAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">

Here is an exmaple of how this works and is used in my code




**Euclidean:**

While Euclidean distance measures the straight-line distance between them.


<img src="https://tse2.mm.bing.net/th/id/OIP.HMw2dip3CqAMSZwbK2LiZQAAAA?cb=thfvnext&rs=1&pid=ImgDetMain&o=7&rm=3" alt="My Image" width="400">



Why have i been using Manhattan and Euclidean and not something else like and RRT(Rapidly-exploring Random Tree):
When i asked ChatGPT this is what it said "The reason someone might use Manhattan Distance or Euclidean Distance instead of something like Rapidly-exploring Random Tree (RRT) usually comes down to the type of problem being solved."
In summary it told me that RRT would be too much and would be too overpowered for the gird finding i am using 

**"RRT would:**
**Produce non-optimal paths**
**Require random sampling**
**Be slower for simple grids"**


**A.I Usage**
For my code i recieved assistance and guidance from Claude 4.5 and Chatgpt 5.0,

<img src="[data:image/png;base64,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](https://www.internetmatters.org/wp-content/uploads/2025/06/Chat-GPT-logo.webp)" alt="My Image" width="400">

<img src="https://cdn.mos.cms.futurecdn.net/SKg6HNSWUodnkPkLAJ8fA.jpg" alt="My Image" width="400">


Github Pages created using the S.T.A.R method.
1. Situation
2. Task
3. Action
4. Result


**References:** 
https://en.wikipedia.org/wiki/Euclidean_algorithm
https://www.youtube.com/watch?v=i0x5fj4PqP4
https://www.youtube.com/watch?v=ySN5Wnu88nE
https://www.geeksforgeeks.org/dsa/a-search-algorithm/
https://chatgpt.com
https://claude.ai
https://en.wikipedia.org/wiki/Heuristic_(computer_science)
https://mljourney.com/manhattan-distance-vs-euclidean-distance-key-differences/
