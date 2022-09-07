#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <unistd.h>
#include <utility>
#include <vector>

class Base {
public:
    Base(int index = 1) : num_(index) {
        std::cout << "base consruction" << std::endl;
    }

    virtual~Base() {
        std::cout << "base destroyed" << std::endl;
    }

    Base(const Base&) {
        std::cout << "base copy construction" << std::endl;
    }

    Base& operator=(const Base&) {
        std::cout << "base copy equal construction" << std::endl;
        return *this;
    }

    void num() { std::cout << "num is " << num_ << std::endl; }

private:
    int num_;
protected:
    int pro_;
public:
    int pub_;
};

class Father : public Base {
public:
    void num() {}
};

void test(std::true_type, std::false_type) {

}

int align = 8;
int get_index(int bytes) {
    return 0;
}

#include <map>
#include <list>
int main() {
    // Father father;
    // sleep(5);
    // Base base = father;

    // Base* ptr = new Base;
    // ptr->num();
    // new (ptr) Base(2);
    // ptr->num();

    Base copy = std::move(Base{});

    // std::map<int, int, std::less<>> mem{
    //     {1, 1},
    //     {2, 2},
    //     {3, 3},
    //     {4, 4}
    // };
    // auto pos = mem.erase(mem.find(2));
    // std::cout << pos->first << std::endl;

    // std::vector<int> vec {1, 2, 3, 4};
    // auto vpos = vec.erase(vec.begin());
    // std::cout << *vpos << std::endl;
    // (vpos++)++;
    // std::cout << *vpos << std::endl;

    std::list<int> con {2, 3, 4};
    auto lpos = std::find(con.begin(), con.end(), 3);
    con.insert(lpos, 2);
    std::for_each(con.cbegin(), con.cend(), [](const auto& elem) {
        std::cout << elem << std::endl;
    });

    // sleep(5);

    return 1;
};


