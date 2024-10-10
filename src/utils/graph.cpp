#include "../../include/core/graph.hpp"
#include "../../include/utils/vector_file_readers.hpp"

/**
 * @brief Prints a vector
 *
 * @tparam T The type of the vector components
 */
template <typename T>
void Graph::print(const vector<T>& vec) {
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

/**
 * @brief Reads vectors from a file
 *
 * @param filename The name of the file to read
 */
void Graph::readFile(const string& filename) {
    // Check if vectors are already populated
    if (!baseVectors.empty() || !queryVectors.empty() || !learningVectors.empty()) {
        cerr << "Vectors are already populated" << endl;
        return;
    }

    // Get the file extension and populate the corresponding vectors
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
 * @brief Adds an edge between two vertices
 *
 * @param u The first vertex
 * @param v The second vertex
 */
void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

/**
 * @brief Generates a random graph
 *
 * @param R The number of edges to generate for each vertex
 */
void Graph::randomGraphGenerator(const int R) {
    // Check if vectors are empty
    if (baseVectors.empty() && queryVectors.empty() && learningVectors.empty()) {
        cerr << "Vectors are empty" << endl;
        return;
    }

    // Get the number of vertices
    if (!baseVectors.empty()) {
        V = baseVectors.size();
    } else if (!queryVectors.empty()) {
        V = queryVectors.size();
    } else if (!learningVectors.empty()) {
        V = learningVectors.size();
    }

    // Generate random edges
    adjList.resize(V);
    for (int u = 0; u < V; ++u) {
        for (int i = 0; i < R; ++i) {
            // If the number of edges for a vertex is already R, break
            if (adjList[u].size() == static_cast<vector<int>::size_type>(R)) {
                break;
            }

            int v = rand() % V;

            // If the vertices are the same or the if target vertex already has R edges or the edge already exists, decrement i and continue
            if (u == v
                || adjList[v].size() == static_cast<vector<int>::size_type>(R)
                || find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end()) {
                --i;
                continue;
            }

            addEdge(u, v);
        }
    }
}

/**
 * @brief Constructor
 *
 * @param filename The name of the file to read
 * @param R The number of edges to generate for each vertex
 */
Graph::Graph(const string& filename, const int R) {
    readFile(filename);
    randomGraphGenerator(R);
}

/**
 * @brief Prints the graph
 */
void Graph::printGraph() {
    for (int u = 0; u < V; ++u) {
        cout << "Node " << u << " makes edges with:\n";
        for (const auto& v : adjList[u]) {
            cout << "  Node " << v << " - ";
        }
        cout << endl << "------------------------------------------------------------------------" << endl;
    }
}

/**
 * @brief Prints the vectors
 */
void Graph::printVectors() {
    // Print the non empty vectors

    if (!baseVectors.empty()) {
        for (const auto& vec : baseVectors) {
            print(vec);
        }
        return;
    }

    if (!queryVectors.empty()) {
        for (const auto& vec : queryVectors) {
            print(vec);
        }
        return;
    }

    if (!learningVectors.empty()) {
        for (const auto& vec : learningVectors) {
            print(vec);
        }
        return;
    }

    cout << "Vectors are empty" << endl;
}
