#include <algorithm>
#include <iostream>
#include <stdexcept>

// 兄弟-儿子表示法
struct TreeNode_Child_Sibling {
    int value;
    TreeNode_Child_Sibling* child;  // 指向儿子
    TreeNode_Child_Sibling* sibling;   // 指向兄弟
};

struct BinaryTreeNode {
    BinaryTreeNode(int vl) : value(vl) {
    }

    int value {0};
    BinaryTreeNode* left {nullptr};
    BinaryTreeNode* right {nullptr};
};

int max(int first, int second) {
    if (first > second) 
        return first;
    return second;
}

int tree_deepth(BinaryTreeNode* node) {
    if (node == nullptr) 
        return 0;
    return max(tree_deepth(node->left), tree_deepth(node->right)) + 1;
};

#include <cmath>
bool is_balance(BinaryTreeNode* node) {
    if (!node)  
        return true;
    return is_balance(node->left) && is_balance(node->right) && 
        (abs(tree_deepth(node->left) - tree_deepth(node->right)) < 2);
}


#include <stack>
// 前序遍历
void preorder(BinaryTreeNode* node) {
    if (!node)
        return;
    std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
};

void preorder_stack(BinaryTreeNode* node) {
    std::stack<BinaryTreeNode*> tree_stack;
    while (node || !tree_stack.empty()) {
        if (node) {
            std::cout << node->value << " ";
            tree_stack.push(node);
        }
        if (node && node->left)
            node = node->left;
        else {
            auto back = tree_stack.top();
            tree_stack.pop();
            node = back->right;
        }
    }
}

// 中序遍历
void inorder(BinaryTreeNode* node) {
    if (!node)
        return;
    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
}

void inorder_stack(BinaryTreeNode* node) {
    std::stack<BinaryTreeNode*> tree_stack;
    while (node || !tree_stack.empty()) {
        if (node)
            tree_stack.push(node);
        if (node && node->left)
            node = node->left;
        else {
            auto back = tree_stack.top();
            std::cout << back->value << " ";
            tree_stack.pop();
            node = back->right;
        }
    }
    std::cout << std::endl;
}

// 后序遍历
void postorder(BinaryTreeNode* node) {
    if (!node)
        return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " ";
}

#include <vector>
/**
 * @brief 后序遍历的堆栈删除
 * @details 
 * 1. 后序遍历的顺序 左右根
 * 2. 先判断还有没有 左子树, 如果有的, 继续寻找下一个节点
 * 3. 如果没有左节点了, 说明已经是最左边了, 从栈中推出一个数, 进入下一步
 * 4. 判断该节点是否存在右子树, 如果存在此节点是子树的根节点, 需要延迟输出, 进入延迟输出逻辑
 * 5. 延迟判断, 将右子树设为标记节点(添加进), 并把当前节点存入 saved_node栈, 作为延迟输出
 * 6. 当标记节点被 pop 时, 说明某个节点的右子树已经被输出, 此时可以输出子树的根节点
 */
void postorder_stack(BinaryTreeNode* node) {
    std::stack<BinaryTreeNode*> tree_stack;
    std::vector<BinaryTreeNode*> mark_node;
    std::stack<BinaryTreeNode*> saved_node;
    while (node || !tree_stack.empty()) {
        if (node)
            tree_stack.push(node);
        if (node && node->left)
            node = node->left;
        else {
            auto back = tree_stack.top();
            tree_stack.pop();
            if (back->right) {
                saved_node.push(back);
                mark_node.push_back(back->right);
                node = back->right;
            } else {
                std::cout << back->value << " ";
                while (std::find(mark_node.begin(), mark_node.end(), 
                    back) != mark_node.end()) {
                    auto pos = std::remove(mark_node.begin(), mark_node.end(), back);
                    mark_node.erase(pos, mark_node.end());
                    back = saved_node.top();
                    saved_node.pop();
                    std::cout << back->value << " ";
                }
                node = nullptr;
            }
        }
    }
    std::cout << std::endl;
}


