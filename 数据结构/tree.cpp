#include <algorithm>
#include <iostream>

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

class TreeNode {

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
 * 6. 当标记节点被 pop 时, 说明某个节点的右子树已经被输出, 此时可以输出子树的根节点, 
 *    即从 saved_node 中取出元素, 用于输出
 * 7. 由于 saved_node 中的元素, 可能也是节点的 右子树, 所以需要遍历
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


int main() {
    test_preorder_stack();
    test_preorder();

    test_inorder_stack();
    test_inorder();

    test_postorder_stack();
    test_postorder();

    return 1;
}