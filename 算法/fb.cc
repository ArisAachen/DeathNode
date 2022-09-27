#include <vector>
#include <iostream>

int fb(int pos = 0) {
    if (pos == 0) 
        return 0;
    if (pos == 1 || pos == 2)
        return 1;
    std::vector<int> vec (pos + 1, 1);
    for (int index = 3; index <= pos; index++) 
        vec[index] = vec[index - 1] + vec[index - 2];
    return vec[pos];
}

int main() {
    // 1 1 2 3 5 8
    std::cout << fb(6) << std::endl;
    return 0;
}