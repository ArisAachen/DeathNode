#include <iostream>
#include <thread>
#include <memory>

static std::shared_ptr<int> global_num = nullptr;

void release_ptr() {
    std::shared_ptr<int> inner_num(new int(10));
    global_num = inner_num;
}

int main() {
    auto thread = std::thread(release_ptr);
    thread.join();
    std::cout << "use count is " << global_num.use_count() << std::endl;
    std::cout << "num is " << global_num << std::endl; 
}