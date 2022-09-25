#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

bool is_pefect(int number) {
    std::vector<int> vec {1};
    for (int index = 2; index < std::sqrt(number); index++) {
        if (number % index == 0) {
            vec.push_back(index);
            vec.push_back(number / index);
        }
    }
    std::cout << "number: " << number << std::endl << "elem: ";
    for (auto elem : vec) 
        std::cout << elem << " ";
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << std::endl << "sum: " << sum << std::endl;
    if (sum == number) 
        std::cout << "this number is perfect" << std::endl;
    std::cout << std::endl;
    return sum == number;
}

int main() {
    int input;
    std::cin >> input;
    int count = 0;
    for (int index = 1; index < input; index++) {
        if (is_pefect(index))
            count ++;
    }
    std::cout << count << std::endl;
}