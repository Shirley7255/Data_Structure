#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


struct node {
    char ch;
    int fre; // 频率
    node* left;
    node* right;

    node(char c, int f) {
        ch = c;
        fre = f;
        left = nullptr;
        right = nullptr;
    }
};


class Heap {
public:
    vector<node*> heap;

    // 从下往上调整堆
    void Up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2; // 找父节点
            if (heap[index]->fre < heap[parent]->fre) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    // 从上往下调整堆
    void Down(int index) {
        int size = heap.size();
        while (index < size) {
            int leftchild = index * 2 + 1;  // 左子节点
            int rightchild = index * 2 + 2; // 右子节点
            int smallest = index;

            if (leftchild < size && heap[leftchild]->fre < heap[smallest]->fre) {
                smallest = leftchild;
            }
            if (rightchild < size && heap[rightchild]->fre < heap[smallest]->fre) {
                smallest = rightchild;
            }

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }

  
    void push(node* n) {
        heap.push_back(n);
        Up(heap.size() - 1);
    }

    
    node* pop() {
        if (heap.empty()) {
            return nullptr;
        }
        node* topnode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        Down(0);

        return topnode;
    }

    
    node* top() {
        return heap[0];
    }

    
    bool empty() {
        return heap.empty();
    }

    
    int size() {
        return heap.size();
    }
};


node* create(vector<pair<char, int>>& freq) {
    Heap myheap;

    // 每个字符创建单独节点并插入
    for (int i = 0; i < freq.size(); i++) {
        node* n = new node(freq[i].first, freq[i].second);
        myheap.push(n);
    }

    // 构建哈夫曼树
    while (myheap.size() > 1) {
        node* left = myheap.pop();  // 最小频率节点
        node* right = myheap.pop(); // 次小频率节点

        // 创建新节点，频率为左右节点频率之和
        node* parent = new node('\0', left->fre + right->fre);
        parent->left = left;
        parent->right = right;

        myheap.push(parent);
    }
    return myheap.pop();
}

// 递归 编码表
void buildCodeTable(node* root, string code, unordered_map<char, string>& codeTable) {
    if (!root) {
        return;
    }

    // 如果是叶子节点，记录其字符和对应的编码
    if (!root->left && !root->right) {
        codeTable[root->ch] = code;
        return;
    }

    buildCodeTable(root->left, code + "0", codeTable);
    buildCodeTable(root->right, code + "1", codeTable);
}

// 用编码压缩字符串
string encodeString(const string& input, const unordered_map<char, string>& codeTable) {
    string encodedString;
    for (int i = 0; i < input.size(); i++) {
        if (codeTable.find(input[i]) != codeTable.end()) {
            encodedString += codeTable.at(input[i]); // 将字符转换为对应的编码
        }
    }
    return encodedString;
}

// 统计频率
vector<pair<char, int>> countFrequency(const string& str) {
    unordered_map<char, int> freqMap;
    for (int i = 0; i < str.size(); i++) {
        if (isalpha(str[i])) { // 只统计字母
            freqMap[str[i]]++;
        }
    }

    vector<pair<char, int>> freq;
    unordered_map<char, int>::iterator it;
    for (it = freqMap.begin(); it != freqMap.end(); it++) {
        freq.push_back(make_pair(it->first, it->second));
    }
    return freq;
}

int main() {
    string input;
    cout << "输入字符串: ";
    getline(cin, input);

  
    vector<pair<char, int>> frequency = countFrequency(input);

    
    node* root = create(frequency);

    
    unordered_map<char, string> codeTable;
    buildCodeTable(root, "", codeTable);

    
    cout << endl;
    unordered_map<char, string>::iterator it;
    for (it = codeTable.begin(); it != codeTable.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }

    
    string encodedString = encodeString(input, codeTable);
    cout  << endl;
    cout << encodedString << endl;

    return 0;
}
