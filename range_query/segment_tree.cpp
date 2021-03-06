#ifndef SEGMENT_TREE_CPP
#define SEGMENT_TREE_CPP

#include <functional> // std::function
#include <iterator> // std::distance
#include <vector> // std::vector

unsigned long long clp(unsigned long long x) {
    x -= 1;
    x = x | (x >>  1);
    x = x | (x >>  2);
    x = x | (x >>  4);
    x = x | (x >>  8);
    x = x | (x >> 16);
    x = x | (x >> 32);
    return x + 1;
}

// a[0], a[1], ... , a[n - 1] is a given array of length n.
// T is the type of elements of array a.
// UNIT is a element such that for any element x, f(x, UNIT) == x.
// e.g. f(x, y) = sum(x, y), UNIT = 0.
// e.g. f(x, y) = min(x, y), UNIT = INFINITY.
template <class T>
class segment_tree {
private:
    const size_t size;
    const size_t n;
    const std::function<T(const T&, const T&)> f;
    const T UNIT;
    std::vector<T> a;
public:
    segment_tree(size_t size, std::function<T(const T&, const T&)> f, T UNIT) : size(size), n(clp(size)), f(f), UNIT(UNIT), a(2 * n - 1, UNIT) { }

    template <class Iterator>
    segment_tree(Iterator first, Iterator last, std::function<T(const T&, const T&)> f, T UNIT) : size(std::distance(first, last)), n(clp(size)), f(f), UNIT(UNIT), a(2 * n - 1, UNIT) {
        for (size_t i = n - 1; first != last; ++i) {
            a[i] = *(first++);
        }
        for (int i = n - 2; i >= 0; --i) {
            a[i] = f(a[2 * i + 1], a[2 * i + 2]);
        }
    }

    void update(size_t i, const T &x) {
        i += n - 1;
        a[i] = x;
        while (i) {
            i = (i - 1) / 2;
            a[i] = f(a[2 * i + 1], a[2 * i + 2]);
        }
    }

    T query(size_t query_first, size_t query_last, size_t k = 0, size_t node_first = 0, size_t node_last = 0) const {
        if (k == 0) {
            node_last = n;
        }
        if (node_last <= query_first || query_last <= node_first) {
            return UNIT;
        }
        if (query_first <= node_first && node_last <= query_last) {
            return a[k];
        } else {
            size_t node_mid = (node_first + node_last) / 2;
            T vl = query(query_first, query_last, k * 2 + 1, node_first, node_mid);
            T vr = query(query_first, query_last, k * 2 + 2, node_mid, node_last);
            return f(vl, vr);
        }
    }

    friend std::istream& operator>>(std::istream &is, segment_tree &st) {
        const size_t m = st.n - 1 + st.size;
        for (size_t i = st.n - 1; i < m; ++i) {
            is >> st.a[i];
        }
        for (int i = st.n - 2; i >= 0; --i) {
            st.a[i] = st.f(st.a[2 * i + 1], st.a[2 * i + 2]);
        }
        return is;
    }
};

#endif // SEGMENT_TREE_CPP
