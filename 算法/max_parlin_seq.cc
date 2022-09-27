#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

/** abcecda
 * x 0 a b c e c d a
 * 0 0 0 0 0 0 0 0 0
 * a 0 1  
 * b 0 0
 * c 0
 * e 0
 * c 0
 * d 0
 * a 0
 */ 

int max_parlin_seq(const std::string& source) {
    std::vector<std::vector<int>> parlin_vec(source.size(), 
        std::vector<int> (source.size(), 0));
    int size = source.size();
    for (int index = 0; index < size; index++) {
        parlin_vec[index][index] = 1;
    }
    for (int index = size - 2; index >= 0; index--) {
        for (int jdex = index + 1; jdex < size; jdex++) {
            if (source[index] == source[jdex])
                parlin_vec[index][jdex] = parlin_vec[index + 1][jdex - 1] + 2;
            else 
                parlin_vec[index][jdex] = std::max(parlin_vec[index + 1][jdex], 
                    parlin_vec[index][jdex - 1]);            
        }
    }
    return parlin_vec[0][size - 1];
}

int main() {
    std::cout << max_parlin_seq("aecba") << std::endl;
    return 0;
}