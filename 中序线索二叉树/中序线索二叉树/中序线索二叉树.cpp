#include <iostream>
using namespace std;

// 定义中序线索二叉树节点
struct TBiTreeNode {
    int value;
    TBiTreeNode* left;
    TBiTreeNode* right;
    bool left_thread;
    bool right_thread;
};

// 中序线索化二叉树
void inorder_thread(TBiTreeNode* root, TBiTreeNode*& prev) {
    if (root == nullptr) {
        return;
    }

    inorder_thread(root->left, prev);

    // 处理当前节点的前驱
    if (root->left == nullptr) {
        root->left_thread = true;
        root->left = prev;
    }

    // 处理前驱的后继
    if (prev != nullptr && prev->right == nullptr) {
        prev->right_thread = true;
        prev->right = root;
    }

    prev = root;
    inorder_thread(root->right, prev);
}

// 中序遍历二叉树
void inorder_traversal(TBiTreeNode* root) {
    TBiTreeNode* curr = root;
    while (curr != nullptr) {
        while (curr->left_thread == false) {
            curr = curr->left;
        }
        cout << curr->value << " ";
        while (curr->right_thread == true) {
            curr = curr->right;
            cout << curr->value << " ";
        }
        curr = curr->right;
    }
    cout << endl;
}

// 构建中序线索二叉树
TBiTreeNode* build_threaded_binary_tree() {
    TBiTreeNode* node1 = new TBiTreeNode{ 1, nullptr, nullptr, false, false };
    TBiTreeNode* node2 = new TBiTreeNode{ 2, nullptr, nullptr, false, false };
    TBiTreeNode* node3 = new TBiTreeNode{ 3, nullptr, nullptr, false, false };
    TBiTreeNode* node4 = new TBiTreeNode{ 4, nullptr, nullptr, false, false };
    TBiTreeNode* node5 = new TBiTreeNode{ 5, nullptr, nullptr, false, false };
    TBiTreeNode* node6 = new TBiTreeNode{ 6, nullptr, nullptr, false, false };
    TBiTreeNode* node7 = new TBiTreeNode{ 7, nullptr, nullptr, false, false };
    TBiTreeNode* node8 = new TBiTreeNode{ 8, nullptr, nullptr, false, false };

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    node5->right = node8;

    TBiTreeNode* prev = nullptr;
    inorder_thread(node1, prev);

    return node1;
}

int main() {
    TBiTreeNode* root = build_threaded_binary_tree();
    inorder_traversal(root);
    return 0;
}