#include <algorithm>
#include <iterator>
#include <queue>
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>

std::string plus_one(std::string cur, int index) {
    if (cur[index] == '9')
        cur[index] = '0';
    else
        cur[index]++;
    return cur;
}

std::string minus_one(std::string cur, int index) {
    if (cur[index] == '0')
        cur[index] = '9';
    else
        cur[index]--;
    return cur;
}

int openlock(const std::vector<std::string>& death_vec, const std::string& target) {
    if (target == "0000")
        return 0;
    std::queue<std::string> offer_queue;
    std::unordered_set<std::string> visited_set;
    std::unordered_set<std::string> invalid_set(
            std::make_move_iterator(death_vec.begin()),
                std::make_move_iterator(death_vec.end()));
    offer_queue.push("0000");
    visited_set.insert("0000");

    int dial_count = 0;
    while (!offer_queue.empty()) {
        int size = offer_queue.size();
        for (int index = 0; index < size; index++) {
            auto front = offer_queue.front();
            offer_queue.pop();
            if (invalid_set.find(front) != invalid_set.cend())
                continue;
            if (front == target)
                return dial_count;
            for (int jdex = 0; jdex < 4; jdex++) {
                auto plus = plus_one(front, jdex);
                if (visited_set.find(plus) == visited_set.cend()) {
                    offer_queue.push(plus);
                    visited_set.insert(plus);
                }
                auto minus = minus_one(front, jdex);
                if (visited_set.find(minus) == visited_set.cend()) {
                    offer_queue.push(minus);
                    visited_set.insert(minus);
                }
            }
        }
        dial_count++;
    }
    return -1;
}

int main() {
    std::vector<std::string> invalid_vec{"8887", "8889", "8878", "8898", 
        "8788", "8988", "7888", "9888"};
    std::string target("8888");
    std::cout << openlock(invalid_vec, target) << std::endl;
    return 0;
}