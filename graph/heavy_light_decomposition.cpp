#include <functional> // std::function
#include <vector> // std::vector

#include "graph.cpp"
#include "range_query/segment_tree.cpp"

template <class Graph>
struct heavy_light_decomposition {
    using Edge = typename Graph::edge_type;
    using Weight = typename Edge::weight_type;

    size_t n_vertices;
    size_t m_root;
    std::vector<size_t> sizes;
    std::vector<size_t> heavy_children;
    std::vector<size_t> branch_vertices;
    std::vector<size_t> pos;
    std::vector<size_t> pos_end;
    std::vector<size_t> depth;
    segment_tree<Weight> seg_tree;
    const size_t NIL;

    heavy_light_decomposition(const Graph &g, size_t root) : n_vertices(g.n_vertices()), m_root(root) , seg_tree(n_vertices, 0, [](Weight x, Weight y) { return x + y; }), NIL(n_vertices) {

        //cout << "heavylieght called" << endl;
        sizes.resize(n_vertices);
        heavy_children.resize(n_vertices);
        branch_vertices.resize(n_vertices);
        pos.resize(n_vertices);
        pos_end.resize(n_vertices);
        depth.resize(n_vertices);

        std::function<size_t(size_t, size_t)> dfs = [&](size_t v, size_t parent) {

            //printf("dfs(%d, %d) is called\n", v, parent);

            sizes[v] = 1;
            heavy_children[v] = NIL;
            size_t child_size_max = 0;

            for (const Edge &e: g.edges_from(v)) {
                size_t child = e.to();

                if (child == parent) continue;
                
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
            //printf("decompose(%d, parent=%d, branch_vertices=%d) is called\n", v, parent, bv);
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

        /*
        REP(i, n_vertices) {
            printf("sizes[%d] = %d\n", i, sizes[i]);
        }

        REP(i, n_vertices) {
            printf("heavy_children[%d] = %d\n", i, heavy_children[i]);
        }

        REP(i, n_vertices) {
            printf("branch_vertices[%d] = %d\n", i, branch_vertices[i]);
        }

        REP(i, n_vertices) {
            printf("pos[%d] = %d\n", i, pos[i]);
        }

        REP(i, n_vertices) {
            printf("pos_end[%d] = %d\n", i, pos_end[i]);
        }
        */
    }

    void update(size_t v, Weight w) {
        //printf("update vertex v = %d, pos[v] = %d\n", v, pos[v]);
        seg_tree.update(pos[v], w);
    }

    Weight query(size_t v) {
        Weight result = 0;
        do {
            //printf("vertex %d to %d, segment [%d, %d)\n", v, branch_vertices[v], pos[v], pos_end[v]);
            result += seg_tree.query(pos[v], pos_end[v]);
        } while ((v = branch_vertices[v]) != NIL);
        return result;
    }
};
