#include <algorithm>
#include <vector>
#include <iostream>

int max_sum_subvec(const std::vector<int>& source) {
    std::vector<int> maxsum_vec(source.size(), 0);
    maxsum_vec[0] = source[0];
    int max_sum = source[0];
    for (int index = 1; index < source.size(); index++) {
        maxsum_vec[index] = std::max(source[index], maxsum_vec[index] + source[index]);
        max_sum = std::max(max_sum, maxsum_vec[index]);
    }
    return max_sum;
}

int main() {
    std::cout << max_sum_subvec({-3, 1, 3, -1, 2, -4, 2}) << std::endl;
    return 0;
}