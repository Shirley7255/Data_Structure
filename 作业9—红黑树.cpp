#include <iostream>
using namespace std;

// 定义红黑树节点颜色
enum Color { RED, BLACK };

// 红黑树节点结构
struct Node {
    int key;            // 关键字（值）
    Color color;        // 节点颜色
    Node* left;         // 左子节点
    Node* right;        // 右子节点
    Node* parent;       // 父节点

    // 构造函数
    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// 全局变量：根节点
Node* root = nullptr;

// 左旋
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

// 右旋
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

// 查找最小值节点
Node* minimum(Node* x) {
    while (x->left) x = x->left;
    return x;
}

// 修复删除后的红黑树性质
void fixDelete(Node*& root, Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {  // Case 1: x 的兄弟是红色
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2: 兄弟的两个子节点都是黑色
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) { // Case 3: 兄弟的左子节点是红色，右子节点是黑色
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // Case 4: 兄弟的右子节点是红色
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
        }
        else {  // 对称情况：x 是右子节点
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

// 将子树 u 替换为子树 v
void transplant(Node*& root, Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;  // u 是根节点，直接更新根节点
    }
    else if (u == u->parent->left) {
        u->parent->left = v;  // u 是其父节点的左子节点
    }
    else {
        u->parent->right = v; // u 是其父节点的右子节点
    }
    if (v != nullptr) {
        v->parent = u->parent;  // 更新 v 的父节点为 u 的父节点
    }
}

// 删除节点
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

// 修复红黑树性质，z 是新插入的节点
void fixInsert(Node*& root, Node* z) {
    while (z != root && z->parent->color == RED) {  // 父节点是红色，违反性质 4
        if (z->parent == z->parent->parent->left) {  // 父节点是祖父节点的左子节点
            Node* uncle = z->parent->parent->right;  // 叔叔节点
            if (uncle != nullptr && uncle->color == RED) {  // Case 1: 叔叔是红色
                z->parent->color = BLACK;  // 父节点变黑
                uncle->color = BLACK;      // 叔叔节点变黑
                z->parent->parent->color = RED;  // 祖父节点变红
                z = z->parent->parent;  // 继续向上修复
            }
            else {
                if (z == z->parent->right) {  // Case 2: z 是父节点的右子节点
                    z = z->parent;
                    leftRotate(root, z);  // 左旋
                }
                // Case 3: z 是父节点的左子节点
                z->parent->color = BLACK;        // 父节点变黑
                z->parent->parent->color = RED;  // 祖父节点变红
                rightRotate(root, z->parent->parent);  // 右旋
            }
        }
        else {  // 对称情况：父节点是祖父节点的右子节点
            Node* uncle = z->parent->parent->left;  // 叔叔节点
            if (uncle != nullptr && uncle->color == RED) {  // Case 1: 叔叔是红色
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {  // Case 2: z 是父节点的左子节点
                    z = z->parent;
                    rightRotate(root, z);  // 右旋
                }
                // Case 3: z 是父节点的右子节点
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);  // 左旋
            }
        }
    }
    root->color = BLACK;  // 保证根节点始终是黑色（性质 2）
}

// 插入节点的辅助函数
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

// 中序遍历
void ascend(Node* root) {
    if (root) {
        ascend(root->left);
        cout << root->key << " ";
        ascend(root->right);
    }
}

// 测试程序
int main() {
    insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 15);

    cout << "Tree before deletion: ";
    ascend(root);
    cout << endl;

    deleteNode(root, root->left); // 删除某个节点
    cout << "Tree after deletion: ";
    ascend(root);
    cout << endl;

    return 0;
}
