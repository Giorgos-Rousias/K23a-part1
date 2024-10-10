#include <iostream>
#include "../../include/core/graph.hpp"

using namespace std;

int main() {
    string filename;

    filename = "./siftsmall/siftsmall_base.fvecs";

    Graph g = Graph(filename, 6);

    g.printGraph();

    return 0;
}
