#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

int max_increase_sequence(std::vector<int> input_vec) {
    std::vector<int> results (input_vec.size(), 1);

    for (int index = 0; index < input_vec.size(); index++) {
        for (int jdex = 0; jdex < index; jdex++) {
            if (input_vec[jdex] < input_vec[index]) {
                results[index] = std::max(results[index], results[jdex] + 1);
            }
        }
    }

    int max_count = std::numeric_limits<int>::min();
    for (auto elem : results)
        if (elem > max_count)
            max_count = elem;

    return max_count;
}

int max_sum_sequence(std::vector<int> input_vec) {

    std::vector<int> results(input_vec.size());
    for (int index = 0; index < input_vec.size(); index++) {
        if (index == 0) 
            results[index] = input_vec[index];
        else 
            results[index] = std::max(results[index - 1] + input_vec[index], input_vec[index]);
    }

    int max_sum = std::numeric_limits<int>::min();
    for (auto elem : results)
        if (elem > max_sum)
            max_sum = elem;

    return max_sum;
}




int main() {
    std::vector<int> input {1, 2, 3, -4, 1};
    auto max_count = max_increase_sequence(input);
    std::cout << "max increase sequence: " << max_count << std::endl;

    auto max_sum = max_sum_sequence(input);
    std::cout << "max sum sequence: " << max_sum << std::endl;

    return 0;
}