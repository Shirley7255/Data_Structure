#include <iostream>
#include <vector>
using namespace std;
class HashChainsWithTail {
private:
    
    struct Node {
        int key;  // ��
        Node* next;   

        // ��
        Node(int k, Node* n = nullptr) : key(k), next(n) {}
    };

    vector<Node*> table;  // ɢ�б�Ĳۣ��洢�����ͷ�ڵ�
    Node* sharedTail;          // ��������Ĺ���β�ڵ�
    int size;                  // ɢ�б�Ĵ�С

    // ������ϣ����
    int hashFunction(int key) const {
        return key % size;  
    }

public:
    // ����Ϊÿ���۷���һ������ͷ
    HashChainsWithTail(int tableSize) : size(tableSize) {
        table.resize(size, nullptr);  
        sharedTail = new Node(0);  // ����һ������β�ڵ�
    }

    
    ~HashChainsWithTail() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            // ����ÿ�����е�����ɾ�����нڵ�
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
        Node* current = table[index];   // ��ȡ��ǰ�۵�����ͷ
        Node* prev = nullptr;           // ���ڼ�¼��һ���ڵ�

        
        while (current && current != sharedTail && current->key < key) {
            prev = current;          // ����prevΪ��ǰ�ڵ�
            current = current->next; // ����ƶ����������һ���ڵ�
        }

        // ����ҵ���ͬ�ļ��������������
        if (current && current != sharedTail && current->key == key) {
            return;
        }

        // �����µĽڵ㣬�½ڵ��nextָ��ǰ�ڵ����β�ڵ�
        Node* newNode = new Node(key, current ? current : sharedTail);

        // ���½ڵ����������
        if (prev) {
            prev->next = newNode;  // �����������ͷ������ǰһ���ڵ��nextָ��
        }
        else {
            table[index] = newNode;  // ���������ͷ�����²۵�ͷ�ڵ�
        }
    }

    
    bool remove(int key) {
        int index = hashFunction(key);  
        Node* current = table[index];   // ��ȡ��ǰ�۵�����ͷ
        Node* prev = nullptr;           // ���ڼ�¼��һ���ڵ�

        // Ѱ��Ŀ��ڵ�
        while (current && current != sharedTail && current->key != key) {
            prev = current;          // ����prevΪ��ǰ�ڵ�
            current = current->next; // ����ƶ����������һ���ڵ�
        }

        // ����ҵ�Ŀ��ڵ㣬ɾ���ڵ�
        if (current && current != sharedTail && current->key == key) {
            if (prev) {
                prev->next = current->next;  // ����ǰһ���ڵ��nextָ��
            }
            else {
                table[index] = current->next;  // ���������ͷ�����²۵�ͷ�ڵ�
            }
            delete current;  // ɾ��Ŀ��ڵ�
            return true;
        }
        return false;  // δ�ҵ�
    }

    
    void print() const {
        // ����ÿ����
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];  // ��ȡ��ǰ�۵�����ͷ

            // ����������ӡÿ���ڵ�ļ�ֵ
            while (current && current != sharedTail) {
                cout << current->key << " -> ";
                current = current->next;
            }

            cout << "Tail"<<endl;  // ���β�ڵ�
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
