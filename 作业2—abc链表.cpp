#include<iostream>
using namespace std;
class node {
public:
	int data;
	node* next;
	node(int n, node* nextnode) {
		data = n;
		next = nextnode;
	}
	node(int n) {
		data = n;
		next = nullptr;
	}

};
class list {
public:
	node* head;
	
	int num;//�ڵ���

	list() {
		num = 0;
		head = nullptr;
	}
	~list() {//�ظ�����׽ڵ�
		node* t;//��ʱ����
		while (head) {
			t = head->next;
			delete head;
			head = t;
		}
	}
	int length() {
		node* current=head;//��ʱ
		int len = 0;
		while (current) {
			len++;
			current = current->next;
		}
		return len;
	}
	

	void insert(int x,int index) {
		if (index == 0) {
			head = new node(x, head);
		}
		else {
			node* p = head;//��ǰ��
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			p->next = new node(x, p->next);
		}
		num++;
	}
	void output() {
		node* current = head;
		while (current != nullptr) {
			cout << current->data << ' ';
			current = current->next;
		}
		cout << endl;
	}
	void append(int x) {
		insert(x, length());
	}
	
};
list meld(const list& a,const list& b) {
	list c;
	node* ca = a.head;
	node* cb = b.head;
	while (ca != nullptr || cb != nullptr) {
		if (ca != nullptr) {
			c.append(ca->data);
			ca = ca->next;
		}
		if (cb != nullptr) {
			c.append(cb->data);
			cb = cb->next;
		}

	}
	return c;
}


int main() {
	list a;
	list b;
	a.append(1);
	a.append(2);
	a.append(3);
	b.append(11);
	b.append(12);
	list c = meld(a, b);
	c.output();



	return 0;
}