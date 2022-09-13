#include <array>
#include <limits>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>

std::array<int, 5> coins {3, 5, 9, 11, 13};
std::vector<int> results;

void print_vec_helper() {
    std::cout << "vec elem: ";
    for (const auto elem : results) 
        std::cout << elem << " ";
    std::cout << std::endl;
}

// if charge onece result is found
static bool charge_once_found = false;
int charge_once(int amount) {
    if (amount < 0) 
        return -1;
    if (amount == 0) 
        return 0;
    int left_amount = 0;
    for (auto coin = coins.crbegin(); coin != coins.crend(); coin++) {
        left_amount = charge_once(amount - *coin);
        if (left_amount == 0) {
            results.push_back(*coin);
            return 0;
        }
        else if (left_amount == -1) 
            continue;
    }
    return left_amount;
}

void test_charge_once() {
    results.clear();
    int success = charge_once(23);
    std::cout << "test_charge_once number is 23, ";
    print_vec_helper();
}

int charge_from_min(int amount) {
    if (amount < 0)
        return -1;
    if (amount == 0)
        return 0;
    int last_count = std::numeric_limits<int>::max();
    for (auto coin = coins.cbegin(); coin != coins.cend(); coin++) {
        int new_count = charge_from_min(amount - *coin);
        if (new_count == -1) 
            continue;
        if (new_count < last_count) {
            std::cout << "new count is less than last count, last: " << last_count 
                << ", new: " << new_count << ", coin: " << *coin << std::endl;
            if (!results.empty() && last_count != std::numeric_limits<int>::max()) {
                int num = results.back();
                results.pop_back();
                std::cout << "pop elem: " << num << ", ";
            }
            results.push_back(*coin);
            last_count = new_count + 1;
            std::cout << "new elem: " << *coin << std::endl;
        }
    }
    return last_count != std::numeric_limits<int>::max() ? last_count : -1;
}

void test_charge_from_min() {
    results.clear();
    int success = charge_from_min(8);
    std::cout << "test_charge_from_min number is 8, ";
    print_vec_helper();
}

int main() {
    test_charge_once();
    test_charge_from_min();
    return 0;
}

