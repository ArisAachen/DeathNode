#include <list>
#include <iostream>
#include <optional>

class Stack {
public:
    std::optional<int> pop() {
        if (lst_.empty())
            return std::nullopt;
        int result = lst_.back();
        lst_.pop_back();
        return result;
    }

    void push(int value) {
        lst_.push_back(value);
    }

    void clear() {
        lst_.clear();
    }

private:
    std::list<int> lst_;
};

class Queue {
public:
    std::optional<int> pop() {
        if (lst_.empty()) 
            return std::nullopt;
    }

private:
    std::list<int> lst_;
};

int main() {
    Stack stack;
    stack.push(1);
    stack.push(2);

    auto result = stack.pop();
    if (result)
        std::cout << "pop value is: " << result.value() << std::endl;
    return 1;
}