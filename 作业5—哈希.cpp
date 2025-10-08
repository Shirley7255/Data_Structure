#include <iostream>
#include <vector>
using namespace std;
class HashTable {
private:
    struct HashNode {
        int key;          // ��
        char value;       // ֵ
        bool isOccupied = false; // �Ƿ�������
        bool isDeleted = false;  // �Ƿ�ɾ��
    };

    vector<HashNode> table; // ɢ�б�
    int numElements = 0;         // ��ǰ��ЧԪ�ظ���
    int numUsed = 0;             // ��ǰʹ�ù��Ĳ�λ��
    const double REHASH = 0.6; // ������֯����ֵ

    //��������
    int hashFunction(int key) const {
        return key % table.size();
    }

    void rehash() {
        //ԭ�������Ǿɱ�
        vector<HashNode> oldTable = table;
        //��վɱ���λ2��
        table.clear();
        table.resize(oldTable.size() * 2); 
        //����
        numElements = 0;
        numUsed = 0;

        //�����ɱ���Ч��ֵ�Բ����±�
        for (vector<HashNode>::iterator it = oldTable.begin(); it != oldTable.end(); ++it) {
            if (it->isOccupied && !it->isDeleted) {
                insert(it->key, it->value);
            }
        }

    }

public:
    //��
    HashTable(int size = 10) : table(size) {}

    void insert(int key, char value) {
        int index = hashFunction(key);

        // ����̽�飬�����ǰ�۱�ռ����һ��
        while (table[index].isOccupied && !table[index].isDeleted) {
            if (table[index].key == key) {
                table[index].value = value; // ����ֵ
                return;
            }
            //�����λ��ռ��������ͬ�ļ�����һ��
            index = (index + 1) % table.size();
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false; // ����ʱ���Ϊδɾ��
        numElements++;
        numUsed++;

        // ����Ƿ���Ҫ������֯
        if ((double)numUsed / table.size() >= REHASH) {
            rehash();
        }
    }

    bool find(int key, char& value) const {
        int index = hashFunction(key);

        while (table[index].isOccupied || table[index].isDeleted) {
            //�����ռ�Ҽ�ƥ�䣬�ҵ�
            if (table[index].isOccupied && table[index].key == key) {
                value = table[index].value;
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);

        while (table[index].isOccupied || table[index].isDeleted) {
            //�����ռ�Ҽ�ƥ�䣬�ҵ�
            if (table[index].isOccupied && table[index].key == key) {
                table[index].isOccupied = false; // ���Ϊδռ��
                table[index].isDeleted = true;   // ���Ϊ��ɾ��
                numElements--;
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    void print() const {
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                cout << "Index " << i << ": " << table[i].key << " -> " << table[i].value << "\n";
            }
        }
        cout << "Total elements: " << numElements << "\n";
    }
};

// 
int main() {
    HashTable hashTable(5);

    hashTable.insert(1, 'A');
    hashTable.insert(2, 'B');
    hashTable.insert(3, 'C');
    hashTable.insert(4, 'D');
    hashTable.insert(5, 'E');

    hashTable.print();
    cout << endl;
    char value;
    if (hashTable.find(3, value)) {
        cout << "Found: " << value << endl;
    }
    else {
        cout << "Not found"<<endl;
    }
    cout << endl;
    hashTable.remove(2);
    cout << "After delete:" << endl;
    hashTable.print();
    cout << endl;
    hashTable.insert(6, 'F');
    cout << "After insert:" << endl;
    hashTable.print();

    return 0;
}
