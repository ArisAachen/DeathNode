#include <algorithm>
#include <vector>
#include <iostream>

int package(int wight_index, int package_index) {
    std::vector<int> col_vec(package_index + 1, 0);
    std::vector<std::vector<int>> row_vec(wight_index + 1, col_vec);
    std::vector<int> weight_vec {2, 1, 3};
    std::vector<int> value_vec {4, 2, 3};

    for (int index = 1; index <= wight_index; index++) {
        for (int jdex = 1; jdex <= package_index; jdex++) {
            if (jdex < weight_vec[index - 1])
                row_vec[index][jdex] = row_vec[index - 1][jdex]; 
            else {
                row_vec[index][jdex] = std::max(row_vec[index - 1][jdex], 
                    value_vec[index - 1] + row_vec[index - 1][jdex - weight_vec[index - 1]]);
            }
        }
    }

    for (const auto& vec : row_vec) {
        for (const auto& elem : vec)
            std::cout << elem << " ";
        std::cout << std::endl;
    }

    return row_vec[wight_index][package_index];
}


int knapsack(int W, int N, std::vector<int>& wt, std::vector<int>& val) {
    std::vector<std::vector<int>> dp(N + 1, std::vector<int> (W + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - wt[i - 1] < 0) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = std::max(dp[i - 1][w - wt[i - 1]] + val[i - 1], dp[i - 1][w]);
            }
        }
    }
    return dp[N][W];
}



int main() {
    std::vector<int> weight_vec {1, 2, 3};
    std::vector<int> value_vec {2, 4, 3};
    int max = knapsack(1, 1, weight_vec, value_vec);
    std::cout << "max elem: " << max << std::endl;
    return 0;
}
