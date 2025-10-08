#include <iostream>
#include <vector>
using namespace std;

// 节点颜色定义
enum Color { RED, BLACK };

// 红黑树节点结构
struct Node {
    int value;          // 节点值
    int count;          // 重复值计数
    Color color;        // 节点颜色
    Node* left;         // 左子节点
    Node* right;        // 右子节点
    Node* parent;       // 父节点

    // 构造函数
    Node(int val) : value(val), count(1), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class dRedBlackTree {
private:
    Node* root;         // 根节点
    Node* TNULL;        // 哨兵节点，用于表示空节点

    // 初始化哨兵节点
    void initializeNULLNode(Node* node, Node* parent) {
        node->value = 0;
        node->count = 0;
        node->color = BLACK;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    // 左旋操作
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // 右旋操作
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // 插入后修复红黑树性质
    void fixInsert(Node* k) {
        Node* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    // 中序遍历辅助函数
    void inOrderHelper(Node* node, vector<int>& result) const {
        if (node != TNULL) {
            inOrderHelper(node->left, result);
            result.push_back(node->value); // 每个值只输出一次
            inOrderHelper(node->right, result);
        }
    }

public:
    // 构造函数
    dRedBlackTree() {
        TNULL = new Node(0);
        initializeNULLNode(TNULL, nullptr);
        root = TNULL;
    }

    // 插入值（支持重复值）
    void insert(int key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node* y = nullptr;
        Node* x = root;

        while (x != TNULL) {
            y = x;
            if (node->value == x->value) {
                // 如果值已存在，增加计数器并返回
                x->count++;
                delete node; // 释放新节点的内存
                return;
            }
            if (node->value < x->value) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->value < y->value) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    // 升序遍历
    vector<int> ascend() const {
        vector<int> result;
        inOrderHelper(root, result);
        return result;
    }
};

int main() {
    dRedBlackTree tree;

    // 测试插入
    tree.insert(10);
    tree.insert(20);
    tree.insert(20); // 插入重复值
    tree.insert(30);
    tree.insert(10); // 插入重复值
    tree.insert(50);

    // 升序输出测试
    vector<int> values = tree.ascend();
    cout << "升序输出: ";
    for (size_t i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;

    return 0;
}
