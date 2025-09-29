# **Graph Theory**

> _This repository comprises a couple of stuff you will need in order to learn _Graph Theory_: functions use to operate, initialize graphs, and applications in finding paths, reconstructing the code architecture,... In each section, there will be a demonstration corresponded with that .c file of a specific algorithm as well as its applications._

### ***Basic Knowledge***
---

[1] Set up basic operations

      + Initialize graph

      + Adjacent edges check

      + Add edge

      + Degree

      + Neighbors

      + Read graph

      + Print graph

[2] Special types of graphs
      
      + Undirected graph

      + Directed graph

      + Weighted graph

      + Multigraph 

      + Pseudograph

      + Subgraph

      + Induced graph

      + Trees & Forests

[3] Connectivity of a graph
      
      + Depth First Search (DFS) using stack

      + Depth First Search (DFS) using recursion

      + Breadth First Search (BFS) using queue

      + Tarjan to find Strongly Connected Components (SCC)

### ***Intermediate Knowledge***
---

[1] Erdos - Gallai

[2] Bipartite graph & 2-colors check

[3] Eulerian trail 

[4] Hamiltonian path 

### ***Advanced Knowledge***
---

[1] Shortest Path

      + Moore - Dijkstra

      + Bellman - Ford

      + Floyd - Warshall

      + A* (Heuristic)

[2] Topological Sort

      + Topological sort

      + DFS & Kahn

[3] Minimum Undirected Spanning Tree

      + Kruskal

      + Prim

      + Boruvka

[4] Minimum Directed Spanning Tree

      + Chu - Liu

      + Edmonds

[5] Maximum Flow

      + Ford - Fulkerson

      + Edmonds - Karp

      + Dinic

### ***Installation Library Guide***
---

> _To install and use this custom static library in your `MSYS2/MinGW` environment, follow these steps:_

[1] Copy the header file (`DataStructureSetUp.h`) and place it into the global include directory:  

      C:\msys64\ucrt64\include


[2] Copy the compile static library (`libgraph.a`) and place it into the global library directory:  

      C:\msys64\ucrt64\lib


[3] Usage in your project: Include the header as if it were a system library:  
```c
#include <DataStructureSetUp.h>
```

[4] When compiling, link against the static library by adding `-lgraph`: The prefix lib and the suffix .a are omitted when using the -l option. For example, `-lgraph` links against `libgraph.a`.
```shell
gcc main.c -lgraph -o main.exe
```
Or we could insert `-lgraph` before the `-o` in `args`-`tasks.json` (in `.vscode` folder). In that way, we simply push `f5` to debug without inserting the line above into the terminal.
```json
"args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-lgraph",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe"
      ],
```