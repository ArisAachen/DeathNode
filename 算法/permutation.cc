#include <ios>
#include <string>
#include <iostream>
#include <unordered_map>

bool has_permutation(const std::string& source, const std::string& target) {
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

        while (right - left >= target.size()) {
            auto ch = source[left];
            if (needed_map.count(ch)) {
                window_map[ch]--;
                if (window_map[ch] < needed_map[ch])
                    valid_ch--;
            }
            left++;
        }

        if (valid_ch == needed_map.size())
            return true;
    }
    return false;
}

int main() {
    std::cout << std::boolalpha << has_permutation("helloworld", "drl") << std::endl;
    return 0;
}