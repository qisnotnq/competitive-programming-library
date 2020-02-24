#include <vector> // std::vector

using namespace std;

class disjoint_set {
private:
    std::vector<size_t> parents;
    std::vector<size_t> ranks;
    std::vector<size_t> component_sizes;
public:
    const size_t n_vertices;
    size_t n_components;

    disjoint_set(size_t n_vertices) : n_vertices(n_vertices), parents(n_vertices), ranks(n_vertices, 0), n_components(n_vertices), component_sizes(n_vertices, 1) {
        for (size_t i = 0; i < n_vertices; ++i) {
            parents[i] = i;
        }
    }

    size_t root(size_t x) {
        if (parents[x] == x) {
            return x;
        } else {
            return parents[x] = root(parents[x]);
        }
    }

    void merge(size_t x, size_t y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return;
        }
        if (ranks[x] < ranks[y]) {
            parents[x] = y;
            component_sizes[y] += component_sizes[x];
        } else {
            parents[y] = x;
            component_sizes[x] += component_sizes[y];
            if (ranks[x] == ranks[y]) {
                ++ranks[x];
            }
        }
        --n_components;
    }

    bool is_same(size_t x, size_t y) {
        return root(x) == root(y);
    }

    size_t component_size(size_t x) {
        return component_sizes[root(x)];
    }
};
