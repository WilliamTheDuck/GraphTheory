# **Graph Theory**

> _This repository comprises a couple of stuff you will need in order to learn **Graph Theory**: functions use to operate, initialize graphs, and applications in finding paths, reconstructing the code architecture,... In each section, there will be a demonstration corresponded with that .c file of a specific algorithm as well as its applications._

#

### ***Basic Knowledge***
---

**[1] Set Up Operations**

+ Initialize graph
  
+ Adjacent edges check

+ Add edge

+ Degree

+ Neighbours

+ Read graph

+ Print graph

**[2] Types Of Graphs**
      
+ Undirected graph

+ Directed graph

+ Weighted graph

+ Multigraph 

+ Pseudograph

+ Subgraph

+ Induced graph

+ Trees & Forests

**[3] Transversal And Connectivity Of A Graph**
      
+ Depth First Search (DFS) using stack or recursion

    + Find cycle, Find connected components, Web crawler, Robot navigation, Flood filling/Seed filling in Image Processing, ...

+ Breadth First Search (BFS) using queue

    + Grid-based game, Knight shortest path, Eigth queens, Priests and devils, ...

+ Strongly Connected Components (SCC): Tarjan, Kosaraju

    + Find strongly related in social media, Module analyzing, ...

**[4] Cycle**

+ Three colours cycle detection 

    + Deadlock detection, Detect loops in dependency (npm, pip), Checking task assignment consistency, ...

+ Bipartite graph 

    + Exam scheduling without conflicts, Matching tasks, Two-coloring (hot/cold wires), ...

+ Eulerian path : Fleury, Hierholzer

    + Urban inspection route design, Electrical wiring inspection cycles, ...

+ Hamiltonian path

  + Travelling Salesman Problem, Bus tour planning, Designing circuits with no node repetition, ...
      
### ***Advanced Knowledge***
---

**[1] Shortest Path**

+ Moore - Dijkstra

    + GPS navigation in Google Maps, Network routing, Minimizing transportation cost, ...

+ Bellman - Ford

    + Detecting negative cycles – financial arbitrage, ...

+ Floyd - Warshall

    + All-pairs shortest paths for static routing tables, Centrality calculation, Social network analysis: compute distance between users, ...

+ A* 

    + AI pathfinding in games (Minecraft, Assassin’s Creed), Geographic heuristic pathfinding, Robot navigation in Amazon warehouses, ...

**[2] Topological Sort**

+ Kahn (BFS)

    + University course scheduling, Data processing pipeline analysis, CI/CD pipeline step ordering, ...

+ Graph Ranking

    + Developer task prioritization, ...

+ Project Management

    + Critical path detection, PERT/CPM project management, ...

**[3] Minimum Undirected Spanning Tree**

+ Kruskal

    + Cost-efficient telecom network design, Maze generation in games, Connecting residential areas with minimal cables, ...

+ Prim

    + Growing a road network from a central hub, ...

+ Boruvka

    + Suitable for large-scale, national network systems, ...

**[4] Minimum Directed Spanning Tree**

+ Chu - Liu / Edmonds

    + Designing optimal one-way street systems, Optimizing decision trees in AI systems, Building an internet backbone from a root router, ...

**[5] Maximum Flow**

+ Ford - Fulkerson (Edmonds - Karp)

    + Logistics flow (goods through warehouses), Water/oil/electricity pipeline systems, Internet bandwidth allocation, Maximum matching problems, Traffic flow optimization in cities, ...

+ Dinic (Dinitz)

    + Resource allocation (server ↔ job mapping), Matching on large graphs (Facebook, Twitter), High-speed max-flow for exam scheduling/job assignment/real-time data routing, ...

#

### ***Installation And Customization Library Guide***
---

> _To install and use my static library in your MSYS2/MinGW environment, follow these steps._

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


> _You can also customize these files as you prefer. Here are the steps you can follow to recreate your own static library._

- First, make your own `.c` file with  definitions (implementations) of functions. For instance:
```c
#include <stdio.h>
#include <string.h>
#include "DataStructure.h"

/* ================== LIST ================== */
void init_list(List* pL)
{
    pL->size = 0;
}
void append_list(List* pL, int x)
{
    pL->size++;
    pL->data[pL->size] = x;
}
```
- Worthy noticing that you also need to have this line in the `.c` file.
```c
#include "DataStructure.h"
```
- After that, we make a header file with the same name of the `DataStructure.c` file (`DataStructure.h`). This header file will include the declarations of mentioned functions in the `.c` file.
```c
#ifndef DATA_STRUCTURE_SETUP_H
#define DATA_STRUCTURE_SETUP_H

#define MAX 200

/* ================== LIST ================== */
typedef struct
{
    int data[MAX];
    int size;
} List;

void init_list(List* pL); // Initializes pL->size to 0
void append_list(List* pL, int x);

#endif /* DATA_STRUCTURE_SETUP_H */
```
- `#ifndef` means _"if not defined"_ and `#endif` stands for _"end if"_. A primary use of `#ifndef` is to prevent multiple inclusions of header files, a technique called _"header guarding"_. 

- The next step is making an object `.o` file of `.c` file (you should name it the same). Change the directory containing your `.c` file in shell to use the below command. 
```shell
cd <"Your directory containing the .c file">
gcc -c -Wall -g <Your file name>.c -o <Your file name>.o
```
- Last but not least, make a static library with this command. Name your library `lib<Name>.a`.
```shell
ar rcs <lib___>.a <Object file>.o
```
- Copy the header file `.h` to `include` and `lib...a` to `lib` as I meantioned above with shell commands or manually like the above steps.
```shell
xcopy /Y DataStructure.h C:\msys64\ucrt64\include
xcopy /Y libdatastructure.a C:\msys64\ucrt64\lib
```
For example:
```shell
cd "D:\CODE C\DataStructure-Library"
D:\CODE C\DataStructure-Library> gcc -c -Wall -g DataStructure.c -o DataStructure.o
D:\CODE C\DataStructure-Library> ar rcs libdatastructure.a DataStructure.o
xcopy /Y DataStructure.h C:\msys64\ucrt64\include
xcopy /Y libdatastructure.a C:\msys64\ucrt64\lib
```

### ***Autofill Section Header In Code Guide***
---

> _To make code files more structured and readable, we can use VSCode user snippets to quickly insert section headers with different divider styles._

- Copy `sectioncomment.code-snippets` and put it in your `.vscode` folder.

- Usage: In any `.c` or `.h` file, just type the prefix (`sec`, `sdc`, or `ssc`) and press `Tab`.
It will automatically expand into a section header with a placeholder for you to type in the section name.

  Eg: type "sec" and a `Tab`, it will be like this:
```c
/* ==================  ================== */
```
