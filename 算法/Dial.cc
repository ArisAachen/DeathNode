#include <bitset>
#include <set>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int openLock(std::vector<std::string>& deadends, std::string& target) {
        int dial_count = 0;
        std::queue<std::string> dial_num_queue;
        std::set<std::string> backup_num_set;
        std::string base("0000");
        dial_num_queue.push(base);
        bool init = false;

        while (!dial_num_queue.empty()) {
            int size = dial_num_queue.size();
            for (int index = 0; index < size; index++) {
                auto dial_num = dial_num_queue.front();
                dial_num_queue.pop();
                if (init && std::find(deadends.cbegin(), deadends.cend(), dial_num) != deadends.cend())
                    continue;
                if (dial_num == target) 
                    return dial_count;
                for (int drc = 0; drc < 4; drc++) {
                    auto up = dial_up(dial_num, drc);
                    if (backup_num_set.find(up) == backup_num_set.end()) {
                        dial_num_queue.push(up);
                        backup_num_set.insert(up);
                    }
                    auto down = dial_down(dial_num, drc);
                    if (backup_num_set.find(down) == backup_num_set.end()) {
                        dial_num_queue.push(down);
                        backup_num_set.insert(down);             
                    }
                }
            }
            dial_count++;
            init = true;
        }
        return -1;
    }

private:
    std::string dial_up(std::string origin, int index) {
        if (origin.size() < index) 
            return origin;
        if (origin[index] == '9') 
            origin[index] = '0';
        else 
            origin[index]++;
        return origin;
    }

    std::string dial_down(std::string origin, int index) {
        if (origin.size() < index) 
            return origin;
        if (origin[index] == '0') 
            origin[index] = '9';
        else 
            origin[index]--;
        return origin;
    }
};

/**
["0201","0101","0102","1212","2002"]
"0202" 
 */

int main() {
    std::string target("8888");
    std::vector<std::string> vec {"0000"};

    Solution sol;
    std::cout << "dial count is " << sol.openLock(vec, target) << std::endl;


    return 1;
}