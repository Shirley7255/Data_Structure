#include <iostream>
#include <vector>
using namespace std;

// �ڵ���ɫ����
enum Color { RED, BLACK };

// ������ڵ�
struct Node {
    int value;          // �ڵ�ֵ
    Color color;        // �ڵ���ɫ
    Node* left;         // ���ӽڵ�
    Node* right;        // ���ӽڵ�
    Node* parent;       // ���ڵ�

    // ���캯��
    Node(int val) : value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class dRedBlackTree {
private:
    Node* root;         // ���ڵ�
    Node* TNULL;        // �ڱ��ڵ㣬���ڱ�ʾ�սڵ�

    // ��ʼ���ڱ��ڵ�
    void initializeNULLNode(Node* node, Node* parent) {
        node->value = 0;
        node->color = BLACK;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    // ��������
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

    // ��������
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

    // ������޸����������
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

    // ���������������
    void inOrderHelper(Node* node, vector<int>& result) const {
        if (node != TNULL) {
            inOrderHelper(node->left, result);
            result.push_back(node->value);
            inOrderHelper(node->right, result);
        }
    }

public:
    // ���캯��
    dRedBlackTree() {
        TNULL = new Node(0);
        initializeNULLNode(TNULL, nullptr);
        root = TNULL;
    }

    // ����ֵ
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

    // �������
    vector<int> ascend() const {
        vector<int> result;
        inOrderHelper(root, result);
        return result;
    }
};

int main() {
    dRedBlackTree tree;

    // ���Բ���
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(50);
    // �����������
    vector<int> values = tree.ascend();
    cout << "��ֵ�������: ";
    for (size_t i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;

    return 0;
}
