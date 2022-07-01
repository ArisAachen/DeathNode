#include <ctime>
#include <iostream>

struct Node {
    int value;
    Node* next;
    Node(int vl, Node* n = nullptr) {
        value = vl;
        next = n;
    }
};

class RingList {
public:
    void add_to_head(int value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            tail_ = node;
            tail_->next = tail_;
            dump_3_times();
            return;
        }
        node->next = tail_->next;
        tail_->next = node;
        dump_3_times();
    }

    void del_from_head() {
        if (tail_ == nullptr) 
            return;
        if (tail_ == tail_->next) {
            delete tail_;
            tail_= nullptr;
            dump_3_times();
            return;
        }
        Node* head = tail_->next;
        tail_->next = head->next;
        delete head;
        dump_3_times();
    }

    void add_to_tail(int value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            tail_ = node;
            tail_->next = tail_;
            dump_3_times();
            return;
        }
        node->next = tail_->next;
        tail_ = node;
        dump_3_times();
    }

    void del_from_tail() {
        if (tail_ == nullptr) 
            return;
        if (tail_ == tail_->next) {
            delete tail_;
            tail_= nullptr;
            dump_3_times();
            return;
        }
        Node* end = tail_->next;
        while (end && end->next != tail_)
            end = end->next;
        end->next = tail_->next;
        tail_ = end;
        dump_3_times();
    }

    void dump_3_times() {
        for (int index = 0; index < 3; index++) {
            std::cout << "====== dump: " << index << " time begin" << std::endl;
            dump();
            std::cout << "====== dump: " << index << " time end" << std::endl;
        }
    }

private:
    void dump() {
        Node* cur = tail_->next;
        bool again = false;
        while(cur && !again) {
            std::cout << cur->value << " ";
            cur = cur->next;
            if (cur == tail_->next)
                again = true;
        }
        std::cout << std::endl;
    }

private:
    Node* tail_ {nullptr};
};

int main() {
    RingList list;
    list.add_to_head(2);
    list.add_to_tail(3);
    list.add_to_head(1);

    list.del_from_tail();
    list.del_from_head();
    return 1;
}