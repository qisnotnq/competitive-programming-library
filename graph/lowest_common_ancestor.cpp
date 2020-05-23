#include <functional> // std::function
#include <vector> // std::vector

// N > 1
class lowest_common_ancestor {

    size_t log2_N; // ceil(log2(N))
    std::vector<std::vector<size_t>> parent;
    std::vector<size_t> depth;

    size_t n_th_parent(size_t u, size_t n) {
        for (size_t i = 0; (1 << i) <= n; ++i) {
            if (n & (1 << i)) {
                u = parent[u][i];
            }
        }
        return u;
    }

public:

    // g is a tree
    template <class Graph>
    lowest_common_ancestor(const Graph &g, size_t root) {

        using Edge = typename Graph::edge_type;

        size_t N = g.n_vertices();
        log2_N = 32 - __builtin_clz(N - 1);
        
        parent.assign(N, std::vector<size_t>(log2_N));
        depth.resize(N);

        std::function<void(int, int)> dfs = [&](int u, int p) {
            for (const Edge &e: g.edges_from(u)) {
                size_t v = e.to();
                if (v == p) {
                    continue;
                }
                parent[v][0] = u;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        };

        parent[root][0] = root;
        depth[root] = 0;
        dfs(root, root);

        for (size_t i = 1; i < log2_N; ++i) {
            for (size_t u = 0; u < N; ++u) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
        }
    }

    size_t query(size_t u, size_t v) {
        if (depth[u] > depth[v]) {
            u = n_th_parent(u, depth[u] - depth[v]);
        } else if (depth[v] > depth[u]) {
            v = n_th_parent(v, depth[v] - depth[u]);
        }
        if (u == v) {
            return u;
        }
        for (int i = log2_N - 1; i >= 0; --i) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }
};
