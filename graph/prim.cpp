#include <functional> // std::greater
#include <queue> // std::priority_queue
#include <utility> // std::pair
#include <vector> // std::vector

// Prim's algorithm
template <class Graph>
typename Graph::edge_type::weight_type minimum_spanning_tree(const Graph &g) {

    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;
    using P = std::pair<Weight, size_t>;

    size_t N = g.n_vertices();

    Weight result = 0;
    std::vector<bool> used(N, false);
    std::priority_queue<P, std::vector<P>, std::greater<P>> q;

    q.push(P(0, 0));

    while (!q.empty()) {
        Weight w;
        size_t u;
        tie(w, u) = q.top();
        q.pop();
        if (used[u]) {
            continue;
        }
        used[u] = true;
        result += w;
        for (const Edge &e: g.edges_from(u)) {
            size_t v = e.to();
            if (!used[v]) {
                q.push(P(e.weight(), v));
            }
        }
    }

    return result;
}
