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

// ��������ȼ�
int level(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '(') return 0; // (�����ȼ����
    return -1; // �Ƿ��ַ�
}
bool lorn(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// ��׺ת��׺
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (lorn(ch)) {
            // ������ֱ�Ӽ����׺���ʽ
            postfix += ch ;
            postfix += " ";
        }
        else if (ch == '(') {
            // ��������ջ
            operators.push(ch);
        }
        else if (ch == ')') {
            // �����ţ����������ֱ������������
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top() ;
                postfix += " ";
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // ����������
        }
        else {
            // ���������Ƚ����ȼ�����ջ
            while (!operators.empty() && level(operators.top()) >= level(ch)) {
                postfix +=operators.top() ;
                postfix += ' ';
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // ���ջ��ʣ��������
    while (!operators.empty()) {
        postfix +=operators.top() ;
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

// ���ݺ�׺���ʽ������ʽ��
node* buildExpressionTree(const string& postfix) {
    stack<node*> nodes;//���ڴ洢�ڵ��ջ
    
    string token;// ������ʱ�洢������

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];//��ǰ�ַ�
        if (ch == ' ') continue;//

        if (lorn(ch)) {
            // ������������Ҷ�ӽڵ㲢ѹ��ջ��
            token = ch;
            nodes.push(new node(token));
        }
        else {
            // �����������������ڵ���Ϊ��������
            node* right = nodes.top();
            nodes.pop();
            node* left = nodes.top();
            nodes.pop();

            //����һ���µĲ������ڵ㣬���������������������ӵ��ýڵ�
            node* opNode = new node(string(1, ch));
            opNode->left = left;
            opNode->right = right;

            //���������ڵ�ѹ��ջ��
            nodes.push(opNode);
        }
    }
    // ����ջ���Ľڵ�,��Ϊ������ı��ʽ���ĸ�
    return nodes.top();
}

// ������ʽ��
void printExpressionTree(node* root, int depth = 0) {
    if (!root) return;

    // �ȴ�ӡ������
    printExpressionTree(root->right, depth + 1);

    // ��ӡ��ǰ�ڵ�
    for (int i = 0; i < depth; i++) cout << "\t";
    cout << root->value << endl;

    // �ٴ�ӡ������
    printExpressionTree(root->left, depth + 1);
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    // ת��Ϊ��׺���ʽ
    string postfix = infixToPostfix(infix);

    // ������ʽ��
    node* root = buildExpressionTree(postfix);

    // ��ӡ���ʽ��
    printExpressionTree(root);

    return 0;
}
