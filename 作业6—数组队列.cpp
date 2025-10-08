#include <iostream>
#include <string>
using namespace std;

class Deque {
private:
    int* data;//用一维数组存
    int maxsize;
    int front;
    int rear;
    int size;

public:
    
    Deque(int cap) {
        maxsize = cap;
        front=0;
        rear=0;
        size=0;
        data = new int[maxsize];
    }

    
    ~Deque() {
        delete[] data;
    }

    void Create() {
        size = 0;
        front = 0;
        rear = 0;
    }

    bool IsEmpty() {
        return size == 0;
    }

    bool IsFull() {
        return size == maxsize;
    }

    void AddLeft(int x) {
        if (IsFull()) {
            cout << "FULL" << endl;
            return;
        }
        front = (front - 1 + maxsize) % maxsize;
        data[front] = x;
        size++;
        Print();
    }

    void AddRight(int x) {
        if (IsFull()) {
            cout << "FULL" << endl;
            return;
        }
        data[rear] = x;
        rear = (rear + 1) % maxsize;
        size++;
        Print();
    }

    void DeleteLeft() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        front = (front + 1) % maxsize;
        size--;
        Print();
    }

    void DeleteRight() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        rear = (rear - 1 + maxsize) % maxsize;
        size--;
        Print();
    }

    void Left() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
        }
        else {
            cout << data[front] << endl;
        }
    }

    void Right() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
        }
        else {
            cout << data[(rear - 1 + maxsize) % maxsize] << endl;
        }
    }

    void Print() {
        if (IsEmpty()) {
            cout << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << data[(front + i) % maxsize];
            if (i < size - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    Deque deque(100); // 设容量为 100
    deque.Create();

    string option;
    while (cin >> option && option != "End") {
        if (option == "AddLeft") {
            int x;
            cin >> x;
            deque.AddLeft(x);
        }
        else if (option == "AddRight") {
            int x;
            cin >> x;
            deque.AddRight(x);
        }
        else if (option == "DeleteLeft") {
            deque.DeleteLeft();
        }
        else if (option == "DeleteRight") {
            deque.DeleteRight();
        }
        else if (option == "Left") {
            deque.Left();
        }
        else if (option == "Right") {
            deque.Right();
        }
        else if (option == "IsEmpty") {
            cout << (deque.IsEmpty() ? "Yes" : "No") << endl;
        }
        else if (option == "IsFull") {
            cout << (deque.IsFull() ? "Yes" : "No") << endl;
        }
        else if (option == "Print") {
            deque.Print();
        }
        else {
            cout << "WRONG" << endl;
        }
    }

    return 0;
}
