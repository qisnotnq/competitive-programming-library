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
// (T, f, e) is a monoid.
// e.g. f(x, y) = sum(x, y), e = 0.
// e.g. f(x, y) = min(x, y), e = inf.
template <class T>
class segment_tree {
private:
    const size_t size;
    const size_t n;
    const std::function<T(T, T)> f;
    const T e;
    std::vector<T> a;
public:
    segment_tree(size_t size, std::function<T(T, T)> f, T e) : size(size), n(clp(size)), f(f), e(e), a(2 * n, e) { }

    template <class Iterator>
    segment_tree(Iterator first, Iterator last, std::function<T(T, T)> f, T e) : size(std::distance(first, last)), n(clp(size)), f(f), e(e), a(2 * n, e) {
        for (size_t i = n; first != last; ++i) {
            a[i] = *(first++);
        }
        for (int i = n - 2; i >= 0; --i) {
            _merge(i);
        }
    }

    void update(size_t i, const T &x) {
        i += n;
        a[i] = x;
        i >>= 1;
        while (i) {
            _merge(i);
            i >>= 1;
        }
    }

    T query(size_t first, size_t last) {
        first += n;
        last += n;
        T l = e;
        T r = e;
        while (first < last) {
            if (first & 1) {
                l = f(l, a[first++]);
            }
            if (last & 1) {
                r = f(a[--last], r);
            }
            first >>= 1;
            last >>= 1;
        }
        return f(l, r);
    }

    friend std::istream& operator>>(std::istream &is, segment_tree &st) {
        const size_t m = st.n + st.size;
        for (size_t i = st.n; i < m; ++i) {
            is >> st.a[i];
        }
        for (int i = st.n - 1; i; --i) {
            st._merge(i);
        }
        return is;
    }

private:
    inline void _merge(size_t i) {
        a[i] = f(a[i << 1], a[(i << 1) + 1]);
    }
};

#endif // SEGMENT_TREE_CPP
