#ifndef CUTHILL_MCKEE
#define CUTHILL_MCKEE

#include <list>
#include <queue>
#include <vector>

bool compare(const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) {
  return a.second < b.second;
}

void cuthill_mckee(const std::vector<std::vector<double> >& A, std::vector<size_t>& ordering,
         size_t root) {
  size_t n = A.size();
  std::queue<size_t> Q;
  std::vector<bool> visited(n, false);
  ordering.reserve(n);
  ordering.resize(0);

  std::vector<size_t> adj(n);
  for (size_t v = 0; v < n; v++)
    for (size_t i = 0; i < n; i++)
      if (std::abs(A[v][i]) > 0.0) adj[v]++;

  Q.push(root);
  visited[root] = true;
  ordering.push_back(root);
  while (!Q.empty()) {
    size_t node = Q.front();
    std::list<std::pair<size_t, size_t> > candidates;
    for (size_t i = 0; i < n; i++) {
      if (!visited[i] && std::abs(A[node][i]) > 0.0) {
        candidates.push_back(std::make_pair(i, adj[i]));
      }
    }
    candidates.sort(compare);
    for (std::list<std::pair<size_t, size_t> >::iterator i = candidates.begin();
         i != candidates.end(); ++i) {
      Q.push(i->first);
      visited[i->first] = true;
      ordering.push_back(i->first);
    }
    Q.pop();
  }
  if (ordering.size() < n) {
    std::cout << "The underlying graph is not connected." << std::endl;
  }
}

#endif