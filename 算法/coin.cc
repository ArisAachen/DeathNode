#include <algorithm>
#include <ios>
#include <vector>
#include <iostream>
#include <limits>

int col(int amount, std::vector<int>& vec) {
    if (amount < 0)
        return -1;
    if (amount == 0)
        return 0;
    int count = std::numeric_limits<int>::max();
    for (int index = 0; index < vec.size(); index++) {
        int coin = col(amount - vec[index], vec);
        if (coin < 0) continue;
        count = std::min(count, coin + 1);
    }
    return count == std::numeric_limits<int>::max() ? -1 : count;
}

int col_dp(int amount, std::vector<int>& vec) {
    std::vector<int> dp (amount + 1, std::numeric_limits<int>::max());
    dp[0] = 0;
    for (int index = 1; index <= dp.size(); index++) {
        for (auto elem : vec) {
            if (index - elem < 0) continue;
            dp[index] = std::min(dp[index], dp[index - elem] + 1);
        }
    }
    return dp[amount + 1];
}

int main() {
    std::vector<int> vec{1, 2, 5};
    col_dp(11, vec);
    return 0;
}