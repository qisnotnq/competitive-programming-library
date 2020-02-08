#include <functional> // std::greater
#include <queue> // std::priority_queue
#include <utility> // std::pair
#include <vector> // std::vector

#include "non_standard.cpp"

template <class Graph>
std::vector<non_standard<typename Graph::edge_type::weight_type>> dijkstra(const Graph &g, size_t start) {
    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;
    using ExtendedWeight = non_standard<Weight>;
    using P = std::pair<Weight, size_t>;

    std::vector<ExtendedWeight> dp(g.n_vertices(), ExtendedWeight::pos_inf());

    std::priority_queue<P, std::vector<P>, std::greater<P>> q;

    dp[start] = ExtendedWeight(0);
    q.emplace(dp[start].value, start);

    while (!q.empty()) {
        Weight w0;
        size_t v0;
        tie(w0, v0) = q.top();
        q.pop();

        if (dp[v0].value < w0)
            continue;

        for (const Edge &e: g.edges_from(v0)) {
            size_t v1 = e.to();
            Weight w1 = w0 + e.weight();
            if (dp[v1].is_pos_inf() || dp[v1].value > w1) {
                dp[v1] = w1;
                q.emplace(dp[v1].value, v1);
            }
        }
    }

    return dp;
}
