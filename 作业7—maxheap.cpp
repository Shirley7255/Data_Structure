#include<iostream>
using namespace std;
class maxHeap {
private:
	int* heap;
	int arrayLength;
	int heapSize;
public:
	maxHeap(int cap,int maxElement,int minElement){
		arrayLength = 2 * cap + 1;
		heap = new int[arrayLength];
		heapSize = 0;
		heap[0] = maxElement;//�ѵĵ�һ��Ԫ��Ϊ���ֵ
		
		// ���ѵ�ʣ��Ԫ��Ϊ��СԪ��
		for (int i = 0; i <= cap; i++) {
			heap[i + cap] = minElement;// �ѵĺ�벿������Ϊ��СԪ��
		}
	}

	~maxHeap() {
		delete[]heap;
	}

	int top() {//�����
		return heap[1]; // ���������Ϊ 1
	}

	void push(int x) {
		int current = ++heapSize;
		
		// ����Ԫ�ز�������ϸ�
		while (heap[current / 2] < x) {// ����²����Ԫ�رȸ��ڵ�����ϸ�
			heap[current] = heap[current / 2];// �����ڵ��ֵ�Ƶ���ǰλ��
			current = current / 2;// ���µ�ǰλ��Ϊ���ڵ�
		}
		heap[current] = x;// �ҵ�����λ�ú󣬽�Ԫ�ز���
	}
	
	void pop() {
		int last = heap[heapSize--]; 

		int current = 1;// �ӶѶ���ʼ�������³�����
		int child = 2;// ��ǰ�ڵ������


		while (child <= heapSize) {
			// ������ӽڵ������childָ�����ӽڵ�
			if (child < heapSize && heap[child] < heap[child + 1]) {
				child++;
			}
			// ������һ��Ԫ�ر�����ӽڵ㻹������Ҫ�����³�
			if (last >= heap[child]) {
				break;
			}
			// ���򣬽�����ӽڵ��ֵ�Ƶ���ǰ�ڵ�λ��
			heap[current] = heap[child];
			current = child;
			child = child * 2;
		}
		// ���һ��Ԫ�طź���λ��
		heap[current] = last;
	}
	void print() {
		for (int i = 1; i <= heapSize; i++) {
			cout << heap[i] << ' ';
		}
		cout << endl;
	}
};


//�ŵ㣺��ֹԽ��
int main() {
//     30
//    /  \
//   20  10
//  /
// 40


	maxHeap myheap(10,100,1);
	myheap.push(30);
	myheap.push(20);
	myheap.push(10);
	myheap.push(40);
	
	cout << "top is" << ' ' << myheap.top();
	cout << endl;

	myheap.print();
	cout << endl;

	myheap.pop();
	cout << "after pop" << endl;
	myheap.print();



	return 0;
}



