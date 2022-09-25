#include <vector>
#include <string>
#include <iostream>


int longest_pal_substr(const std::string& origin) {
    if (origin.length() == 0)
        return 0;

    int max_len = 1;
    std::vector<int> match_vec(origin.length());
    match_vec[0] = 0;
    for (int index = 1; index < origin.length(); index++) {
        if (origin[index - 1] > 0 && origin[match_vec[index - 1] - 1] == origin[index]) 
            match_vec[index] = match_vec[index - 1] - 1;
        else {
            int left = match_vec[index - 1];
            int right = index;
            int start = left;
            while (left < right) {
                if (origin[left] != origin[right]) {
                    right = index;
                    start = left + 1;
                } else 
                    right--;
                left++;
            }
            match_vec[index] = start;
        }
    }

    return max_len;
}