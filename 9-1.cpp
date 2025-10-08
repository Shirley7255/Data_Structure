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
    TreeNode* NIL; // �����ڱ��ڵ㣨����սڵ㣩
    
    // ����������ά��ƽ��
    void leftRotate(TreeNode* x);
    
    // ����������ά��ƽ��
    void rightRotate(TreeNode* y);
    
    // �����޸���������֤������������ʲ����ƻ�
    void insertFix(TreeNode* z);
   
    // ɾ���޸���������֤ɾ�����������ʲ����ƻ�
    void deleteFix(TreeNode* x);
   
    // �滻�����ڵ������
    void transplant(TreeNode* u, TreeNode* v);
   
    // ��ȡ��ĳ���ڵ�Ϊ������Сֵ�ڵ�
    TreeNode* minimum(TreeNode* x);
    
    // �������
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

//��
RedBlackTree::RedBlackTree() {
    NIL = new TreeNode(0);
    NIL->color = false; // NIL always black
    root = NIL;
}

//��
RedBlackTree::~RedBlackTree() {
    clear(root);
    delete NIL;
}
//���ܣ�clear �ݹ�ɾ����ĳ�ڵ�Ϊ��������
void RedBlackTree::clear(TreeNode* node) {
    if (node != NIL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void RedBlackTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;// y ����������Ϊ x ��������
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;// y �ӹ� x �ĸ��ڵ�
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;// x ��Ϊ y ��������
    x->parent = y;
}

void RedBlackTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    y->left = x->right;// x ����������Ϊ y ��������
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;// x �ӹ� y �ĸ��ڵ�
    if (y->parent == NIL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y; // y ��Ϊ x ��������
    y->parent = x;
}

//���ܣ�����
void RedBlackTree::insert(int key) {
    TreeNode* z = new TreeNode(key);
    TreeNode* y = NIL;
    TreeNode* x = root;

    // �Ҳ���λ��
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;// ���� z �ĸ��ڵ�
    if (y == NIL) root = z;// �����Ϊ�գ�z ��Ϊ���ڵ�
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    
    // ��ʼ���½ڵ�������ӽڵ����ɫ
    z->left = NIL;
    z->right = NIL;
    z->color = true; // �²���ڵ�Ϊ��ɫ

    insertFix(z); // �޸����������
}

void RedBlackTree::insertFix(TreeNode* z) {
    // �����ڵ�Ϊ�죬�޸�
    while (z->parent->color) {
        // ������ڵ����游�ڵ�����ӽڵ�
        if (z->parent == z->parent->parent->left) {
            TreeNode* y = z->parent->parent->right;// z ����ڵ�
            if (y->color) {// Case 1: ��ڵ�Ϊ��
                // �����ڵ������ڵ�Ϳ�ڣ��游�ڵ�Ϳ��
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                // �� z �ƶ����游�ڵ㣬����������ϲ�
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {// Case 2: ��ڣ�z �����ӽڵ�
                    // �Ը��ڵ�������ʹ z ��Ϊ���ӽڵ�
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: �����Ǻڣ�z �����ӽڵ�
                // �����ڵ�Ϳ�ڣ��游�ڵ�Ϳ�죬���游�ڵ�����
                z->parent->color = false;
                z->parent->parent->color = true;
                rightRotate(z->parent->parent);
            }
        }
        else {
            // ������ڵ����游�ڵ�����ӽڵ㣬�����߼��Գ�
            TreeNode* y = z->parent->parent->left;// y �� z ������ڵ�
            // Case 1: ���
            if (y->color) {
                // �����ڵ������ڵ�Ϳ�ڣ��游�ڵ�Ϳ��
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                // �� z �ƶ����游�ڵ㣬����������ϲ�
                z = z->parent->parent;
            }
            else {
                // Case 2: ����ڵ��Ǻ�ɫ���� z �����ӽڵ�
                if (z == z->parent->left) {
                    // �Ը��ڵ�������ʹ z ��Ϊ���ӽڵ�
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: ����ڵ��Ǻ�ɫ���� z �����ӽڵ�
                // �����ڵ�Ϳ�ڣ��游�ڵ�Ϳ�죬���游�ڵ�����

                z->parent->color = false;
                z->parent->parent->color = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = false;// ���ڵ�Ϊ��ɫ
}

//���ܣ�ɾ���ڵ�
void RedBlackTree::erase(int key) {
    TreeNode* z = root;

    // ���Ҵ�ɾ���ڵ�
    while (z != NIL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }

    if (z == NIL) {// ����ڵ㲻����
        cout << "Key " << key << " not found.\n";
        return;
    }

    TreeNode* y = z;// y ��ʵ�ʱ�ɾ���Ľڵ�
    TreeNode* x; // x �������޸��Ľڵ�
    bool yOriginalColor = y->color;// ��¼ y ����ɫ

    //ɾ
    if (z->left == NIL) {
        // Case 1: z û�������������������滻 z
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        // Case 2: z û�������������������滻 z
        x = z->left;
        transplant(z, z->left);
    }
    else {
        // Case 3: z ����������
       // �ҵ� z �ĺ�̽ڵ㣨�������е���С�ڵ㣩
        y = minimum(z->right);// �ҵ���̽ڵ�
        yOriginalColor = y->color; //��¼��̽ڵ����ɫ
        x = y->right;// ��̽ڵ��������
       
        if (y->parent == z) {
            // �����̽ڵ��� z ��ֱ���ӽڵ�
            x->parent = y;// ���� x �ĸ��ڵ�Ϊ y
        }
        else {
            // �����̽ڵ㲻�� z ��ֱ���ӽڵ�
            transplant(y, y->right);// �� y ���������滻 y
            y->right = z->right; // �� z ������������ y
            y->right->parent = y;
        }
        // �ú�̽ڵ��滻 z ��λ��
        transplant(z, y);
        y->left = z->left;// �� z ������������ y
        y->left->parent = y;
        y->color = z->color;// ���� y ����ɫ�� z һ��
    }

    delete z;// ɾ���ڵ�
    if (!yOriginalColor) deleteFix(x);// �޸����������
}

void RedBlackTree::deleteFix(TreeNode* x) {
    // �޸�ʱ��ֻ�е� x ��Ϊ���ڵ��� x ����ɫΪ��ɫʱ��������
    while (x != root && !x->color) {
        if (x == x->parent->left) {
            // x ���丸�ڵ�����ӽڵ�
            TreeNode* w = x->parent->right; // w �� x ���ֵܽڵ�
            // Case 1: �ֵܽڵ��Ǻ�ɫ
            if (w->color) {
                w->color = false;// ���ֵܽڵ�Ϳ��
                x->parent->color = true; // �����ڵ�Ϳ��
                leftRotate(x->parent);// �Ը��ڵ�����
                w = x->parent->right; // �����ֵܽڵ�
            }
            // Case 2: �ֵܽڵ��Ǻ�ɫ���������ӽڵ�ҲΪ��ɫ
            if (!w->left->color && !w->right->color) {
                w->color = true; // ���ֵܽڵ�Ϳ��
                x = x->parent; // ���������Ƶ����ڵ�
            }
            else {
                // Case 3: �ֵܽڵ��Ǻ�ɫ�����ֵܵ����ӽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ
                if (!w->right->color) {
                    w->left->color = false;// ���ֵܵ����ӽڵ�Ϳ��
                    w->color = true; // ���ֵܽڵ�Ϳ��
                    rightRotate(w); // ���ֵܽڵ�����
                    w = x->parent->right;// �����ֵܽڵ�
                }
                // Case 4: �ֵܽڵ��Ǻ�ɫ�����ֵܵ����ӽڵ�Ϊ��ɫ
                w->color = x->parent->color;// ���ֵܽڵ����ɫ��Ϊ���ڵ����ɫ
                x->parent->color = false;// �����ڵ�Ϳ��
                w->right->color = false;// ���ֵܵ����ӽڵ�Ϳ��
                leftRotate(x->parent); // �Ը��ڵ�����
                x = root;
            }
        }
        else {
            // x ���丸�ڵ�����ӽڵ㣬�����߼������ӽڵ�Գ�
            TreeNode* w = x->parent->left;
            // Case 1: �ֵܽڵ��Ǻ�ɫ
            if (w->color) {
                w->color = false;
                x->parent->color = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            // Case 2: �ֵܽڵ��Ǻ�ɫ���������ӽڵ�ҲΪ��ɫ
            if (!w->right->color && !w->left->color) {
                w->color = true;
                x = x->parent;
            }
            else {
                // Case 3: �ֵܽڵ��Ǻ�ɫ�����ֵܵ����ӽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ
                if (!w->left->color) {
                    w->right->color = false;
                    w->color = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4: �ֵܽڵ��Ǻ�ɫ�����ֵܵ����ӽڵ�Ϊ��ɫ
                w->color = x->parent->color;
                x->parent->color = false;
                w->left->color = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false; // ��� x ����ɫ��Ϊ��ɫ��ȷ�����ڵ��Ǻ�ɫ
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

//���ܣ�find
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

//���ܣ��������
void RedBlackTree::ascend() {
    inorderTraversal(root);
    cout << endl;
}

// ��������ĵݹ�ʵ��
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
