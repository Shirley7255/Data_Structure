#include <iostream>
#include <queue>
#include <algorithm> 
using namespace std;


struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};


class BinaryTree {
private:
    TreeNode* root;

    
    int countLeaves(TreeNode* node) {
        if (!node) return 0;//˵������ĩ��
        if (!(node->left) && (!node->right)) return 1;//˵����Ҷ
        return countLeaves(node->left) + countLeaves(node->right);
    }

    
    void swapSubtree(TreeNode* node) {
        if (!node) return;
        swap(node->left, node->right);
        swapSubtree(node->left);//���ϵݹ�
        swapSubtree(node->right);
    }

    
    int getHeight(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

public:
    BinaryTree() : root(nullptr) {}

    
    void create() {
        cout << "Enter root value : ";
        int value;
        cin >> value;
        //�涨-1�����
        if (value == -1) return;
        root = new TreeNode(value);
        queue<TreeNode*> q;//����ǻ�δ¼�뺢�ӵĽڵ�
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // ��������
            cout << "Enter left child of " << current->value << " (-1 for NULL): ";
            cin >> value;
            if (value != -1) {
                current->left = new TreeNode(value);
                q.push(current->left);
            }

            // �����Һ���
            cout << "Enter right child of " << current->value << " (-1 for NULL): ";
            cin >> value;
            if (value != -1) {
                current->right = new TreeNode(value);
                q.push(current->right);
            }
        }
    }

    //  ͳ��Ҷ�ڵ���Ŀ
    int countLeaves() {
        return countLeaves(root);
    }

    //  �������нڵ����������
    void swapSubtree() {
        swapSubtree(root);
    }

    //  �����˳�����
    void levelOrderTraversal() {
        if (!root) return;
        queue<TreeNode*> q;//�浱ǰ���Ͻڵ�
        q.push(root);//�Ӹ���ʼ
        while (!q.empty()) {//�������Ҫ���ʵĽڵ㣬����˵������û������
            TreeNode* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left) q.push(current->left);//�����Ӿ���ӣ�ѭ��ͬ������
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }

    //  ��������Ŀ��
    int getWidth() {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int maxWidth = 0;

        while (!q.empty()) {
            int levelSize = q.size(); // ��ǰ��Ľڵ���
            maxWidth = (maxWidth>levelSize)? maxWidth : levelSize;
            for (int i = 0; i < levelSize; i++) {
                TreeNode* current = q.front();
                q.pop();
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
        }

        return maxWidth;
    }
};

int main() {
 //        1
 //       / \
 //      2   3
 //     / \
 //    4   5


    BinaryTree tree;

    tree.create();

    //  ͳ��Ҷ�ڵ���Ŀ
    cout << "Number of leaf nodes: " << tree.countLeaves() << endl;

    //  �������нڵ����������
    tree.swapSubtree();
    cout << "Tree after swapping left and right subtrees (level order): ";
    tree.levelOrderTraversal();

    //  �����˳�����
    cout << "Level order traversal: ";
    tree.levelOrderTraversal();

    //  ��������Ŀ��
    cout << "Width of the tree: " << tree.getWidth() << endl;

    return 0;
}
