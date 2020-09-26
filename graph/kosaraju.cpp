#include <algorithm> // std::fill
#include <functional> // std::function
#include <vector> // std::vector

template <class Graph>
Graph opposite_graph(const Graph &g) {

    using Edge = typename Graph::edge_type;

    size_t n = g.n_vertices();
    Graph g_op(n);
    for (size_t u = 0; u < n; ++u) {
        for (Edge e: g.edges_from(u)) {
            size_t v = e.to();
            e.m_to = u;
            g_op.add_edge(v, e);
        }
    }
    return g_op;
}

template <class Graph>
std::vector<size_t> kosaraju(const Graph &g) {

    using Edge = typename Graph::edge_type;

    size_t n = g.n_vertices();
    std::vector<bool> used(n, false);

    std::vector<size_t> post_order;
    std::function<void(size_t)> post_order_traversal = [&](size_t u) {
        used[u] = true;
        for (const Edge &e: g.edges_from(u)) {
            size_t v = e.to();
            if (!used[v]) {
                post_order_traversal(v);
            }
        }
        post_order.push_back(u);
    };
    for (size_t u = 0; u < n; ++u) {
        if (!used[u]) {
            post_order_traversal(u);
        }
    }

    Graph g_op = opposite_graph(g);
    std::vector<size_t> components(n, n);
    size_t n_components = 0;
    std::function<void(size_t)> dfs = [&](size_t u) {
        components[u] = n_components;
        used[u] = true;
        for (const Edge &e: g_op.edges_from(u)) {
            size_t v = e.to();
            if (!used[v]) {
                dfs(v);
            }
        }
    };
    std::fill(used.begin(), used.end(), false);
    for (int i = n - 1; i >= 0; --i) {
        size_t u = post_order[i];
        if (!used[u]) {
            dfs(u);
            ++n_components;
        }
    }

    return components;
}

template <class Graph>
std::vector<std::vector<size_t>> kosaraju2(const Graph &g) {

    using Edge = typename Graph::edge_type;

    size_t n = g.n_vertices();
    std::vector<bool> used(n, false);

    std::vector<size_t> post_order;
    std::function<void(size_t)> post_order_traversal = [&](size_t u) {
        used[u] = true;
        for (const Edge &e: g.edges_from(u)) {
            size_t v = e.to();
            if (!used[v]) {
                post_order_traversal(v);
            }
        }
        post_order.push_back(u);
    };
    for (size_t u = 0; u < n; ++u) {
        if (!used[u]) {
            post_order_traversal(u);
        }
    }

    Graph g_op = opposite_graph(g);
    std::vector<std::vector<size_t>> scc;
    std::function<void(size_t)> dfs = [&](size_t u) {
        scc.back().push_back(u);
        used[u] = true;
        for (const Edge &e: g_op.edges_from(u)) {
            size_t v = e.to();
            if (!used[v]) {
                dfs(v);
            }
        }
    };
    std::fill(used.begin(), used.end(), false);
    for (int i = n - 1; i >= 0; --i) {
        size_t u = post_order[i];
        if (!used[u]) {
            scc.push_back(std::vector<size_t>());
            dfs(u);
        }
    }

    return scc;
}
