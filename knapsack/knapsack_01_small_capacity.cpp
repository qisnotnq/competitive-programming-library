#include <algorithm> // std::max
#include <utility> // std::pair
#include <vector> // std::vector

using ull = unsigned long long;

// First element is weight, second element is value.
using Item = std::pair<int, ull>;

// Time complexity is O(n * W),
// auxiliary space is O(n * W),
// where n = items.size(),
//       W = min(capacity, sum(weight)).
ull knapsack_01_small_capacity(std::vector<Item> &items, int capacity) {
    int n = items.size();
    int weight_sum = 0;
    for (const Item &item: items) {
        weight_sum += item.first;
    }
    int W = std::min(capacity, weight_sum);
    std::vector<std::vector<ull>> dp(n + 1, std::vector<ull>(W + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (items[i - 1].first <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].first] + items[i - 1].second);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}
