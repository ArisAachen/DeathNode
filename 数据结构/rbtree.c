
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * 强查找过程
 * 1. rbtree
 * 2. hash
 * 3. b/b+
 * 4. skip list
 */

/**
 * 红黑树性质
 * 1. 一个节点 必须是 红色或者黑色
 * 2. 根节点是黑色的
 * 3. 叶子节点是黑色的 (nil)
 * 4. 红色父节点的子节点必须是黑色的
 * 5. 节点到子孙节点的路径是一样的 
 */

enum Color: unsigned char {
    Red,
    Black
};

#define RBTREE_ENTRY(name, type)    \
    struct name {                   \
        struct type* left;          \
        struct type* right;         \
        struct type* parent;        \
        unsigned char color;        \
    }

typedef struct _rbtree_node {
#ifdef USE_RBTREE
    RBTREE_ENTRY(, _rbtree_node) node;
#else 
    struct _rbtree_node* left;
    struct _rbtree_node* right;
    struct _rbtree_node* parent;
    unsigned char color;
#endif
    int key;
    void* value;
} rbtree_node;

typedef struct _rbtree {
    struct _rbtree_node* root;
    struct _rbtree_node* nil;
} rbtree;

void left_rotation(rbtree* tree, rbtree_node* node) {
    if (tree->root == nullptr || node->right == nullptr ||
        node->right == tree->nil)
        assert(false);

    // get node
    rbtree_node* right_node = node->left;
    rbtree_node* child_node = right_node->left;
    rbtree_node* parent_node = node->parent;

    // change node
    right_node->left = node;
    node->right = child_node;

    // change parent
    right_node->parent = parent_node;
    if (tree->root == node)
        tree->root = right_node;
    else if (parent_node->left == node)
        parent_node->left = right_node;
    else if (parent_node->right == node)
        parent_node->right = node;

    node->parent = right_node;
    child_node->parent = node;
}

void right_rotation(rbtree* tree, rbtree_node* node) {
    if (tree->root == nullptr || node->left == nullptr ||
        node->left == tree->nil)
        assert(false);
    rbtree_node* left_node = node->left;
    rbtree_node* child_node = left_node->right;
    rbtree_node* parent_node = node->parent;

    // child node
    child_node->parent = node;
    node->left = child_node;

    // left node
    left_node->right = node;
    node->parent = left_node;

    // node
    left_node->parent = parent_node;
    if (tree->root == node)
        tree->root = left_node;
    else if (parent_node->left == node)
        parent_node->left = left_node;
    else if (parent_node->right == node) 
        parent_node->right = left_node;
}

void rbtree_insert_fixup(rbtree* tree, rbtree_node* node) {
    rbtree_node *parent, *uncle, *grand_parent;
    parent = node->parent;
    grand_parent = parent->parent;
    while (parent->color == Red) {
        // parent is grand parent left
        if (parent == grand_parent->left) {
            uncle = grand_parent->right;
            // uncle color is red
            if (uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                grand_parent->color = Red;
                // check grand parent`s parent color
                node = grand_parent;
                parent = node->parent;
            } else {
                if (node == parent->right) {
                    right_rotation(tree, node);
                    node = node->parent;
                }
                parent->color = Black;
                grand_parent->color = Red;
                right_rotation(tree, grand_parent);
            }

        } else {
            // parent is grand parent right
            uncle = grand_parent->left;
            if (uncle->color == Red) {
                parent->color = Black;
                grand_parent->color = Red;
                uncle->color = Black;
                node = grand_parent;
                parent = node->parent;
            } else {
                if (node == parent->left) {
                    left_rotation(tree, node);
                    node = node->parent;
                }
                parent->color = Black;
                grand_parent->color = Red;
                left_rotation(tree, grand_parent);
            }
        }

    }
}

void rbtree_insert(rbtree* tree, rbtree_node* node) {
    rbtree_node* pre,* cur;
    cur  = tree->root;
    while (cur != tree->nil) {
        pre = cur;
        if (cur->key > node->key) 
            cur = node->left;
        else if (cur->key < node->key)
            cur = node->right;
        else 
            return;
    }

    // not tree
    if (pre == tree->nil)
        tree->root = node;
    else if (pre->key > node->key)
        pre->left = node;
    else if (pre->key < node->key)
        pre->right = node;

    node->parent = pre;
    node->left = tree->nil;
    node->right = tree->nil;
    node->color = Red;

    rbtree_insert_fixup(tree, node);
}