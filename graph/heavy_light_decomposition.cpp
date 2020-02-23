#ifndef HEAVY_LIGHT_DECOMPOSITION_CPP
#define HEAVY_LIGHT_DECOMPOSITION_CPP

#include <functional> // std::function
#include <vector> // std::vector

#include "range_query/segment_tree.cpp"

template <class Graph>
struct heavy_light_decomposition {
    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;

    std::vector<size_t> branch_vertices;
    std::vector<size_t> pos;
    std::vector<size_t> pos_end;
    std::vector<size_t> depth;
    segment_tree<Weight> seg_tree;
    const size_t NIL;

    heavy_light_decomposition(const Graph &g, size_t root) : seg_tree(g.n_vertices, 0, [](Weight x, Weight y) { return x + y; }), NIL(g.n_vertices) {
        size_t n_vertices = g.n_vertices;
        std::vector<size_t> sizes(n_vertices);
        std::vector<size_t> heavy_children(n_vertices);
        branch_vertices.resize(n_vertices);
        pos.resize(n_vertices);
        pos_end.resize(n_vertices);
        depth.resize(n_vertices);

        std::function<size_t(size_t, size_t)> dfs = [&](size_t v, size_t parent) {
            sizes[v] = 1;
            heavy_children[v] = NIL;
            size_t child_size_max = 0;
            for (const Edge &e: g.edges_from(v)) {
                size_t child = e.to();
                if (child == parent) {
                    continue;
                }
                dfs(child, v);
                sizes[v] += sizes[child];
                if (child_size_max < sizes[child]) {
                    child_size_max = sizes[child];
                    heavy_children[v] = child;
                }
            }
            return sizes[v];
        };

        dfs(root, NIL);

        size_t cur_pos = n_vertices;

        std::function<void(size_t, size_t, size_t, size_t)> decompose = [&](size_t v, size_t parent, size_t bv, size_t ep) {
            branch_vertices[v] = bv;
            pos[v] = --cur_pos;
            pos_end[v] = ep;
            if (heavy_children[v] != NIL) {
                decompose(heavy_children[v], v, bv, ep);
            }
            for (const Edge &e: g.edges_from(v)) {
                size_t child = e.to();
                if (child != parent && child != heavy_children[v]) {
                    decompose(child, v, v, cur_pos);
                }
            }
        };

        decompose(root, n_vertices, n_vertices, n_vertices);
    }

    void update(size_t v, Weight w) {
        seg_tree.update(pos[v], w);
    }

    Weight query(size_t v) const {
        Weight result = 0;
        do {
            result += seg_tree.query(pos[v], pos_end[v]);
        } while ((v = branch_vertices[v]) != NIL);
        return result;
    }
};

#endif // HEAVY_LIGHT_DECOMPOSITION_CPP
