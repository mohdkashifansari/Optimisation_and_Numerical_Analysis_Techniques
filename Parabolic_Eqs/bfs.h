#ifndef BFS
#define BFS

#include <queue>
#include <vector>
#include <cmath>

void bfs(const std::vector<std::vector<double> > &A, std::vector<size_t> &ordering,
         size_t root) {
  size_t n = A.size();
  std::queue<size_t> Q;
  std::vector<bool> visited(n, false);
  ordering.reserve(n);
  ordering.resize(0);

  Q.push(root);
  visited[root] = true;
  ordering.push_back(root);
  while (!Q.empty()) {
    size_t node = Q.front();
    for (size_t i = 0; i < n; i++) {
      if (!visited[i] && std::abs(A[node][i]) > 0.0) {
        Q.push(i);
        visited[i] = true;
        ordering.push_back(i);
      }
    }
    Q.pop();
  }
  if (ordering.size() < n) {
    // What can we say about the graph/matrix in this situation?
  }
}

#endif