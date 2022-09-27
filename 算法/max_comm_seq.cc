#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

// babcabe
// ace
/**
 *  x 0 b a b c a b e
 *  0 0 0 0 0 0 0 0 0 
 *  a 0 0 1 1 1 1 1 1
 *  c 0 0 1 1 2 2 2 2
 *  e 0 0 1 1 2 2 2 3
 */

int max_comm_sequence(const std::string& first, const std::string& second) {
    std::vector<std::vector<int>> dp (first.size() + 1, 
        std::vector<int> (second.size() + 1, 0));
    for (int index = 1; index <= first.size(); index++) {
        for (int jdex = 1; jdex <= second.size(); jdex++) {
            if (first[index] == second[jdex])
                dp[index][jdex] = dp[index - 1][jdex - 1] + 1;
            else
                dp[index][jdex] = std::max(dp[index - 1][jdex], 
                    dp[index][jdex - 1]);
        }
    }
    return dp[first.size()][second.size()];
}

int main() {
    std::cout << max_comm_sequence("babcabe", "abef") << std::endl;
    return 0;
}