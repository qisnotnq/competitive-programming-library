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

long long ceil_div(long long a, long long b) {
    if (b > 0) {
        if (a >= 0) {
            return (a + b - 1) / b;
        } else {
            // ceil(a / b) == ceil(-((-a) / b)) == -floor((-a) / b)
            return -((-a) / b);
        }
    } else if (b < 0) {
        if (a >= 0) {
            // ceil(a / b) == ceil(-(a / (-b))) == -floor(a / (-b))
            return -(a / (-b));
        } else {
            // ceil(a / b) == ceil((-a) / (-b))
            return ((-a) + (-b) - 1) / (-b);
        }
    } else {
        throw runtime_error("division by zero");
    }
}

#endif // UTILS_CPP
