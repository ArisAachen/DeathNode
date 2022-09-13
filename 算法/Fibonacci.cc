#include <vector>
#include <iostream>

int fibonacci_recursion(int count) {
    // dp vec to store index calculated result
    static std::vector<int> vec(count + 1, 0);
    // stop condtion
    if (count == 0) 
        return 0;
    if (count == 1 || count == 2)
        return 1;
    // check if has already calculated
    if (vec.size() >= count && vec[count]) {
        std::cout << "reuse vec, index: " << count << ", value: " << vec[count] << std::endl;
        return vec[count];
    }
    // state equation
    int num = fibonacci_recursion(count - 1) + fibonacci_recursion(count - 2);
    // store
    vec[count] = num;
    return num;
}

int fibonacci_cycle(int count) {
    if (count == 0) 
        return 0;
    if (count <= 2) 
        return 1;
    static std::vector<int> vec(count + 1, 0);
    vec[1] = vec[2] = 1;
    for (int index = 3; index < count + 1; index++) 
        vec[index] = vec[index - 1] + vec[index - 2];
    return vec[count];
}

int main() {
    int result = fibonacci_recursion(8);
    std::cout << "fibonacci_recursion result is " << result << std::endl;
    std::cout << "fibonacci_cycle result is " << fibonacci_cycle(8) << std::endl;
    return 1;
}