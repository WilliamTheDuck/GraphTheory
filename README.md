# **Graph Theory**

> _This repository comprises a couple of stuff you will need in order to learn **Graph Theory**: functions use to operate, initialize graphs, and applications in finding paths, reconstructing the code architecture,... In each section, there will be a demonstration corresponded with that .c file of a specific algorithm as well as its applications._

#

### ***Basic Knowledge***
---

[1] Set Up Basic Operations

      + Initialize graph

      + Adjacent edges check

      + Add edge

      + Degree

      + Neighbors

      + Read graph

      + Print graph

[2] Special Types Of Graphs
      
      + Undirected graph

      + Directed graph

      + Weighted graph

      + Multigraph 

      + Pseudograph

      + Subgraph

      + Induced graph

      + Trees & Forests

[3] Transversal And Connectivity Of A Graph
      
      + Depth First Search (DFS) using stack

      + Depth First Search (DFS) using recursion

      + Breadth First Search (BFS) using queue

      + Tarjan to find Strongly Connected Components (SCC)

      + Erdos - Gallai

      + Bipartite graph & 2-colors check

      + Eulerian trail 

      + Hamiltonian path 

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

#

### ***Installation Library Guide***
---

> _To install and use this custom static library in your `MSYS2/MinGW` environment, follow these steps._

- Copy the header file (`DataStructure.h`) and place it into the global include directory:  
```
C:\msys64\ucrt64\include
```

- Copy the compile static library (`libdatastructure.a`) and place it into the global library directory:  
```
C:\msys64\ucrt64\lib
```

- Usage in your project: Include the header as if it were a system library:  
```c
#include <DataStructure.h>
```

- When compiling, link against the static library by adding `-ldatastructure`: The prefix lib and the suffix .a are omitted when using the -l option. For example, `-ldatastructure` links against `libdatastructure.a`. Notice that you also need to replace your own file names `main.c` and `main.exe` accordingly.
```shell
gcc main.c -ldatastructure -o main.exe
```
- Or we could insert `-ldatastructure` before the `-o` in `args`-`tasks.json` (in `.vscode` folder). In that way, we simply push `f5` to debug without inserting the line above into the terminal.
```json
"args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-ldatastructure",
        "-o",
        "${fileDirname}\\${fileBasenameNoExtension}.exe"
      ],
```

### ***Autofill Section Header In Code Guide***
---

> _To make code files more structured and readable, we can use VSCode user snippets to quickly insert section headers with different divider styles._

- Copy `sectioncomment.code-snippets` and put it in your `.vscode` folder.

- Usage: In any `.c` or `.h` file, just type the prefix (`sec`, `sdc`, or `ssc`) and press `Tab`.
It will automatically expand into a section header with a placeholder for you to type in the section name. Ex: type "sec" and a `Tab`, it will be like this:
```c
/* ==================  ================== */
```
