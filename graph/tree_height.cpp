#include <functional> // std::function
#include <vector> // std::vector

template <class Graph>
std::vector<typename Graph::edge_type::weight_type> tree_height(const Graph &g) {
    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;

    const size_t n_vertices = g.n_vertices();
    const size_t NIL = n_vertices;

    std::vector<Weight> longests(n_vertices);
    std::vector<Weight> second_longests(n_vertices);

    std::function<Weight(size_t, size_t)> dfs_longest = [&](size_t u, size_t parent) {
        Weight longest = 0;
        Weight second_longest = 0;
        for (Edge e: g.edges_from(u)) {
            size_t v = e.to();
            if (v == parent) {
                continue;
            }
            Weight weight = e.weight();
            Weight length = weight + dfs_longest(v, u);
            if (longest < length) {
                second_longest = longest;
                longest = length;
            } else if (second_longest < length) {
                second_longest = length;
            }
        }
        second_longests[u] = second_longest;
        return longests[u] = longest;
    };

    dfs_longest(0, NIL);

    std::vector<Weight> heights(n_vertices);

    std::function<void(size_t, size_t, Weight)> dfs_height = [&](size_t u, size_t parent, Weight parent_longest) {
        for (Edge e: g.edges_from(u)) {
            size_t v = e.to();
            if (v == parent) {
                continue;
            }
            Weight weight = e.weight();
            Weight length = weight + longests[v];
            Weight sibling_longest = weight + longests[v] == longests[u] ? second_longests[u] : longests[u];
            dfs_height(v, u, weight + max(parent_longest, sibling_longest));
        }
        heights[u] = max(longests[u], parent_longest);
    };

    dfs_height(0, NIL, 0);

    return heights;
}
