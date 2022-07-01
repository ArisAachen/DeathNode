#include <iostream>

struct Node {
    Node() : Node(0, nullptr, nullptr) {}
    Node(int vl, Node* p = nullptr, Node* n = nullptr) :
    value(vl), pre(p), next(n) {}
    int value {0};
    Node* pre {nullptr};
    Node* next {nullptr};
};

class DoubleList {
public:
    void add_to_head(int value) {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = tail_ = node;
            dump_vor();
            dump_bak();
            return;
        }
        node->next = head_;
        head_->pre = node;
        head_ = node;
        dump_vor();
        dump_bak();        
    }

    void del_from_head() {
        if (head_ == nullptr)
            return;
        if (head_ == tail_) {
            delete head_;
            head_ = tail_ = nullptr;
            dump_vor();
            dump_bak();            
            return;
        }
        Node* tmp = head_;
        head_ = head_->next;
        head_->pre = nullptr;
        delete tmp;
        dump_vor();
        dump_bak();     
    }

    void add_to_tail(int value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = tail_ = node;
            dump_vor();
            dump_bak();
            return;
        }
        tail_->next = node;
        node->pre = tail_;
        tail_ = node;
        dump_vor();
        dump_bak();        
    }

    void del_from_tail() {
        if (tail_ == nullptr) 
            return;
        if (head_ == tail_) {
            delete tail_;
            head_ = tail_ = nullptr;
            dump_vor();
            dump_bak();
            return;
        }
        Node* tmp = tail_;
        tail_ = tail_->pre;
        tail_->next = nullptr;
        delete tmp;
        dump_vor();
        dump_bak();
    }

    void dump_vor() {
        Node* cur = head_;
        std::cout << "===== dump vor =====" << std::endl;
        while (cur) {
            std::cout << cur->value << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
        std::cout << "===== dump vor =====" << std::endl;
    }

    void dump_bak() {
        Node* cur = tail_;
        std::cout << ">>>>>> dump bak <<<<<<" << std::endl;
        while (cur) {
            std::cout << cur->value << " ";
            cur = cur->pre;
        }
        std::cout << std::endl;
        std::cout << ">>>>>> dump bak <<<<<<" << std::endl;
    }

private:
    Node* head_ {nullptr};
    Node* tail_ {nullptr};
};

int main() {
    DoubleList list;
    list.add_to_head(2);
    list.add_to_head(1);
    list.add_to_tail(3);

    list.del_from_head();
    list.del_from_tail();

    return 1;
}