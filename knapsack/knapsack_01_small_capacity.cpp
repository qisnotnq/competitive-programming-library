#include <algorithm> // std::max, std::min
#include <utility> // std::pair
#include <vector> // std::vector

using ull = unsigned long long;

// First element is weight, second element is value.
using Item = std::pair<int, ull>;

// Time complexity is O(n * W),
// auxiliary space is O(W),
// where n = items.size(),
//       W = min(capacity, sum(weight)).
ull knapsack_01_small_capacity(const std::vector<Item> &items, int capacity) {
    int n = items.size();
    int weight_sum = 0;
    for (const Item &item: items) {
        weight_sum += item.first;
    }
    int W = std::min(capacity, weight_sum);
    std::vector<ull> dp(W + 1, 0);
    for (const Item &item: items) {
        for (int w = W; w >= item.first; --w) {
            dp[w] = std::max(dp[w], dp[w - item.first] + item.second);
        }
    }
    return dp[W];
}
