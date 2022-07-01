#include <random>
#include <chrono>
#include <iostream>

const int max_level_ {5};

struct Node {
    Node() {}
    Node(int vl) { 
        value = vl;
        for (int index = 0; index < max_level_; index++) {
            next[index] = nullptr;
        }
    }
    int value {0};
    Node* next[max_level_];
};

class SkipList {
public:
    SkipList() {
        root_ = new Node(-1);
        for (int index = 0; index < max_level_; index++) {
            root_->next[index] = nullptr;
        }
        choose_power();
        std::cout << "skip list power: ";
        for (int index = 0; index < max_level_; index++) {
            std::cout << powers_[index] << " ";
        }
        std::cout << std::endl;
    }

    void add_node(int value) {
        if (root_ == nullptr)
            throw "add node, root is null";
        Node* node = new Node(value);
        int level = choose_level();
        std::cout << "add node, choose level is: " << level << std::endl;
        if (root_->next[0] == nullptr) {
            for (int index = 0; index < level; index++) {
                root_->next[index] = node;
            }
            dump();
            return;
        }
        Node* cur = root_;
        while (level >= 0) {
            if (cur == nullptr)
                throw "add node unexpected null pointer";
            if (cur->next[level] == nullptr) {
                cur->next[level] = node;
                std::cout << "cur next is null, add node as next, " << 
                    "level: " << level << ", cur value: " << cur->value << 
                        ", inser value is: " << value << std::endl;
                level--;
                continue;
            }
            if (cur->next[level]->value < value) {
                std::cout << "cur next is smaller, switch to next node, "
                    "cur level: " << level << ", next value: " << cur->next[level]->value 
                        << std::endl;
                cur = cur->next[level];
                continue;
            }
            if (cur->next[level]->value > value) {
                std::cout << "cur next is bigger, found insert pos " << "cur level: " 
                    << level << ", cur value: " << cur->value << std::endl;
                node->next[level] = cur->next[level];
                cur->next[level] = node;
                level--;
                continue;
            }
            std::cout << "found same value in level: " << level << std::endl;
        }
        dump();
    }

    void del_node(int value) {
        if (root_ == nullptr)
            throw "del node, root is null";
        Node* cur;
        int level = max_level_ - 1;
        cur = root_;
        while(level >= 0) {
            if (cur == nullptr)
                throw "del node unexpected null pointer";
            if (cur->next[level] == nullptr) {
                std::cout << "cur next is null, switch to next level, "
                    "cur level: " << level << std::endl;
                level--;
                continue;
            }
            if (cur->next[level]->value > value) {
                std::cout << "cur next is bigger, switch to next level, "
                    "cur level: " << level << ", next value: " << cur->next[level]->value 
                        << std::endl;
                level--;
                continue;
            }
            if (cur->next[level]->value < value) {
                std::cout << "cur next is smaller, switch to next node, "
                    "cur level: " << level << ", next value: " << cur->next[level]->value 
                        << std::endl;
                cur = cur->next[level];
                continue;
            }
            cur->next[level] = cur->next[level]->next[level];
            level--;
            std::cout << "value is found, level is: " << level << std::endl;
            if (level == 0) {
                delete cur->next[level];
                dump();
            }
        }
    }

    bool is_empty() {
        return root_->next[0] == nullptr;
    }

    void choose_power() {
        for (int index = 0; index < max_level_; index++) {
            powers_[index] = (2 << index) - 1;
        }
    }

    int choose_level() {
        std::default_random_engine engine;
        engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> generator(0, 31);
        int num = generator(engine) + 1;
        std::cout << "generate num: " << num << std::endl;
        for (int index = 0; index < max_level_; index++) {
            if (powers_[index] >= num) 
                return index + 1;
        }
        return max_level_ + 1;
    }

    void dump() {
        for (int level = 0; level < max_level_; level++) {
            std::cout << "====== level: " << level << ", value: ";
            Node* cur = root_->next[level];
            while(cur) {
                std::cout << cur->value << " ";
                cur = cur->next[level];
            }
            std::cout << std::endl;
        }
    }

private:
    Node* root_;
    int powers_[max_level_];
};

int main() {
    SkipList list;
    list.add_node(2);
    list.add_node(5);
    list.add_node(6);

    list.del_node(2);
}