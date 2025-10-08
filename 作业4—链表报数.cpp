#include<iostream>
using namespace std;
class node {
public:
	int data;
	node* next;
	
};
class linkstack :private node {
private:
	node* top;
public:
	linkstack() { top = 0; }
	~linkstack() {
		node* p = top;
		while (p) {
			p = p->next;
			delete top;
			top = p;
		}
	}
	bool empty() {
		return top == 0;
	}
	int Top() {
		return top->data;
	}
	linkstack& push(int x) {
		node* n = new node;
		n->data = x;
		n->next = top;
		top = n;
		return *this;
	}
	linkstack& pop() {
		node* p = top;
		int x = top->data;
		top = top->next;
		delete p;
		return *this;
	}
};
void jo(int n, int m) {

	linkstack people;
	linkstack temp;

	for (int i = n; i >= 1; --i) {
		people.push(i);  // 从 n到 1 入栈
	}

	int count = 0;
	while (!people.empty()) {
		// 数到第 m 个人出列
		while (!people.empty()) {
			int current = people.Top();
			people.pop();
			count++;

			if (count == m) {
				cout << current << ' ';  // 出列
				count = 0;  // 重新开始报数
			}
			else {
				temp.push(current);  // 没到 m 的人暂存到另一个栈中
			}
		}

		// 将剩下的未出列的人重新从 tempStack 入 people 栈，模拟循环
		while (!temp.empty()) {
			people.push(temp.Top());
			temp.pop();
		}
	}
	cout << endl;
}





int main() {
	int n, m;
	cin >> n >> m;
	jo(n, m);

	return 0;
}