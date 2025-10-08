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
		heap[0] = maxElement;//堆的第一个元素为最大值
		
		// 填充堆的剩余元素为最小元素
		for (int i = 0; i <= cap; i++) {
			heap[i + cap] = minElement;// 堆的后半部分设置为最小元素
		}
	}

	~maxHeap() {
		delete[]heap;
	}

	int top() {//找最大
		return heap[1]; // 根最大，索引为 1
	}

	void push(int x) {
		int current = ++heapSize;
		
		// 将新元素插入堆中上浮
		while (heap[current / 2] < x) {// 如果新插入的元素比父节点大，则上浮
			heap[current] = heap[current / 2];// 将父节点的值移到当前位置
			current = current / 2;// 更新当前位置为父节点
		}
		heap[current] = x;// 找到合适位置后，将元素插入
	}
	
	void pop() {
		int last = heap[heapSize--]; 

		int current = 1;// 从堆顶开始，进行下沉操作
		int child = 2;// 当前节点的左孩子


		while (child <= heapSize) {
			// 如果右子节点更大，则将child指向右子节点
			if (child < heapSize && heap[child] < heap[child + 1]) {
				child++;
			}
			// 如果最后一个元素比最大子节点还大，则不需要继续下沉
			if (last >= heap[child]) {
				break;
			}
			// 否则，将最大子节点的值移到当前节点位置
			heap[current] = heap[child];
			current = child;
			child = child * 2;
		}
		// 最后一个元素放合适位置
		heap[current] = last;
	}
	void print() {
		for (int i = 1; i <= heapSize; i++) {
			cout << heap[i] << ' ';
		}
		cout << endl;
	}
};


//优点：防止越界
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



