#include <algorithm> // std::max
#include <utility> // std::pair
#include <vector> // std::vector

using ull = unsigned long long;

// First element is weight, second element is value.
using Item = std::pair<int, ull>; 

// Time complexity is O(items.size() * capacity),
// auxiliary space is O(capacity).
ull knapsack(const std::vector<Item> &items, int capacity) {
    std::vector<ull> dp(capacity + 1, 0);
    for (int i = 1; i <= capacity; ++i) {
        for (const Item &item: items) {
            int weight = item.first;
            ull value = item.second;
            if (weight <= i) {
                dp[i] = std::max(dp[i], dp[i - weight] + value);
            }
        }
    }
    return dp[capacity];
}
