#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

int max_insert_parlin(const std::string& source) {
    std::vector<std::vector<int>> parlin_vec(source.size(), 
        std::vector<int> (source.size(), 0));
    int size = source.size();
    for (int index = size - 2; index >= 0; index--) {
        for (int jdex = index + 1; jdex < size; jdex++) {
            if (source[index] == source[jdex])
                parlin_vec[index][jdex] = parlin_vec[index + 1][jdex - 1];
            else 
                parlin_vec[index][jdex] = std::min(parlin_vec[index + 1][jdex],
                    parlin_vec[index][jdex - 1]) + 1;            
        }
    }
    return parlin_vec[0][size - 1];    
}

int main() {
    std::cout << max_insert_parlin("abcea") << std::endl;
    return 0;
}