#include<iostream>
using namespace std;
class node {
public:
	int data;
	node* prior;
	node* next;
	node(int x, node* p=nullptr, node* n=nullptr) {
		data = x;
		prior = p;
		next = n;
	}
	node() {};
	node(int x) {
		data = x;
	}
};
class dclist :public node {
public:
	node* head;
	int size;
	dclist(){
		head = new node();
		head->next = head;
		head->prior = head;
		size = 0;
	}
	
	void append(int x) {
		node* nnode = new node(x, head->prior, head);
		head->prior->next = nnode;
		head->prior = nnode;
		size++;
	}
	void print() {
		node* current = head->next;
		while (current != head) {
			cout << current->data << ' ';
			current = current->next;
		}
		cout << endl;
	}

};
void split(dclist c, dclist &a, dclist& b) {
	int index = 1;
	node* current = c.head->next;
	while (current != c.head) {
		if (index % 2 == 1) {
			a.append(current->data);
		}
		else {
			b.append(current->data);
		}
		current = current->next;
		index++;
	}
}



int main() {
	dclist c;
	dclist a;
	dclist b;

	c.append(1);
	c.append(2);
	c.append(3);
	c.append(4);
	c.append(5);
	

	split(c, a, b);
	a.print();
	b.print();
	
	


	return 0;
}