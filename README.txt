File:    README.txt
Author:  Dillon Lohr
Date:    3 September 2014
Program: CS-1428 Exam

How to use:
| 1. Run 'make'.
| 2. Run './populate [NUM_ENTRIES] [MAX_CONNECTIONS] [DATA_SIZE]'.
| 3. (optional) Inspect generated 'populated-graph.txt'.
| 4. Run './graph'.
| 5. (optional) Inspect generated 'strongly-connected-components.txt'.
+------


In-depth:
| 1. Run 'make'.
| | - Compiles both 'populate.cpp' and 'graph.cpp'.
| | - Might also run:
| |   + 'make clean'      (deletes 'populate' and 'graph')
| |   + 'make clean-all'  (calls 'clean' and deletes 'populated-graph.txt' and
| |                        'strongly-connected-components.txt')
| +------
|
| 2. Run './populate [NUM_ENTRIES] [MAX_CONNECTIONS] [DATA_SIZE]'.
| | - Generates 'populated-graph.txt' with random information based on input.
| | - Optional input:
| |   + NUM_ENTRIES
| |     - The number of nodes to be generated.
| |     - Defaults to 100.
| |   + MAX_CONNECTIONS
| |     - The maximum number of directed connections each node may have.
| |     - Defaults to 10.
| |   + DATA_SIZE
| |     - The length of each node's data string.
| |     - Essentially irrelevant; meant to simulate some type of real data.
| |     - Defaults to 10.
| +------
|
| 3. (optional) Inspect generated 'populated-graph.txt'.
| | - Contains information about each generated node.
| | - id:data:c1,c2,...,cn
| +------
|
| 4. Run './graph'.
| | - Reads 'populated-graph.txt' and populates a directed graph.
| | - Calculates strongly connected components (SCC).
| |   + Uses Tarjan's algorithm.
| |   + en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
| | - Generates 'strongly-connected-components.txt'.
| | - Outputs to console the same information.
| +------
|
| 5. (optional) Inspect generated 'strongly-connected-components.txt'.
| | - Contains information about each group of SCC.
| | - The start of each SCC is labeled with '[Strongly Connected Components]'.
| | - Following is information about each node in the SCC.
| +------
+------


Example files:
| 'populated-graph.txt'
| | 7
| | 0:A:1
| | 1:B:3
| | 2:C:4
| | 3:D:0
| | 4:E:2
| | 5:F:
| | 6:G:5
| +------
|
| 'strongly-connected-components.txt'
| | [Strongly Connected Components]
| |     Node #3
| |     Data: D
| |     Connections: 0
| |     Node #1
| |     Data: B
| |     Connections: 3
| |     Node #0
| |     Data: A
| |     Connections: 1
| | [Strongly Connected Components]
| |     Node #4
| |     Data: E
| |     Connections: 2
| |     Node #2
| |     Data: C
| |     Connections: 4
| | [Strongly Connected Components]
| |     Node #5
| |     Data: F
| |     Connections:
| | [Strongly Connected Components]
| |     Node #6
| |     Data: G
| |     Connections: 5
| +------
+------
