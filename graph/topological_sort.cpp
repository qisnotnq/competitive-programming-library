#include <queue> // std::queue
#include <vector> // std::vector

// if g has a cycle, return empty vector.
// Time complexity is O(V + E),
// where V is the number of vertices,
//       E is the number of edges.
template <class Graph>
std::vector<size_t> topological_sort(const Graph &g) {

    using Edge = typename Graph::edge_type;

    std::vector<size_t> topological_orders(g.n_vertices());
    std::vector<size_t> indegrees(g.n_vertices());

    for (size_t v = 0; v < g.n_vertices(); ++v) {
        for (const Edge &e: g.edges_from(v)) {
            ++indegrees[e.to()];
        }
    }

    std::queue<size_t> q;

    for (size_t v = 0; v < g.n_vertices(); ++v) {
        if (!indegrees[v]) {
            q.push(v);
        }
    }

    for (size_t i = 0; i < g.n_vertices(); ++i) {
        if (q.empty()) { // has cycle
            return { };
        }
        size_t u = q.front();
        q.pop();
        topological_orders[i] = u;
        for (const Edge &e: g.edges_from(u)) {
            size_t v = e.to();
            --indegrees[v];
            if (!indegrees[v]) {
                q.push(v);
            }
        }
    }

    return topological_orders;
}
