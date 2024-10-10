#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Graph {
private:
    int V;  // Number of vertices

    // Helper methods
    template <typename T>
    void print(const vector<T>& vec);

    void readFile(const string& filename);
    void addEdge(int u, int v);
    void randomGraphGenerator(const int R);

public:
    vector<vector<int>> adjList;  // Adjacency list for unweighted graph

    vector<vector<unsigned char>> baseVectors;  // For .bvecs format
    vector<vector<float>> queryVectors;  // For .fvecs format
    vector<vector<int>> learningVectors; // For .ivecs format

    Graph(const string& filename, const int R = 5);
    void printGraph();
    void printVectors();
};

#endif
