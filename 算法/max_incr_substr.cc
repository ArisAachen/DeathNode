#include <algorithm>
#include <vector>
#include <iostream>

int max_incr_substr(const std::vector<int>& source) {
    int max_incr = 1;
    std::vector<int> incr_vec(source.size(), 1);
    for (int index = 0; index < source.size(); index++) {
        for (int jdex = 0; jdex < index; jdex++) {
            if (source[index] > source[jdex])
                incr_vec[index] = std::max(incr_vec[jdex] + 1, incr_vec[index]);
        }
        if (incr_vec[index] > max_incr)
            max_incr = incr_vec[index];
    }
    return max_incr;
}

int main() {
    std::cout << max_incr_substr({1, 2, 3, 4, 3, 6}) << std::endl;
    return 0;
}