#ifndef FENWICK_TREE_CPP
#define FENWICK_TREE_CPP

#include <functional> // std::function
#include <vector> // std::vector

template<class T>
class fenwick_tree {
private:
    const size_t size;
    const std::function<T(T, T)> f;
    const T unit;
    std::vector<T> a;
public:
    fenwick_tree(size_t n, std::function<T(T, T)>, T unit);
    void update(size_t i, T x);
    T query(size_t i) const;
};

template<class T>
fenwick_tree<T>::fenwick_tree(size_t size, std::function<T(T, T)> f, T unit): size(size), f(f), unit(unit), a(size, unit) { }

template<class T>
void fenwick_tree<T>::update(size_t i, T x) {
    for (size_t j = i; j < size; j |= j + 1) {
        a[j] = f(a[j], x);
    }
}

template<class T>
T fenwick_tree<T>::query(size_t i) const {
    T result = unit;
    for (size_t j = i; j > 0; j = (j & (j + 1))) {
        result = f(result, a[--j]);
    }
    return result;
}

template <class T>
class range_add_sum_query {
private:
    fenwick_tree<T> fenwick_1;
    fenwick_tree<T> fenwick_2;
public:
    range_add_sum_query(size_t n) : fenwick_1(n + 1, [](T x, T y) { return x + y; }, 0),
                                    fenwick_2(n + 1, [](T x, T y) { return x + y; }, 0) { }

    void range_add(size_t first, size_t last, T x) {
        fenwick_1->update(first, x);
        fenwick_1->update(last, -x);
        fenwick_2->update(first, first * x);
        fenwick_2->update(last, -last * x);
    }

    T range_sum(size_t last) const {
        return fenwick_1->query(last) * last - fenwick_2->query(last);
    }

    T range_sum(size_t first, size_t last) const {
        return range_sum(last) - range_sum(first);
    }
};

#endif // FENWICK_TREE_CPP