#include "thread_test.h"
#include <chrono>
#include <cstdlib>
#include <thread>

void sleep_test() 
{
    std::cout << "sleep start" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "sleep end" << std::endl;
}



void thread_test() 
{
    std::thread t(sleep_test);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}