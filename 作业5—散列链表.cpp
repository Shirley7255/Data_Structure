#include <iostream>
#include <vector>
using namespace std;
class HashChainsWithTail {
private:
    
    struct Node {
        int key;  // 键
        Node* next;   

        // 构
        Node(int k, Node* n = nullptr) : key(k), next(n) {}
    };

    vector<Node*> table;  // 散列表的槽，存储链表的头节点
    Node* sharedTail;          // 所有链表的共享尾节点
    int size;                  // 散列表的大小

    // 辅助哈希函数
    int hashFunction(int key) const {
        return key % size;  
    }

public:
    // 构，为每个槽分配一个链表头
    HashChainsWithTail(int tableSize) : size(tableSize) {
        table.resize(size, nullptr);  
        sharedTail = new Node(0);  // 创建一个共享尾节点
    }

    
    ~HashChainsWithTail() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            // 遍历每个槽中的链表，删除所有节点
            while (current && current != sharedTail) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete sharedTail; 
    }

    
    void insert(int key) {
        int index = hashFunction(key);  
        Node* current = table[index];   // 获取当前槽的链表头
        Node* prev = nullptr;           // 用于记录上一个节点

        
        while (current && current != sharedTail && current->key < key) {
            prev = current;          // 更新prev为当前节点
            current = current->next; // 向后移动到链表的下一个节点
        }

        // 如果找到相同的键，不插入避免重
        if (current && current != sharedTail && current->key == key) {
            return;
        }

        // 创建新的节点，新节点的next指向当前节点或者尾节点
        Node* newNode = new Node(key, current ? current : sharedTail);

        // 将新节点插入链表中
        if (prev) {
            prev->next = newNode;  // 如果不是链表头，更新前一个节点的next指针
        }
        else {
            table[index] = newNode;  // 如果是链表头，更新槽的头节点
        }
    }

    
    bool remove(int key) {
        int index = hashFunction(key);  
        Node* current = table[index];   // 获取当前槽的链表头
        Node* prev = nullptr;           // 用于记录上一个节点

        // 寻找目标节点
        while (current && current != sharedTail && current->key != key) {
            prev = current;          // 更新prev为当前节点
            current = current->next; // 向后移动到链表的下一个节点
        }

        // 如果找到目标节点，删除节点
        if (current && current != sharedTail && current->key == key) {
            if (prev) {
                prev->next = current->next;  // 更新前一个节点的next指针
            }
            else {
                table[index] = current->next;  // 如果是链表头，更新槽的头节点
            }
            delete current;  // 删除目标节点
            return true;
        }
        return false;  // 未找到
    }

    
    void print() const {
        // 遍历每个槽
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];  // 获取当前槽的链表头

            // 遍历链表并打印每个节点的键值
            while (current && current != sharedTail) {
                cout << current->key << " -> ";
                current = current->next;
            }

            cout << "Tail"<<endl;  // 输出尾节点
        }
    }
};


int main() {
    
    HashChainsWithTail hashTable(5);

    
    hashTable.insert(1);
    hashTable.insert(6);
    hashTable.insert(11);
    hashTable.insert(2);
    hashTable.insert(3);

    
    hashTable.print();

   
    std::cout << "Removing 6...\n";
    hashTable.remove(6);
    hashTable.print();

    

    std::cout << "Removing 2...\n";
    hashTable.remove(2);
    hashTable.print();
    return 0;
}
