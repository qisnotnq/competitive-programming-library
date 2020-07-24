#include <algorithm> // std::max
#include <tuple> // std::tie
#include <utility> // std::pair
#include <vector> // std::vector

using ull = unsigned long long;

using Item = std::pair<ull, ull>; // (weight, value)

std::vector<Item> enumerate_items(const std::vector<Item> &items, const ull capacity) {

    std::vector<Item> a0{Item(0, 0)};
    for (const Item &item: items) {

        ull weight, value;
        std::tie(weight, value) = item;

        size_t N0 = a0.size();
        std::vector<Item> a1;
        for (size_t i = 0; i < N0; ++i) {
            ull w = a0[i].first + weight;
            if (w > capacity) break;
            ull v = a0[i].second + value;
            a1.emplace_back(w, v);
        }
        size_t N1 = a1.size();

        std::vector<Item> b{Item(0, 0)};
        size_t i0 = 1;
        size_t i1 = 0;
        while (true) {
            if (i0 == N0) {
                while (i1 < N1) {
                    b.push_back(a1[i1++]);
                }
                break;
            } else if (i1 == N1) {
                while (i0 < N0) {
                    b.push_back(a0[i0++]);
                }
                break;
            } else {
                if (a0[i0].first < a1[i1].first) {
                    b.push_back(a0[i0++]);
                    while (i1 < N1 && (b.back().first >= a1[i1].first || b.back().second >= a1[i1].second)) {
                        ++i1;
                    }
                } else if (a0[i0].first > a1[i1].first) {
                    b.push_back(a1[i1++]);
                    while (i0 < N0 && (b.back().first >= a0[i0].first || b.back().second >= a0[i0].second)) {
                        ++i0;
                    }
                } else {
                    if (a0[i0].second >= a1[i1].second) {
                        b.push_back(a0[i0++]);
                        ++i1;
                        while (i1 < N1 && (b.back().first >= a1[i1].first || b.back().second >= a1[i1].second)) {
                            ++i1;
                        }
                    } else if (a0[i0].second < a1[i1].second) {
                        b.push_back(a1[i1++]);
                        ++i0;
                        while (i0 < N0 && (b.back().first >= a0[i0].first || b.back().second >= a0[i0].second)) {
                            ++i0;
                        }
                    }
                }
            }
        }
        a0 = b;
    }
    return a0;
}

ull knapsack_01_small_items(const std::vector<Item> &items, ull capacity) {

    size_t N = items.size();
    size_t N0 = N / 2;

    std::vector<Item> a0 = enumerate_items(std::vector<Item>(items.begin(), items.begin() + N0), capacity);
    std::vector<Item> a1 = enumerate_items(std::vector<Item>(items.begin() + N0, items.end()), capacity);

    ull result = 0;
    size_t j = a1.size() - 1;
    for (const Item &item0: a0) {
        ull w0, v0;
        std::tie(w0, v0) = item0;
        ull res = capacity - w0;
        while (a1[j].first > res) {
            if (j == 0) {
                goto out_of_loop;
            }
            --j;
        }
        result = std::max(result, v0 + a1[j].second);
    }
out_of_loop:
    return result;
}
