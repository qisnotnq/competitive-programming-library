#include <vector> // std::vector

template <class Integer>
std::vector<Integer> divisors(Integer n) {
    std::vector<Integer> ds;
    for (Integer i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            Integer j = n / i;
            ds.push_back(i);
            if (j > i) {
                ds.push_back(j);
            }
        }
    }
    return ds;
}
