#include <ios>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

void index_permutation(std::vector<int>& vec, const std::string& source, const std::string& target) {
    std::unordered_map<char, int> window_map, needed_map;
    for (auto ch : target) 
        needed_map[ch]++;
    int valid_ch, left;
    valid_ch = left = 0;
    for (int right = 0; right < source.size(); right++) {
        auto ch = source[right];
        if (needed_map.count(ch)) {
            window_map[ch]++;
            if (window_map[ch] == needed_map[ch])
                valid_ch++;
        }

        if (right - left + 1 == target.size()) {
            if (valid_ch == needed_map.size()) 
                vec.push_back(left);
            auto ch = source[left];
            if (needed_map.count(ch)) {
                window_map[ch]--;
                if (window_map[ch] < needed_map[ch])
                    valid_ch--;
            }
            left++;
        }
    }
}

int main() {
    std::vector<int> begin_vec;
    index_permutation(begin_vec, "cbaebabacd", "abc");
    for (auto elem : begin_vec)
        std::cout << elem << std::endl;
    return 0;
}