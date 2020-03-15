#ifndef INVERSION_NUMBER_CPP
#define INVERSION_NUMBER_CPP

#include <algorithm> // std::sort
#include <iterator> // std::iterator_traits, std::distance
#include <vector> // std::vector

#include "range_query/fenwick_tree.cpp"
#include "utils/utils.cpp"

// Returns the inversion number of [first, last).
// Value type of Iterator must be totally ordered.
// The inversion number of a sequence a[i] (0 <= i < n) is
// # { (i, j) | i < j and a[i] > a[j] }.
template <class Iterator>
unsigned long long inversion_number(Iterator first, Iterator last) {
    using T = typename std::iterator_traits<Iterator>::value_type;

    size_t n = std::distance(first, last);
    std::vector<size_t> a = argsort(std::vector<size_t>(first, last));
    unsigned long long result = 0;
    fenwick_tree<size_t> range_sum_query(n, [](size_t x, size_t y) { return x + y; }, 0);
    for (auto it = a.rbegin(); it != a.rend(); ++it) {
        result += range_sum_query.query(*it);
        range_sum_query.update(*it, 1);
    }
    return result;
}

#endif // INVERSION_NUMBER_CPP
