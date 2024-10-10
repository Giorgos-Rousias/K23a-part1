#include <iostream>
#include <map>
#include <vector>
#include <algorithm>  // Include this for std::find
#include <cstdlib>

#include "../utils/vector_file_readers.hpp"

using namespace std;

class Graph {

    /**
     * @brief Print a vector
     *
     * @tparam T The type of the vector components
     */
    template <typename T>
    void print(const vector<T>& vec) {
        for (const auto& val : vec) {
            cout << val << " ";
        }
        cout <<  endl;
    }

    /**
     * @brief Read vectors from a file
     *
     * @param filename The name of the file to read
     */
    void readFile(const string& filename) {
        if(!baseVectors.empty() || !queryVectors.empty() || !learningVectors.empty()) {
            cerr << "Vectors are already populated" << endl;
            return;
        }

        string extension = filename.substr(filename.find_last_of(".") + 1);
        if (extension == "bvecs") {
            read_file_vecs(filename, baseVectors);
        } else if (extension == "fvecs") {
            read_file_vecs(filename, queryVectors);
        } else if (extension == "ivecs") {
            read_file_vecs(filename, learningVectors);
        } else {
            cerr << "Invalid file extension" << endl;
        }
    }

    /**
     * @brief Add an edge to the graph
     *
     * @param u The source vertex
     * @param v The destination vertex
     */
    void addEdge(int u, int v) {
        // Since we are implementing an undirected graph, we need to add edges in both directions
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    /**
     * @brief Generate a random graph
     *
     * @param R The number of edges for each vertex
     */
    void randomGraphGenerator(const int R) {
        if (baseVectors.empty() && queryVectors.empty() && learningVectors.empty()) {
            cerr << "Vectors are empty" << endl;
            return;
        }

        if (!baseVectors.empty()) {
            V = baseVectors.size();
        } else if (!queryVectors.empty()) {
            V = queryVectors.size();
        } else if (!learningVectors.empty()) {
            V = learningVectors.size();
        }

        adjList.resize(V);

        // Creates R random edges for each vertex so that the graph is R-regular
        for (int u = 0; u < V; ++u) {
            for (int i = 0; i < R; ++i) {
                // Checks to see how many vertices are already connected to u
                if (adjList[u].size() == static_cast<vector<int>::size_type>(R)) {
                    break;
                }

                int v = rand() % V;

                if (u == v) {
                    --i;
                    continue;
                }

                // Check to see if the edge already has the max number of edges
                if (adjList[v].size() == static_cast<vector<int>::size_type>(R)) {
                    --i;
                    continue;
                }

                // Checks if the edge already exists
                if (find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end()) {
                    --i;
                    continue;
                }

                addEdge(u, v);
            }
        }
    }

public:
    int V;  // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list for unweighted graph

    vector<vector<unsigned char>> baseVectors;  // For .bvecs format
    vector<vector<float>> queryVectors;  // For .fvecs format
    vector<vector<int>> learningVectors; // For .ivecs format


    /**
     * @brief Construct a new Graph object
     *
     * @param filename The name of the file to read
     * @param R The number of edges for each vertex
     */
    Graph(const string& filename, const int R = 5) {
        readFile(filename);
        randomGraphGenerator(R);
    }

    /**
     * @brief Print the graph
     */
    void printGraph() {
        for (int u = 0; u < V; ++u) {
            cout << "Node " << u << " makes edges with:\n";
            for (const auto& v : adjList[u]) {
                cout << "  Node " << v << " - ";
            }
            cout << endl << "------------------------------------------------------------------------" <<  endl;
        }
    }

    /**
     * @brief Print the vectors
     */
    void printVectors() {
        if (!baseVectors.empty() && queryVectors.empty() && learningVectors.empty()) {
            for (const auto& vec : baseVectors) {
                print(vec);
            }
            return;
        }
        if (baseVectors.empty() && !queryVectors.empty() && learningVectors.empty()) {
            for (const auto& vec : queryVectors) {
                print(vec);
            }
            return;
        }
        if (baseVectors.empty() && queryVectors.empty() && !learningVectors.empty()) {
            for (const auto& vec : learningVectors) {
                print(vec);
            }
            return;
        }
        cout << "Vectors are empty" << endl;
    }
};