#include<iostream>
using namespace std;
class node {
public:
	char data;
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
	char Top() {
		return top->data;
	}
	linkstack& push(char x) {
		node* n = new node;
		n->data = x;
		n->next = top;
		top = n;
		return *this;
	}
	linkstack& pop() {
		node* p = top;
		char x = top->data;
		top = top->next;
		delete p;
		return *this;
	}
	void deleteall(char d) {
		linkstack temp;
		linkstack result;
		while (!empty()) {
			if (Top() == d) {
				pop();
			}
			else {
				temp.push(Top());
				pop();
			}
		}
		while (!temp.empty()) {
			result.push(temp.Top());
			temp.pop();
		}
		while (!result.empty()) {
			cout << result.Top()<<' ';
			result.pop();
		}
	}
};



int main() {
	linkstack ori;
	ori.push('b');
	ori.push('a');
	ori.push('t');
	ori.push('a');
	ori.push('a');
	ori.push('e');
	ori.push('c');
	ori.deleteall('a');
	return 0;
}