#include <utility>
#include <vector>

using ull = unsigned long long;

// First element is weight, second element is value.
using Item = std::pair<int, ull>; 

// Time Complexity: O(items.size() * capacity)
// Space Complexity: O(capacity)
ull knapsack(std::vector<Item> &items, int capacity) {
    std::vector<ull> dp(capacity + 1, 0);
    for (int i = 1; i <= capacity; ++i) {
        for (Item item: items) {
            int weight = item.first;
            ull value = item.second;
            if (weight <= i) {
                dp[i] = std::max(dp[i], dp[i - weight] + value);
            }
        }
    }
    return dp[capacity];
}
