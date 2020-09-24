#ifndef FENWICK_TREE_CPP
#define FENWICK_TREE_CPP

#include <functional> // std::function
#include <istream> // std::istream
#include <iterator> // std::distance
#include <vector> // std::vector

template<class T>
class fenwick_tree {
private:
    const std::function<T(T, T)> f;
    const T unit;
    std::vector<T> a;
public:
    fenwick_tree(size_t size, std::function<T(T, T)> f, T unit) : f(f), unit(unit), a(size, unit) { }

    template <class Iterator>
    fenwick_tree(Iterator first, Iterator last, std::function<T(T, T)> f, T unit) : f(f), unit(unit), a(std::distance(first, last), unit) {
        size_t size = a.size();
        for (size_t i = 0; i < size; ++i) {
            a[i] = f(a[i], *(first++));
            size_t j = i | (i + 1);
            if (j < size) {
                a[j] = f(a[j], a[i]);
            }
        }
    }

    void update(size_t i, T x) {
        size_t size = a.size();
        for (size_t j = i; j < size; j |= j + 1) {
            a[j] = f(a[j], x);
        }
    }

    T query(size_t i) const {
        T result = unit;
        for (size_t j = i; j > 0; j = (j & (j + 1))) {
            result = f(result, a[--j]);
        }
        return result;
    }

    friend std::istream& operator>>(std::istream &is, fenwick_tree &ft) {
        size_t size = ft.a.size();
        for (size_t i = 0; i < size; ++i) {
            T x;
            is >> x;
            ft.a[i] = ft.f(ft.a[i], x);
            size_t j = i | (i + 1);
            if (j < size) {
                ft.a[j] = ft.f(ft.a[j], ft.a[i]);
            }
        }
        return is;
    }
};

template <class T>
class range_add_sum_query {
private:
    fenwick_tree<T> fenwick_1;
    fenwick_tree<T> fenwick_2;
public:
    range_add_sum_query(size_t n) : fenwick_1(n + 1, [](T x, T y) { return x + y; }, 0),
                                    fenwick_2(n + 1, [](T x, T y) { return x + y; }, 0) { }

    void update(size_t first, size_t last, T x) {
        fenwick_1.update(first, x);
        fenwick_1.update(last, -x);
        fenwick_2.update(first, x * T(first));
        fenwick_2.update(last, x * (-T(last)));
    }

    T query(size_t last) const {
        return fenwick_1.query(last) * T(last) - fenwick_2.query(last);
    }

    T query(size_t first, size_t last) const {
        return query(last) - query(first);
    }
};

#endif // FENWICK_TREE_CPP
