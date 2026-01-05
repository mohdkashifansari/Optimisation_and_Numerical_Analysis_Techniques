#include <iostream>
#include <vector>

// Include the BFS header
#include "bfs.h"

// Helper function to print a vector
void printOrdering(const std::vector<size_t> &ordering)
{
    for (size_t v : ordering) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

int main()
{
    // Example symmetric matrix (graph)
    std::vector<std::vector<double>> A = {
        {1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1} // disconnected node
    };

    std::vector<size_t> ordering;
    size_t root = 0;

    bfs(A, ordering, root);

    std::cout << "BFS ordering starting from node " << root << ":\n";
    printOrdering(ordering);

    if (ordering.size() < A.size()) {
        std::cout << "The graph is NOT connected.\n";
    } else {
        std::cout << "The graph is connected.\n";
    }

    return 0;
}
