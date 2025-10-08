#include <iostream>
using namespace std;

class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    bool color; // true for red, false for black

    TreeNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
};

class RedBlackTree {
private:
    TreeNode* root;
    TreeNode* NIL; // 用作哨兵节点（代表空节点）
    
    // 左旋操作：维护平衡
    void leftRotate(TreeNode* x);
    
    // 右旋操作：维护平衡
    void rightRotate(TreeNode* y);
    
    // 插入修复操作：保证插入后红黑树性质不被破坏
    void insertFix(TreeNode* z);
   
    // 删除修复操作：保证删除后红黑树性质不被破坏
    void deleteFix(TreeNode* x);
   
    // 替换两个节点的子树
    void transplant(TreeNode* u, TreeNode* v);
   
    // 获取以某个节点为根的最小值节点
    TreeNode* minimum(TreeNode* x);
    
    // 中序遍历
    void inorderTraversal(TreeNode* node);

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(int key);
    void erase(int key);
    void find(int key);
    void ascend();
    void clear(TreeNode* node);
};

//构
RedBlackTree::RedBlackTree() {
    NIL = new TreeNode(0);
    NIL->color = false; // NIL always black
    root = NIL;
}

//析
RedBlackTree::~RedBlackTree() {
    clear(root);
    delete NIL;
}
//功能：clear 递归删除以某节点为根的子树
void RedBlackTree::clear(TreeNode* node) {
    if (node != NIL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void RedBlackTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;// y 的左子树成为 x 的右子树
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;// y 接管 x 的父节点
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;// x 成为 y 的左子树
    x->parent = y;
}

void RedBlackTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    y->left = x->right;// x 的右子树成为 y 的左子树
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;// x 接管 y 的父节点
    if (y->parent == NIL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y; // y 成为 x 的右子树
    y->parent = x;
}

//功能：插入
void RedBlackTree::insert(int key) {
    TreeNode* z = new TreeNode(key);
    TreeNode* y = NIL;
    TreeNode* x = root;

    // 找插入位置
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;// 设置 z 的父节点
    if (y == NIL) root = z;// 如果树为空，z 成为根节点
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    
    // 初始化新节点的左右子节点和颜色
    z->left = NIL;
    z->right = NIL;
    z->color = true; // 新插入节点为红色

    insertFix(z); // 修复红黑树性质
}

void RedBlackTree::insertFix(TreeNode* z) {
    // 当父节点为红，修复
    while (z->parent->color) {
        // 如果父节点是祖父节点的左子节点
        if (z->parent == z->parent->parent->left) {
            TreeNode* y = z->parent->parent->right;// z 的叔节点
            if (y->color) {// Case 1: 叔节点为红
                // 将父节点和叔叔节点涂黑，祖父节点涂红
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                // 将 z 移动到祖父节点，继续检查其上层
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {// Case 2: 叔黑，z 是右子节点
                    // 对父节点左旋，使 z 成为左子节点
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: 叔叔是黑，z 是左子节点
                // 将父节点涂黑，祖父节点涂红，对祖父节点右旋
                z->parent->color = false;
                z->parent->parent->color = true;
                rightRotate(z->parent->parent);
            }
        }
        else {
            // 如果父节点是祖父节点的右子节点，处理逻辑对称
            TreeNode* y = z->parent->parent->left;// y 是 z 的叔叔节点
            // Case 1: 叔红
            if (y->color) {
                // 将父节点和叔叔节点涂黑，祖父节点涂红
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                // 将 z 移动到祖父节点，继续检查其上层
                z = z->parent->parent;
            }
            else {
                // Case 2: 叔叔节点是黑色，且 z 是左子节点
                if (z == z->parent->left) {
                    // 对父节点右旋，使 z 成为右子节点
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: 叔叔节点是黑色，且 z 是右子节点
                // 将父节点涂黑，祖父节点涂红，对祖父节点左旋

                z->parent->color = false;
                z->parent->parent->color = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = false;// 根节点为黑色
}

//功能：删除节点
void RedBlackTree::erase(int key) {
    TreeNode* z = root;

    // 查找待删除节点
    while (z != NIL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }

    if (z == NIL) {// 如果节点不存在
        cout << "Key " << key << " not found.\n";
        return;
    }

    TreeNode* y = z;// y 是实际被删除的节点
    TreeNode* x; // x 是用于修复的节点
    bool yOriginalColor = y->color;// 记录 y 的颜色

    //删
    if (z->left == NIL) {
        // Case 1: z 没有左子树，用右子树替换 z
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        // Case 2: z 没有右子树，用左子树替换 z
        x = z->left;
        transplant(z, z->left);
    }
    else {
        // Case 3: z 有两个子树
       // 找到 z 的后继节点（右子树中的最小节点）
        y = minimum(z->right);// 找到后继节点
        yOriginalColor = y->color; //记录后继节点的颜色
        x = y->right;// 后继节点的右子树
       
        if (y->parent == z) {
            // 如果后继节点是 z 的直接子节点
            x->parent = y;// 设置 x 的父节点为 y
        }
        else {
            // 如果后继节点不是 z 的直接子节点
            transplant(y, y->right);// 用 y 的右子树替换 y
            y->right = z->right; // 将 z 的右子树赋给 y
            y->right->parent = y;
        }
        // 用后继节点替换 z 的位置
        transplant(z, y);
        y->left = z->left;// 将 z 的左子树赋给 y
        y->left->parent = y;
        y->color = z->color;// 保持 y 的颜色与 z 一致
    }

    delete z;// 删除节点
    if (!yOriginalColor) deleteFix(x);// 修复红黑树性质
}

void RedBlackTree::deleteFix(TreeNode* x) {
    // 修复时，只有当 x 不为根节点且 x 的颜色为黑色时继续处理
    while (x != root && !x->color) {
        if (x == x->parent->left) {
            // x 是其父节点的左子节点
            TreeNode* w = x->parent->right; // w 是 x 的兄弟节点
            // Case 1: 兄弟节点是红色
            if (w->color) {
                w->color = false;// 将兄弟节点涂黑
                x->parent->color = true; // 将父节点涂红
                leftRotate(x->parent);// 对父节点左旋
                w = x->parent->right; // 更新兄弟节点
            }
            // Case 2: 兄弟节点是黑色，且两个子节点也为黑色
            if (!w->left->color && !w->right->color) {
                w->color = true; // 将兄弟节点涂红
                x = x->parent; // 将问题上移到父节点
            }
            else {
                // Case 3: 兄弟节点是黑色，且兄弟的右子节点为黑色，左子节点为红色
                if (!w->right->color) {
                    w->left->color = false;// 将兄弟的左子节点涂黑
                    w->color = true; // 将兄弟节点涂红
                    rightRotate(w); // 对兄弟节点右旋
                    w = x->parent->right;// 更新兄弟节点
                }
                // Case 4: 兄弟节点是黑色，且兄弟的右子节点为红色
                w->color = x->parent->color;// 将兄弟节点的颜色设为父节点的颜色
                x->parent->color = false;// 将父节点涂黑
                w->right->color = false;// 将兄弟的右子节点涂黑
                leftRotate(x->parent); // 对父节点左旋
                x = root;
            }
        }
        else {
            // x 是其父节点的右子节点，处理逻辑与左子节点对称
            TreeNode* w = x->parent->left;
            // Case 1: 兄弟节点是红色
            if (w->color) {
                w->color = false;
                x->parent->color = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            // Case 2: 兄弟节点是黑色，且两个子节点也为黑色
            if (!w->right->color && !w->left->color) {
                w->color = true;
                x = x->parent;
            }
            else {
                // Case 3: 兄弟节点是黑色，且兄弟的左子节点为黑色，右子节点为红色
                if (!w->left->color) {
                    w->right->color = false;
                    w->color = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4: 兄弟节点是黑色，且兄弟的左子节点为红色
                w->color = x->parent->color;
                x->parent->color = false;
                w->left->color = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false; // 最后将 x 的颜色设为黑色，确保根节点是黑色
}

void RedBlackTree::transplant(TreeNode* u, TreeNode* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

TreeNode* RedBlackTree::minimum(TreeNode* x) {
    while (x->left != NIL) x = x->left;
    return x;
}

//功能：find
void RedBlackTree::find(int key) {
    TreeNode* current = root;
    while (current != NIL) {
        if (key == current->key) {
            cout << "Key " << key << " found"<<endl;
            return;
        }
        current = (key < current->key) ? current->left : current->right;
    }
    cout << "Key " << key << " not found"<<endl;
}

//功能：升序输出
void RedBlackTree::ascend() {
    inorderTraversal(root);
    cout << endl;
}

// 中序遍历的递归实现
void RedBlackTree::inorderTraversal(TreeNode* node) {
    if (node != NIL) {
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }
}

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);

    cout << "Ascending order: ";
    tree.ascend();
    cout << endl;

    tree.find(15);
    tree.find(30);
    cout << endl;

    tree.erase(15);
    cout << "After deleting 15: ";
    tree.ascend();

    return 0;
}
