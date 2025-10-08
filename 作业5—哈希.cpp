#include <iostream>
#include <vector>
using namespace std;
class HashTable {
private:
    struct HashNode {
        int key;          // 键
        char value;       // 值
        bool isOccupied = false; // 是否存放数据
        bool isDeleted = false;  // 是否被删除
    };

    vector<HashNode> table; // 散列表
    int numElements = 0;         // 当前有效元素个数
    int numUsed = 0;             // 当前使用过的槽位数
    const double REHASH = 0.6; // 重新组织的阈值

    //辅助函数
    int hashFunction(int key) const {
        return key % table.size();
    }

    void rehash() {
        //原表现在是旧表
        vector<HashNode> oldTable = table;
        //清空旧表，槽位2倍
        table.clear();
        table.resize(oldTable.size() * 2); 
        //重置
        numElements = 0;
        numUsed = 0;

        //遍历旧表将有效键值对插入新表
        for (vector<HashNode>::iterator it = oldTable.begin(); it != oldTable.end(); ++it) {
            if (it->isOccupied && !it->isDeleted) {
                insert(it->key, it->value);
            }
        }

    }

public:
    //构
    HashTable(int size = 10) : table(size) {}

    void insert(int key, char value) {
        int index = hashFunction(key);

        // 线性探查，如果当前槽被占查下一个
        while (table[index].isOccupied && !table[index].isDeleted) {
            if (table[index].key == key) {
                table[index].value = value; // 更新值
                return;
            }
            //如果槽位被占但不是相同的键查下一个
            index = (index + 1) % table.size();
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false; // 插入时标记为未删除
        numElements++;
        numUsed++;

        // 检查是否需要重新组织
        if ((double)numUsed / table.size() >= REHASH) {
            rehash();
        }
    }

    bool find(int key, char& value) const {
        int index = hashFunction(key);

        while (table[index].isOccupied || table[index].isDeleted) {
            //如果被占且键匹配，找到
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
            //如果被占且键匹配，找到
            if (table[index].isOccupied && table[index].key == key) {
                table[index].isOccupied = false; // 标记为未占用
                table[index].isDeleted = true;   // 标记为已删除
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
