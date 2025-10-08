#include <iostream>
#include <stack>
using namespace std;










void josephus_stack(int n, int m) {
    

    // 初始化一个栈用于存储所有人编号
    stack<int> people;
    stack<int> tempStack;

    for (int i = n; i >= 1; --i) {
        people.push(i);  // 从 n到 1 入栈，顶部为 1，栈底为 n
    }

    int count = 0;  // 计数器，用于模拟数数
    while (!people.empty()) {
        // 将栈中的人逐个出栈，数到第 m 个人出列
        while (!people.empty()) {
            int current = people.top();
            people.pop();
            count++;

            if (count == m) {
                cout << current<<' ';  // 出列的人的编号
                count = 0;  // 重置计数器
            }
            else {
                tempStack.push(current);  // 没到 m 的人暂存到另一个栈中
            }
        }

        // 将剩下的未出列的人重新从 tempStack 入 people 栈，模拟循环
        while (!tempStack.empty()) {
            people.push(tempStack.top());
            tempStack.pop();
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    // 栈实现
    josephus_stack(n, m);

    return 0;
}
