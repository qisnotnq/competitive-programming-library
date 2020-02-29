#ifndef UTILS_CPP
#define UTILS_CPP

#include <algorithm> // std::sort
#include <vector> // std::vector

template <class T>
std::vector<size_t> argsort(const std::vector<T> &a) {
    std::vector<size_t> result(a.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = i;
    }
    std::sort(result.begin(), result.end(), [&](size_t i, size_t j) { return a[i] < a[j]; });
    return result;
}

#endif // UTILS_CPP
