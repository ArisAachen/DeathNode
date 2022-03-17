
#include <bits/types/struct_tm.h>
#include <ctime>
#include <memory>
#include <iostream>
#include <ostream>
#include <sys/ucontext.h>
#include <vector>
#include <queue>
#include <functional>
#include <ucontext.h>

void test() {
    std::cout << "test" << std::endl;
}

class Test {
public:
    typedef std::shared_ptr<Test> ptr;
    Test(std::function<void()> cb): cb_(cb) {

    }

    void add (std::function<void()> cb) {
        cb_ = cb;
    }

    void log() {
        if (cb_) 
            cb_();
    }
private: 
    std::function<void()> cb_;
};

class TestMgr : public std::enable_shared_from_this<TestMgr> {
public:
    typedef std::shared_ptr<TestMgr> ptr;
    TestMgr() {}
    void log(Test::ptr arg) {
        arg->log();
    }
};

void cotine() {
    std::cout << "cotine" << std::endl;
}

template <typename T>
class SingeltonPtr {
public: 
    template<typename... Args>
    static std::shared_ptr<T> get_instance(Args... args) {
        static std::shared_ptr<T> instance_ptr_ = std::shared_ptr<T>(new T(args...));
        return instance_ptr_->shared_from_this();
    }
};

class VectorTest {
public:
    void run () {
        while (!que.empty()) {
            auto it = que.front();
            que.pop();
            it->log();

            ucontext_t context;
            getcontext(&context);
            char stack[512];
            context.uc_link = nullptr;
            context.uc_stack.ss_sp = stack;
            context.uc_stack.ss_size = 512;
            makecontext(&context, cotine, 0);
            swapcontext(&context, nullptr);
        }
    }

    void push(std::function<void()> cb) {
        que.push(Test::ptr(new Test(cb)));
    }

    std::queue<Test::ptr> que;
};

void test_arg(Test::ptr arg) {
    arg->log();
}

int main() {

    // Test::ptr arg(new Test(test));
    // for (int index = 0; index < 20; index ++) {
    //     test_arg(arg);
    // }

    VectorTest v;
    for (int index = 0; index < 10; index++) {
        v.push(test);
    }
    
    v.run();

    return 1;
}