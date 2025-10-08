#include <iostream>
using namespace std;


struct AVLNode {
    int key;              
    AVLNode* left;         
    AVLNode* right;       
    int height;            

    
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// �ݹ�
int Height(AVLNode* root) {
    if (root == nullptr) {
        return 0; 
    }

    //�ݹ�����������
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    // ��ǰ�ڵ�ĸ������������ߵ����ֵ��1
    root->height = max(leftHeight, rightHeight) + 1;

    return root->height;
}


int main() {
 //         10
 //        / \
 //       5  15
 //      / \
 //     3   7


    AVLNode* root = new AVLNode(10);
    root->left = new AVLNode(5);
    root->right = new AVLNode(15);
    root->left->left = new AVLNode(3);
    root->left->right = new AVLNode(7);

    
    cout << Height(root) << endl;

    
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
