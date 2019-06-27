// Item is represented by (usize, u64).
// First element is weight, second element is value.
//
// Time complexity is O(items.len() * capacity),
// auxiliary space is O(capacity).
pub fn knapsack(items: &[(usize, u64)], capacity: usize) -> u64 {
    let mut dp = vec![0; capacity + 1];
    for i in 1..capacity + 1 {
        for &(weight, value) in items {
            if weight <= i {
                dp[i] = std::cmp::max(dp[i], dp[i - weight] + value);
            }
        }
    }
    dp[capacity]
}