BinaryTreeNode* create_node() {
    BinaryTreeNode* root = new BinaryTreeNode(1);

    BinaryTreeNode* node_2 = new BinaryTreeNode(2);
    root->left = node_2;

    BinaryTreeNode* node_3 = new BinaryTreeNode(3);
    root->right = node_3;

    BinaryTreeNode* node_4 = new BinaryTreeNode(4);
    node_2->left = node_4;

    BinaryTreeNode* node_5 = new BinaryTreeNode(5);
    node_2->right = node_5;

    BinaryTreeNode* node_6 = new BinaryTreeNode(6);
    node_3->left = node_6;

    BinaryTreeNode* node_7 = new BinaryTreeNode(7);
    node_3->right = node_7;

    BinaryTreeNode* node_8 = new BinaryTreeNode(8);
    node_5->left = node_8; 

    BinaryTreeNode* node_9 = new BinaryTreeNode(9);
    node_5->right = node_9;

    BinaryTreeNode* node_10 = new BinaryTreeNode(10);
    node_9->left = node_10;

    return root;
}

BinaryTreeNode* create_balance_tree() {
    BinaryTreeNode* root = new BinaryTreeNode(10);

    BinaryTreeNode* node_2 = new BinaryTreeNode(5);
    root->left = node_2;

    BinaryTreeNode* node_3 = new BinaryTreeNode(11);
    root->right = node_3;

    BinaryTreeNode* node_4 = new BinaryTreeNode(3);
    node_2->left = node_4;

    BinaryTreeNode* node_5 = new BinaryTreeNode(6);
    node_2->right = node_5;

    return root;
}

void test_preorder_stack() {
    std::cout << "===== preorder stack =====" << std::endl;
    auto root = create_node();
    preorder_stack(root);
    std::cout << std::endl;
    std::cout << "===== preorder stack =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_preorder() {
    std::cout << "===== preorder =====" << std::endl;
    auto root = create_node();
    preorder(root); 
    std::cout << std::endl;
    std::cout << "===== preorder =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_inorder_stack() {
    std::cout << "===== inorder stack =====" << std::endl;
    auto root = create_node();
    inorder_stack(root);
    std::cout << "===== inorder stack =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_inorder() {
    std::cout << "===== inorder =====" << std::endl;
    auto root = create_node();
    inorder(root); 
    std::cout << std::endl;
    std::cout << "===== inorder =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_postorder_stack() {
    std::cout << "===== postorder stack =====" << std::endl;
    auto root = create_node();
    postorder_stack(root);
    std::cout << "===== postorder stack =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_postorder() {
    std::cout << "===== postorder =====" << std::endl;
    auto root = create_node();
    postorder(root); 
    std::cout << std::endl;
    std::cout << "===== postorder =====" << std::endl;
    std::cout << std::endl << std::endl;
}

void test_is_balance() {
    std::cout << "===== is balance =====" << std::endl;
    auto node = create_node();
    std::cout << "is balance: " << std::boolalpha << is_balance(node) << std::endl;
    std::cout << "===== is balance =====" << std::endl;
    std::cout << std::endl << std::endl;
}

// tree
#include <limits>
class BinaryTree {
public:
    void insert_node(int value) {
        if (root_ == nullptr) {
            root_ = new BinaryTreeNode(value);
            dump_preorder();
            return;
        }
        BinaryTreeNode* cur = root_;
        while (cur) {
            if (cur->value > value) {
                if (cur->left) 
                    cur = cur->left;
                else {
                    cur->left = new BinaryTreeNode(value);
                    break;
                }
            }
            else if (cur->value < value) 
                if (cur->right) 
                    cur = cur->right;
                else {
                    cur->right = new BinaryTreeNode(value);
                    break;
                }
            else 
                throw "value already exist";
        }
        dump_preorder();
    }

    BinaryTreeNode* search(int value) {
        BinaryTreeNode* cur = root_;
        while (cur) {
            if (cur->value > value)
                cur = cur->left;
            else if (cur->value < value)
                cur = cur->right;
            else 
                break;
        }
        return cur;
    }

    void delete_node(int value) {
        
    }

    void dump_preorder() {
        std::cout << "===== tree preorder =====" << std::endl;
        preorder_stack(root_);
        std::cout << std::endl;
        std::cout << "===== tree preorder =====" << std::endl;
        std::cout << std::endl << std::endl;
    }

