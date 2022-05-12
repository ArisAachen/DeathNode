#include <iostream>
#include <memory>
#include <functional>


class Base {
public:
    typedef std::shared_ptr<Base> ptr;
    Base() {}
    virtual void extends() {
        std::cout << "base call extends" << std::endl;
    }

    void base() {
        auto func = std::bind(&Base::extends, this);
        func();
        std::cout << "base" << std::endl;
    }

    virtual~Base() {
        std::cout << "base destory" << std::endl;
    }

};


class Extends : public Base {
public:
    virtual void extends() {
        std::cout << "extends call extends" << std::endl;
    }

    ~Extends() {
        std::cout << "extends destory" << std::endl;
    }
};

int main() {
    Base::ptr bs(new Extends{});
    bs->base();
}