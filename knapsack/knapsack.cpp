using ull = unsigned long long;

// First element is weight, second element is value.
using Item = pair<int, ull>; 

// Time Complexity: O(items.size() * capacity)
// Space Complexity: O(capacity)
ull knapsack(vector<Item> &items, int capacity) {
    vector<ull> dp(capacity + 1, 0);
    for (int i = 1; i <= capacity; ++i) {
        for (Item item: items) {
            int weight = item.first;
            ull value = item.second;
            if (weight <= i) {
                dp[i] = max(dp[i], dp[i - weight] + value);
            }
        }
    }
    return dp[capacity];
}
