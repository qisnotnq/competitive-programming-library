template<class T>
class binary_indexed_tree {
private:
    const size_t size;
    const function<T(T, T)> f;
    const T unit;
    T *a;
public:
    binary_indexed_tree(size_t n, function<T(T, T)>, T unit);
    ~binary_indexed_tree();
    void update(size_t i, T x);
    T query(size_t i) const;
};

template<class T>
binary_indexed_tree<T>::binary_indexed_tree(size_t size, function<T(T, T)> f, T unit): size(size), f(f), unit(unit) {
    a = new T[size];
    fill(a, a + size, unit);
}

template<class T>
binary_indexed_tree<T>::~binary_indexed_tree() {
    delete [] a;
}

template<class T>
void binary_indexed_tree<T>::update(size_t i, T x) {
    for (size_t j = i; j < size; j |= j + 1) {
        a[j] = f(a[j], x);
    }
}

template<class T>
T binary_indexed_tree<T>::query(size_t i) const {
    T result = unit;
    for (size_t j = i; j > 0; j = (j & (j + 1))) {
        result = f(result, a[--j]);
    }
    return result;
}

class range_add_sum_query {
private:
    binary_indexed_tree<ll> *bit1;
    binary_indexed_tree<ll> *bit2;
public:
    range_add_sum_query(size_t n) {
        this->bit1 = new binary_indexed_tree<ll>(n + 1, [](ll x, ll y) { return x + y; }, 0);
        this->bit2 = new binary_indexed_tree<ll>(n + 1, [](ll x, ll y) { return x + y; }, 0);
    }

    ~range_add_sum_query() {
        delete this->bit1;
        delete this->bit2;
    }

    void range_add(size_t first, size_t last, ll x) {
        bit1->update(first, x);
        bit1->update(last, -x);
        bit2->update(first, first * x);
        bit2->update(last, -last * x);
    }

    ll range_sum(size_t last) {
        return bit1->query(last) * last - bit2->query(last);
    }

    ll range_sum(size_t first, size_t last) {
        return range_sum(last) - range_sum(first);
    }
};

int main() {
    return 0;
}
