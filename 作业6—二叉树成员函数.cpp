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
        if (!node) return 0;//说明到了末端
        if (!(node->left) && (!node->right)) return 1;//说明是叶
        return countLeaves(node->left) + countLeaves(node->right);
    }

    
    void swapSubtree(TreeNode* node) {
        if (!node) return;
        swap(node->left, node->right);
        swapSubtree(node->left);//不断递归
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
        //规定-1代表空
        if (value == -1) return;
        root = new TreeNode(value);
        queue<TreeNode*> q;//存的是还未录入孩子的节点
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // 输入左孩子
            cout << "Enter left child of " << current->value << " (-1 for NULL): ";
            cin >> value;
            if (value != -1) {
                current->left = new TreeNode(value);
                q.push(current->left);
            }

            // 输入右孩子
            cout << "Enter right child of " << current->value << " (-1 for NULL): ";
            cin >> value;
            if (value != -1) {
                current->right = new TreeNode(value);
                q.push(current->right);
            }
        }
    }

    //  统计叶节点数目
    int countLeaves() {
        return countLeaves(root);
    }

    //  交换所有节点的左右子树
    void swapSubtree() {
        swapSubtree(root);
    }

    //  按层次顺序遍历
    void levelOrderTraversal() {
        if (!root) return;
        queue<TreeNode*> q;//存当前层上节点
        q.push(root);//从根开始
        while (!q.empty()) {//存的是需要访问的节点，不空说明还有没遍历的
            TreeNode* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left) q.push(current->left);//有左孩子就入队，循环同样操作
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }

    //  求二叉树的宽度
    int getWidth() {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int maxWidth = 0;

        while (!q.empty()) {
            int levelSize = q.size(); // 当前层的节点数
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

    //  统计叶节点数目
    cout << "Number of leaf nodes: " << tree.countLeaves() << endl;

    //  交换所有节点的左右子树
    tree.swapSubtree();
    cout << "Tree after swapping left and right subtrees (level order): ";
    tree.levelOrderTraversal();

    //  按层次顺序遍历
    cout << "Level order traversal: ";
    tree.levelOrderTraversal();

    //  求二叉树的宽度
    cout << "Width of the tree: " << tree.getWidth() << endl;

    return 0;
}
