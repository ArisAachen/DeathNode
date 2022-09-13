#include <cmath>
#include <bitset>
#include <iostream>

int convert_binary_to_dst(std::string& num, int digtal) {
    std::bitset<8> bit_num(num);
    int iresult;
    if (digtal == 10) {
        for (int index = 0; index < bit_num.size(); index++) {
            iresult += bit_num[index] * std::pow(2, index);
        }
        return iresult;
    }
}

int main() {
    
    return 0;
}