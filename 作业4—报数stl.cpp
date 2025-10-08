#include <iostream>
#include <stack>
using namespace std;










void josephus_stack(int n, int m) {
    

    // ��ʼ��һ��ջ���ڴ洢�����˱��
    stack<int> people;
    stack<int> tempStack;

    for (int i = n; i >= 1; --i) {
        people.push(i);  // �� n�� 1 ��ջ������Ϊ 1��ջ��Ϊ n
    }

    int count = 0;  // ������������ģ������
    while (!people.empty()) {
        // ��ջ�е��������ջ�������� m ���˳���
        while (!people.empty()) {
            int current = people.top();
            people.pop();
            count++;

            if (count == m) {
                cout << current<<' ';  // ���е��˵ı��
                count = 0;  // ���ü�����
            }
            else {
                tempStack.push(current);  // û�� m �����ݴ浽��һ��ջ��
            }
        }

        // ��ʣ�µ�δ���е������´� tempStack �� people ջ��ģ��ѭ��
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

    // ջʵ��
    josephus_stack(n, m);

    return 0;
}
