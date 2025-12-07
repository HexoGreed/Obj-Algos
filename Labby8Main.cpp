/*
Hamza S


QA:

1. How many walls separate the cells of an NxN grid: 
    
	2N(N-1) (there are n(n-1) vertical and n(n-1) horizontal walls)


2. Given an NxN maze with no cycles (a perfect maze), how many walls separate the cells?
    (N-1)^2 (A perfect maze is a tree with n^2 nodes meaning it has N^2 -1 edges, 
    you subtract these from the total # of walls).


3. What is the runtime complexity of the find operation of the disjoint set data structure?


	O(a(N^2)) where a is the inverse Ackermann function, which grows very slowly.



4. without a detailed analysis, how might we generalize the runtime complexity of the find operation?

    O(1), because the parent array stores the cells by index and path compression it flatends the tree
	structure. looking up a paent becomes almost instant.


5.Why do the paths created when generating a maze represent a minimum spanning tree?

    because kruskals algo connects every single cell without creaing any loops using the 
	minimum number of edges possible.

*/






















#include "Labby8.h"

vector<int> adj[rows * cols];

int main() {
    srand(time(0));

    generateMaze();

    printMaze("maze.maz");
    cout << "Maze generated to maze.maz" << endl;

    vector<bool> visited(rows * cols, false);
    vector<int> path;

    if (solveMaze(0, rows * cols - 1, visited, path)) {
        printMaze("maze_solved.maz", path);
        cout << "Maze solved to maze_solved.maz" << endl;
    }
    else {
        cout << "No solution avaliable" << endl;
    }

    return 0;
}