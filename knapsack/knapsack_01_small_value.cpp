#include <algorithm> // std::min
#include <utility> // std::pair
#include <vector> // std::vector

using ull = long long;

// First element is weight, second element is value.
using Item = std::pair<ull, int>;

// Time complexity is O(items.size() * sum(value)),
// auxiliary space is O(sum(value)).
int knapsack_01_small_value(const std::vector<Item> &items, ull capacity) {
    int n = items.size();
    int value_sum = 0;
    for (const Item &item: items) {
        value_sum += item.second;
    }
    std::vector<ull> dp(value_sum + 1, capacity + 1);
    dp[0] = 0;
    for (const Item &item: items) {
        for (int v = value_sum; v >= item.second; --v) {
            dp[v] = std::min(dp[v], dp[v - item.second] + item.first);
        }
    }
    for (int v = value_sum; ; --v) {
        if (dp[v] <= capacity) {
            return v;
        }
    }
}