    BinaryTreeNode* min() {
        BinaryTreeNode* cur = root_, *pre;
        while (cur) {
            pre = cur;
            cur = cur->left;
        }
        return pre;
    }

    BinaryTreeNode* max() {
        return max(root_);
    }

private:
    BinaryTreeNode* max(BinaryTreeNode* node) {
        BinaryTreeNode* cur = node, *pre = nullptr;
        while (cur) {
            pre = cur;
            cur = cur->right;
        }
        return pre;        
    }

private:
    BinaryTreeNode* root_ {nullptr};
};


BinaryTreeNode* right_rotation(BinaryTreeNode* node) {
    if (!node)
        return node;
    std::cout << "right rotation node is: " << node->value << std::endl;
    BinaryTreeNode* left_node = node->left;
    BinaryTreeNode* left_right_node = left_node->right;
    left_node->right = node;
    node->left = left_right_node;
    return left_node;
};

BinaryTreeNode* left_rotation(BinaryTreeNode* node) {
    if (!node)
        return node;
    BinaryTreeNode* right_node = node->right;
    BinaryTreeNode* right_left_node = right_node->left;
    right_node->left = node;
    node->right = right_left_node;
    return right_node;
}

BinaryTreeNode* right_left_rotation(BinaryTreeNode* node) {
    if (!node)
        return node;
    node->left = left_rotation(node->left);
    return right_rotation(node);
}

BinaryTreeNode* left_right_rotation(BinaryTreeNode* node) {
    if (!node)
        return node;
    node->right = right_rotation(node->right);
    return left_rotation(node);
}

BinaryTreeNode* balance_insert(BinaryTreeNode* node, int value) {
    if (!node)
        return new BinaryTreeNode(value);
    if (node->value > value) 
        node->left = balance_insert(node->left, value);
    else if (node->value < value) 
        node->right = balance_insert(node->right, value);
    else 
        throw std::logic_error("value already exist");
    int sub = tree_deepth(node->left) - tree_deepth(node->right);
    if (sub > 1 && node->left && node->left->value > value) 
        node = right_rotation(node);
    else if (sub > 1 && node->left && node->left->value < value) 
        node  = right_left_rotation(node);
    else if (sub < -1 && node->right && node->right->value < value)
        node = left_rotation(node);
    else if (sub < -1 && node->right && node->right->value > value)
        node = left_right_rotation(node);
    return node;
}

BinaryTreeNode* balance_delete(BinaryTreeNode* node, int value) {
    if (!node)
        throw std::logic_error("node is empty");
    else if (node->value < value)   
        node->right = balance_delete(node->right, value);
    else if (node->value > value) 
        node->left = balance_delete(node->left, value);
    else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (node->left && !node->right) {
            delete node;
            node = node->left;
        } else if (!node->left && node->right) {
            delete node;
            node = node->right;
        } else {
            
        }
    }
}


class BalanceTree {
public:
    void insert_node(int value) {
        root_ = balance_insert(root_, value);
        std::cout << "balance tree now is: ";
        preorder_stack(root_);
        std::cout << std::endl << std::endl;
    }

    void delete_node(int value) {

    }

    BinaryTreeNode* search_node(int value) {
        
    }

private:
    BinaryTreeNode* root_ {nullptr};
};

void test_binary_tree_insert() {
    BinaryTree tree;
    tree.insert_node(4);
    tree.insert_node(2);
    tree.insert_node(5);
    tree.insert_node(3);
    tree.insert_node(1);

    std::cout << "binary tree min: " << tree.min()->value << std::endl;
    std::cout << "binary tree max: " << tree.max()->value << std::endl;
}

void test_balance_tree_insert() {
    std::cout << "===== binary tree insert =====" << std::endl;
    BinaryTreeNode* tree = create_balance_tree();
    tree = balance_insert(tree, 1);
    std::cout << "preorder: ";
    preorder_stack(tree);
    std::cout << std::endl;
    std::cout << "===== binary tree insert =====" << std::endl;
}


int main() {
    test_preorder_stack();
    test_preorder();

    test_inorder_stack();
    test_inorder();

    test_postorder_stack();
    test_postorder();

    test_is_balance();

    test_binary_tree_insert();


    test_balance_tree_insert();

    return 1;
}