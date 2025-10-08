#include <iostream>
using namespace std;

// ���������ڵ���ɫ
enum Color { RED, BLACK };

// ������ڵ�ṹ
struct Node {
    int key;            // �ؼ��֣�ֵ��
    Color color;        // �ڵ���ɫ
    Node* left;         // ���ӽڵ�
    Node* right;        // ���ӽڵ�
    Node* parent;       // ���ڵ�

    // ���캯��
    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ȫ�ֱ��������ڵ�
Node* root = nullptr;

// ����
void leftRotate(Node*& root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// ����
void rightRotate(Node*& root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// ������Сֵ�ڵ�
Node* minimum(Node* x) {
    while (x->left) x = x->left;
    return x;
}

// �޸�ɾ����ĺ��������
void fixDelete(Node*& root, Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {  // Case 1: x ���ֵ��Ǻ�ɫ
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2: �ֵܵ������ӽڵ㶼�Ǻ�ɫ
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) { // Case 3: �ֵܵ����ӽڵ��Ǻ�ɫ�����ӽڵ��Ǻ�ɫ
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // Case 4: �ֵܵ����ӽڵ��Ǻ�ɫ
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
        }
        else {  // �Գ������x �����ӽڵ�
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// ������ u �滻Ϊ���� v
void transplant(Node*& root, Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;  // u �Ǹ��ڵ㣬ֱ�Ӹ��¸��ڵ�
    }
    else if (u == u->parent->left) {
        u->parent->left = v;  // u ���丸�ڵ�����ӽڵ�
    }
    else {
        u->parent->right = v; // u ���丸�ڵ�����ӽڵ�
    }
    if (v != nullptr) {
        v->parent = u->parent;  // ���� v �ĸ��ڵ�Ϊ u �ĸ��ڵ�
    }
}

// ɾ���ڵ�
void deleteNode(Node*& root, Node* z) {
    Node* y = z;
    Node* x;
    Color originalColor = y->color;

    if (!z->left) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (originalColor == BLACK) fixDelete(root, x);
}

// �޸���������ʣ�z ���²���Ľڵ�
void fixInsert(Node*& root, Node* z) {
    while (z != root && z->parent->color == RED) {  // ���ڵ��Ǻ�ɫ��Υ������ 4
        if (z->parent == z->parent->parent->left) {  // ���ڵ����游�ڵ�����ӽڵ�
            Node* uncle = z->parent->parent->right;  // ����ڵ�
            if (uncle != nullptr && uncle->color == RED) {  // Case 1: �����Ǻ�ɫ
                z->parent->color = BLACK;  // ���ڵ���
                uncle->color = BLACK;      // ����ڵ���
                z->parent->parent->color = RED;  // �游�ڵ���
                z = z->parent->parent;  // ���������޸�
            }
            else {
                if (z == z->parent->right) {  // Case 2: z �Ǹ��ڵ�����ӽڵ�
                    z = z->parent;
                    leftRotate(root, z);  // ����
                }
                // Case 3: z �Ǹ��ڵ�����ӽڵ�
                z->parent->color = BLACK;        // ���ڵ���
                z->parent->parent->color = RED;  // �游�ڵ���
                rightRotate(root, z->parent->parent);  // ����
            }
        }
        else {  // �Գ���������ڵ����游�ڵ�����ӽڵ�
            Node* uncle = z->parent->parent->left;  // ����ڵ�
            if (uncle != nullptr && uncle->color == RED) {  // Case 1: �����Ǻ�ɫ
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {  // Case 2: z �Ǹ��ڵ�����ӽڵ�
                    z = z->parent;
                    rightRotate(root, z);  // ����
                }
                // Case 3: z �Ǹ��ڵ�����ӽڵ�
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);  // ����
            }
        }
    }
    root->color = BLACK;  // ��֤���ڵ�ʼ���Ǻ�ɫ������ 2��
}

// ����ڵ�ĸ�������
void insert(Node*& root, int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (!y) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    fixInsert(root, z);
}

// �������
void ascend(Node* root) {
    if (root) {
        ascend(root->left);
        cout << root->key << " ";
        ascend(root->right);
    }
}

// ���Գ���
int main() {
    insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 15);

    cout << "Tree before deletion: ";
    ascend(root);
    cout << endl;

    deleteNode(root, root->left); // ɾ��ĳ���ڵ�
    cout << "Tree after deletion: ";
    ascend(root);
    cout << endl;

    return 0;
}
