#include <iostream>
#include <stack>
#include <string>

using namespace std;


struct node {
    string value;
    node* left;
    node* right;
    node(string val) {
        value=val;
        left=nullptr;
        right = nullptr;
    } 
};

// 运算符优先级
int level(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '(') return 0; // (的优先级最低
    return -1; // 非法字符
}
bool lorn(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// 中缀转后缀
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (lorn(ch)) {
            // 操作数直接加入后缀表达式
            postfix += ch ;
            postfix += " ";
        }
        else if (ch == '(') {
            // 左括号入栈
            operators.push(ch);
        }
        else if (ch == ')') {
            // 右括号，弹出运算符直到遇到左括号
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top() ;
                postfix += " ";
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // 弹出左括号
        }
        else {
            // 操作符，比较优先级并弹栈
            while (!operators.empty() && level(operators.top()) >= level(ch)) {
                postfix +=operators.top() ;
                postfix += ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // 清空栈中剩余的运算符
    while (!operators.empty()) {
        postfix +=operators.top() ;
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

// 根据后缀表达式构造表达式树
node* buildExpressionTree(const string& postfix) {
    stack<node*> nodes;//用于存储节点的栈
    
    string token;// 用于临时存储操作数

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];//当前字符
        if (ch == ' ') continue;//

        if (lorn(ch)) {
            // 操作数，创建叶子节点并压入栈中
            token = ch;
            nodes.push(new node(token));
        }
        else {
            // 操作符，弹出两个节点作为左右子树
            node* right = nodes.top();
            nodes.pop();
            node* left = nodes.top();
            nodes.pop();

            //创建一个新的操作符节点，并将左子树和右子树连接到该节点
            node* opNode = new node(string(1, ch));
            opNode->left = left;
            opNode->right = right;

            //将操作符节点压入栈中
            nodes.push(opNode);
        }
    }
    // 返回栈顶的节点,即为构建完的表达式树的根
    return nodes.top();
}

// 输出表达式树
void printExpressionTree(node* root, int depth = 0) {
    if (!root) return;

    // 先打印右子树
    printExpressionTree(root->right, depth + 1);

    // 打印当前节点
    for (int i = 0; i < depth; i++) cout << "\t";
    cout << root->value << endl;

    // 再打印左子树
    printExpressionTree(root->left, depth + 1);
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    // 转换为后缀表达式
    string postfix = infixToPostfix(infix);

    // 构造表达式树
    node* root = buildExpressionTree(postfix);

    // 打印表达式树
    printExpressionTree(root);

    return 0;
}
