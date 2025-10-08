#include<iostream>
using namespace std;
class node {
public:
	int data;
	node* next;
	
};
class list :public node{
private:
	node* head;
public:
	list() {
		head = 0;
	}
	~list() {
		node* p;
		while (head) {
			p = head->next;
			delete head;
			head = p;
		}
	}
	bool isEmpty() { return head == 0; }
	int length() {
		int size=0;
		node* p = head;
		while (p) {
			size++;
			p = p->next;
		}
		return size;
	}
	int find(int k) {
		node* p = head;
		int x;//��¼����
		int i = 1;
		while (i < k&&p) {
			p = p->next;
			i++;
		}
		if (p) {
			x = p->data;
		}
		return x;
	}
	list& Delete(int k) {
		node* p=head;//��ɾ
		node* q = head;//ָʾ
		int x;//��¼��ɾ����
		if (k == 1) {
			head = head->next;
		}
		else {
			for (int i = 1; i < k - 1 && q; i++) {
				q = q->next;
			}
			p = q->next;
			q->next = p->next;
			x = p->data;
			delete p;
		}
		return *this;
	}
	list& insert(int k, int x) {
		node* p = head;
		for (int i = 1; i < k && p; i++) {
			p = p->next;
		}
		node* n = new node;
		n->data = x;
		if (k ) {
			n->next = p->next;
			p->next = n;
		}
		else {//���ͷ
			n->next = head;
			head = n;
		}
		return *this;
	}
};
class stack :private list {
public:
	stack() {
		list();
	}
	bool empty() {
		return isEmpty();
	}
	int top() {
		return find(length());
	}
	stack& push(int x) {
		insert(length(), x);
		return *this;
	}
	stack& pop() {
		Delete(length());
		return *this;
	}
};

void jo(int n, int m) {

	stack people;
	stack temp;

	for (int i = n; i >= 1; --i) {
		people.push(i);  // �� n�� 1 ��ջ
	}

	int count = 0;  
	while (!people.empty()) {
		// ������ m ���˳���
		while (!people.empty()) {
			int current = people.top();
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
			people.push(temp.top());
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