#include <algorithm> // std::max
#include <climits> // ULLONG_MAX
#include <utility> // std::pair
#include <vector> // std::vector

using ull = unsigned long long;

// First element is weight, second element is value.
using Item = std::pair<ull, ull>;
 
// Helper function.
template <class ItemIterator>
std::vector<Item> _knapsack_bitdp(ItemIterator first, ItemIterator last, ull capacity) {
    int n = distance(first, last);
    std::vector<Item> a;
    for (int b = 0; b < (1 << n); ++b) {
        ull sum_value = 0;
        ull sum_weight = 0;
        for (int i = 0; i < b; ++i) {
            if (b & (1 << i)) {
                sum_weight += (*(first + i)).first;
                sum_value += (*(first + i)).second;
            }
        }
        if (sum_weight <= capacity) {
            a.push_back(Item(sum_weight, sum_value));
        }
    }
    return a;
}

// Time complexity is O(m * log(m)),
// auxiliary space is O(m * log(m)),
// where n = items.size(),
//       m = pow(2, n / 2).
ull knapsack_01_small_items(const std::vector<Item> &items, ull capacity) {
    int n = items.size();
    std::vector<Item> a1 = _knapsack_bitdp(items.begin(), items.begin() + n / 2, capacity);
    std::vector<Item> a2 = _knapsack_bitdp(items.begin() + n / 2, items.end(), capacity);
    sort(a2.begin(), a2.end());
 
    std::vector<ull> acc_max_value(a2.size() + 1);
    acc_max_value[0] = 0;
    for (int i = 0; i < a2.size(); ++i) {
        acc_max_value[i + 1] = std::max(acc_max_value[i], a2[i].second);
    }
 
    ull result = 0;
    for (const Item &item: a1) {
        ull weight1 = item.first;
        ull value1 = item.second;
        ull value2 = acc_max_value[distance(a2.begin(), upper_bound(a2.begin(), a2.end(), Item(capacity - weight1, ULLONG_MAX)))];
        result = std::max(result, value1 + value2);
    }
    return result;
}
