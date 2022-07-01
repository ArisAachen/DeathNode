#include <iostream>

struct Node {
    int value;
    Node* next;
    Node() {
        value = 0;
        next = nullptr;
    }
    Node(int vl) {
        value = vl;
        next = nullptr;
    }
};

class List {
public:
    List() {
    }

    void add_node(int value) {
        if (!head_) {
            head_ = new Node(value);
            dump();
            return;
        }
        Node* cur = head_;
        Node* tmp = cur;
        while(cur && cur->value < value) {
            tmp = cur;
            cur = cur->next;
        }
        if (cur == head_) {
            Node* node = new Node(value);
            node->next = head_;
            head_ = node;
            dump();
            return;
        }
        Node* node = new Node(value);
        tmp->next = node;
        dump();
    }

    void del_node(int value) {
        if (!head_) {
            dump();
            return;
        }
        Node* cur = head_;
        Node* tmp = cur;
        while (cur && cur->value != value) {
            tmp = cur;
            cur = cur->next;
        }
        if (cur == head_) {
            head_ = cur->next;
            delete cur;
            dump();
            return;
        }
        if (cur == nullptr) {
            dump();
            return;
        }
        tmp->next = cur->next;
        delete cur;
        dump();
    }

    void dump() {
        std::cout << "====== begin to dump" << std::endl;
        Node* cur = head_;
        while (cur) {
            std::cout << cur->value << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
        std::cout << "====== end to dump" << std::endl;
        std::cout << std::endl;
    }

private:
    Node* head_ {nullptr};
};

int main() {
    List test;
    test.add_node(2);
    test.add_node(3);
    test.add_node(1);

    test.del_node(1);
    test.del_node(3);
}