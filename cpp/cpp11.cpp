#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>

void test_static_assert() {
    int num = 4;
    static_assert(sizeof(int) == 4, "not int type");
}

auto test_auto_value(int first, double second) -> decltype(first + second) {
    return first + second;
}

void test_promiss(std::promise<int>& promise) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    promise.set_value(6);
}

void test_thread() {
    // std::thread t([](){
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    //     return 8;});
    // t.join();

    std::promise<int> promise;
    auto future = promise.get_future();
    int result = future.get();

    std::future<int> res = std::async([](){
        return 8;
    });
}

void test_lock_guard() {
    std::mutex mut;
    std::lock_guard<std::mutex> lock(mut);
    std::unique_lock<std::mutex> ulock(mut);
}


void test_condition_variant() {
    bool check = false;
    std::mutex mu;
    std::unique_lock<std::mutex> lck(mu);
    std::condition_variable condition;
    condition.wait(lck, [&check]() { return check;});
}

void test_call_once() {
    std::once_flag once;
    std::call_once(once, []() {});
}
