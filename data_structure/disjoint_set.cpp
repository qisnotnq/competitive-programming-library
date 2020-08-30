#include <vector> // std::vector

using namespace std;

class disjoint_set {
private:
    // if vertex i is a root, r[i] = -(size of the component),
    // eles r[i] = root of i.
    std::vector<int> r;
public:
    const size_t n_vertices;
    size_t n_components;

    disjoint_set(size_t n_vertices) : n_vertices(n_vertices), n_components(n_vertices), r(n_vertices, -1) { }

    size_t root(size_t x) {
        if (r[x] < 0) {
            return x;
        } else {
            return r[x] = root(r[x]);
        }
    }

    void merge(size_t x, size_t y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return;
        }
        if (r[x] < r[y]) {
            r[x] += r[y];
            r[y] = r[x];
        } else {
            r[y] += r[x];
            r[x] = r[y];
        }
        --n_components;
    }

    bool is_same(size_t x, size_t y) {
        return root(x) == root(y);
    }

    size_t component_size(size_t x) {
        return -r[root(x)];
    }
};
