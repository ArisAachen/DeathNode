#include <algorithm>
#include <limits>
#include <string>
#include <iostream>
#include <unordered_set>

int max_not_repeat(const std::string& source) {
    std::unordered_set<char> repeat_set;

    int max_len = 1;
    int left = 0;
    for (int right = 0; right < source.size(); right++) {
        auto ch = source[right];
        if (repeat_set.find(ch) == repeat_set.cend()) 
            repeat_set.insert(ch);
        else {
            while (source[left] != ch) {
                repeat_set.erase(source[left]);
                left++;
            }
            max_len = std::max(max_len, right - left);
            left++;
        }
    }
    return max_len;
}

int main() {
    std::cout << max_not_repeat("abcdefa") << std::endl;
    return 0;
}