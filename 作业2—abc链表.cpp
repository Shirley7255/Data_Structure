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
	
	int num;//节点数

	list() {
		num = 0;
		head = nullptr;
	}
	~list() {//重复清除首节点
		node* t;//临时变量
		while (head) {
			t = head->next;
			delete head;
			head = t;
		}
	}
	int length() {
		node* current=head;//临时
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
			node* p = head;//找前驱
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