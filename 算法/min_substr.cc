#include <limits>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

std::string slide_window(const std::string& source, const std::string& target) {
    std::unordered_map<char, int> window_map, need_map;
    for (auto ch: target)
        need_map[ch]++;
    
    int min_count = std::numeric_limits<int>::max();
    std::string result;
    int valid_ch, left, start;
    valid_ch = left = start = 0;
    for (int right = 0; right < source.size(); right++) {
        auto ch = source[right];
        if (need_map.count(ch)) {
            window_map[ch]++;
            if (window_map[ch] == need_map[ch])
                valid_ch++;
        }

        while (valid_ch == need_map.size()) {
            auto ch = source[left];
            if (window_map.count(ch)) {
                window_map[ch]--;
                if (window_map[ch] < need_map[ch]) {
                    valid_ch--;
                    int len = right - left + 1;
                    if (min_count > len) {
                        min_count = len;
                        result = source.substr(left, len);
                    }
                }
            }
            left++;
        }
    }
    return result;
}

int main() {
    std::cout << slide_window("ADBECFEBANC", "ABC") << std::endl;
    return 0;
}