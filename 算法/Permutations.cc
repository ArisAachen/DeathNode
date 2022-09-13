#include <list>
#include <array>
#include <vector>
#include <numeric>
#include <iterator>
#include <iostream>
#include <algorithm>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


std::list<int> tmp_saver;
std::list<std::list<int>> results;

void permutation(int arr[], int count) {
    if (tmp_saver.size() == count) {
        results.push_back(tmp_saver);
        return;
    }
    for (int index = 0; index < count; index++) {
        if (std::find(tmp_saver.cbegin(), tmp_saver.cend(), arr[index]) != tmp_saver.cend())
            continue;
        tmp_saver.push_back(arr[index]);
        permutation(arr, count);
        tmp_saver.pop_back();
    }
}

void test_permutation() {
    int arr[4] {1, 2, 3, 4};
    permutation(arr, 4);
    for (const auto& result : results) {
        std::cout << "combine: ";
        for (const auto elem : result) 
            std::cout << elem << " ";
        std::cout << std::endl;
    }
}

bool legal_position(std::vector<std::vector<int>>& vec, int row, int column) {
    for (int index = 0; index < vec.size(); index++) 
        for (int jdex = 0; jdex < vec[index].size(); jdex++) {
            if (vec[index][jdex] == 1) {
                if (index == row || jdex == column) 
                    return false;
                if (index - row == jdex - column) 
                    return false;
            } 
        }
    
    return true;
}


int main() {
    inet_pton(int __af, const char *__restrict __cp, void *__restrict __buf)

    return 0;
}