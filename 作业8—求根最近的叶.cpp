#include <iostream>
#include <queue>
using namespace std;


struct AVLNode {
    int key;               
    AVLNode* left;         
    AVLNode* right;        

    AVLNode(int k) : key(k), left(nullptr), right(nullptr) {}
};


int findLeaf(AVLNode* root) {
    if (root == nullptr) {
        throw runtime_error("Tree is empty"); // 空树时抛出异常
    }

    
    queue<AVLNode*> q;
    q.push(root);

    while (!q.empty()) {
        AVLNode* current = q.front();
        q.pop();

        // 遍历树每一层，如果当前节点是叶节点，即为所求
        if (current->left == nullptr && current->right == nullptr) {
            return current->key;
        }

        // 将子节点加入队列
        if (current->left!=nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    throw runtime_error("No leaf node found"); // 理论上不会触发
}


int main() {
 //        10
 //       / \
 //      5   15
 //     / \    \
 //    3   7    20
 //   /     \
 //  4      14

    AVLNode* root = new AVLNode(10);
    root->left = new AVLNode(5);
    root->right = new AVLNode(15);
    root->left->left = new AVLNode(3);
    root->left->right = new AVLNode(7);
    root->right->right = new AVLNode(20);
    root->left->left->left = new AVLNode(4);
    root->left->right->right = new AVLNode(14);

    try {
        
        cout << "Closest leaf node value: " << findLeaf(root) << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    delete root->left->left->left;
    delete root->left->right->right;
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->right;
    delete root->right;
    delete root;

    return 0;
}
