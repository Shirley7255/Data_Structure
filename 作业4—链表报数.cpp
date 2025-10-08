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
		people.push(i);  // �� n�� 1 ��ջ
	}

	int count = 0;
	while (!people.empty()) {
		// ������ m ���˳���
		while (!people.empty()) {
			int current = people.Top();
			people.pop();
			count++;

			if (count == m) {
				cout << current << ' ';  // ����
				count = 0;  // ���¿�ʼ����
			}
			else {
				temp.push(current);  // û�� m �����ݴ浽��һ��ջ��
			}
		}

		// ��ʣ�µ�δ���е������´� tempStack �� people ջ��ģ��ѭ��
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