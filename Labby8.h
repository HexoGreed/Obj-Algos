#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>
#include <ctime>

using namespace std;


const int rows = 20;
const int cols = 20;



//had ot put extern here to stop errors for double decleration
extern vector<int> adj[rows * cols];



struct edge {
    int i, j;
};





// Helper to get 1D index
inline int getID(int i, int j) {
    return i * cols + j;
}








//disjoint set


class DisjointSet {
    vector<int> parent;
    vector<int> rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // Fill 0 to n-1
        rank.assign(n, 0);
    }

    int find(int i) {
        if (parent[i] != i)
            parent[i] = find(parent[i]); // Path compression
        return parent[i];
    }

    void unionSets(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            // Union by rank
            if (rank[rootI] < rank[rootJ])
                parent[rootI] = rootJ;
            else if (rank[rootI] > rank[rootJ])
                parent[rootJ] = rootI;
            else {
                parent[rootI] = rootJ;
                rank[rootJ]++;
            }
        }
    }
};



inline void generateMaze() {
    vector<edge> edges;

    // 1. Create all possible edges
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int u = getID(r, c);


            if (c < cols - 1) {
                edges.push_back({ u, getID(r, c + 1) });
            }// Right


            if (r < rows - 1) {
                edges.push_back({ u, getID(r + 1, c) });
            }// Down
        }
    }


    //  Shuffle edges
    shuffle(edges.begin(), edges.end(), default_random_engine(time(0)));

    // Kruskal algo
    DisjointSet ds(rows * cols);

    for (const auto& e : edges) {
        if (ds.find(e.i) != ds.find(e.j)) {
            ds.unionSets(e.i, e.j);

            // Remove wall
            adj[e.i].push_back(e.j);
            adj[e.j].push_back(e.i);
        }
    }
}







//solve maze

inline bool solveMaze(int u, int target, vector<bool>& visited, vector<int>& path) {
    if (u == target) {
        path.push_back(u);
        return true;
    }

    visited[u] = true;
    path.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (solveMaze(v, target, visited, path)) return true;
        }
    }

    path.pop_back(); // Backtrack
    return false;
}




//filepath

 inline void printMaze(string filename, const vector<int>& solutionPath = {}) {
    ofstream outFile(filename);

    // Setup lookup for solution path for fast checking
    vector<bool> inPath(rows * cols, false);
    for (int id : solutionPath) inPath[id] = true;

    // Top Border
    for (int c = 0; c < cols; c++) outFile << "+-";
    outFile << "+" << endl;

    for (int r = 0; r < rows; r++) {
        outFile << "|"; // Left edge
        for (int c = 0; c < cols; c++) {
            int curr = getID(r, c);

            // Determine content (Start, End, Path, or Empty)
            if (r == 0 && c == 0) outFile << "S";
            else if (r == rows - 1 && c == cols - 1) outFile << "E";
            else if (inPath[curr]) outFile << "~";
            else outFile << " ";

            // Check right wall
            bool connectedRight = false;
            int right = getID(r, c + 1);
            if (c < cols - 1) {
                for (int neighbor : adj[curr]) {
                    if (neighbor == right) connectedRight = true;
                }
            }
            outFile << (connectedRight ? " " : "|");
        }
        outFile << endl;

        // Bottom walls
        outFile << "+";
        for (int c = 0; c < cols; c++) {
            int curr = getID(r, c);
            bool connectedDown = false;
            int down = getID(r + 1, c);

            if (r < rows - 1) {
                for (int neighbor : adj[curr]) {
                    if (neighbor == down) connectedDown = true;
                }
            }
            outFile << (connectedDown ? " " : "-") << "+";
        }
        outFile << endl;
    }
    outFile.close();
}