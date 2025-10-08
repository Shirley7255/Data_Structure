#include <iostream> 
#include <map>       
#include <string>    
using namespace std; 


class Node {
public:
    char ch;       
    int weight;       
    Node* left;       
    Node* right;      
    
    Node(char c, int m) {
        ch = c;     
        weight = m;    
        left = right = nullptr; 
    }
};


class MinHeap {
public:
    Node** heap;   
    int capacity;
    int size;
    
    MinHeap(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new Node * [maxSize + 1];
    }
   
    void insert(Node* node) {
        if (size >= capacity) {
            cout << "Heap is full!" << endl;
            return;
        }
        int i = ++size;                        // 从堆尾插入

        // 上浮操作，维护最小堆性质
        while (i != 1 && node->weight < heap[i / 2]->weight) {
            heap[i] = heap[i / 2];             // 父节点下移
            i /= 2;                            // 更新当前节点位置为父节点位置
        }
        heap[i] = node;                        // 将节点插入到正确位置
    }

    
    Node* removeMin() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return NULL;
        }
        Node* minNode = heap[1];               // 保存堆顶节点
        Node* lastNode = heap[size--];         // 用堆尾节点替换堆顶，并减少堆大小
        // 初始化父节点和左子节点位置
        int parent = 1;
        int   child = 2; 
        
        
        // 下沉操作，维护最小堆性质
        while (child <= size) {  // 当存在子节点时
            if (child < size && heap[child]->weight > heap[child + 1]->weight)
                ++child;  
            // 如果右子节点更小，选择右子节点
            if (lastNode->weight <= heap[child]->weight)
                break;                         
            // 如果堆尾节点小于子节点，停止下沉
            heap[parent] = heap[child];        // 子节点上移
            parent = child;                    // 更新父节点位置
            child *= 2;                        // 更新子节点位置
        }
        heap[parent] = lastNode;               // 将堆尾节点放入正确位置
        return minNode;                        
    }

   
    bool isEmpty() {
        return size == 0;                      
    }
};


class HuffmanTree {
public:
    Node* root;
    map<char, int> m;             
    map<char, string> m2;          
    string encodestr;
    
    HuffmanTree(string s) {
        int n = s.length();
        encodestr = "";
        MinHeap heap(n);              
        for (char c : s) {             // 遍历字符串
            if (isalpha(c)) m[c]++;    // 统计每个字母的出现频率
        }
        for (char c : s) {             // 初始化字符编码为 "0"
            if (isalpha(c))
                m2[c] = "0";
        }
        for (auto& p : m) {            
            heap.insert(new Node(p.first, p.second));
        }
        while (heap.size > 1) {        
            Node* left = heap.removeMin();      // 删除堆顶（最小权重节点）作为左子节点
            Node* right = heap.removeMin();     // 再次删除堆顶作为右子节点
            Node* parent = new Node('\0', left->weight + right->weight);
            // 创建父节点，权重为左右子节点权重之和
            parent->left = left;             
            parent->right = right;           
            heap.insert(parent);             
        }
        root = heap.removeMin();            
    }

    
    void printTree(Node* node, string prefix = "") {
        if (!node) return;                  
        if (!node->left && !node->right) {  // 如果是叶子节点
            cout << node->ch << ": " << prefix << endl; // 打印字符及其编码
            m2[node->ch] = prefix;      
        }
        else {                             // 如果不是叶子节点，递归处理左右子树
            printTree(node->left, prefix + "0");
            printTree(node->right, prefix + "1");
        }
    }
    void printTree() {                     
        printTree(root);
    }

    // 将字符串编码成哈夫曼
    void code(string s) {
        for (int i = 0; i < s.length(); i++) { 
            for (auto& p : m2) {              
                if (s[i] == p.first) {        // 如果字符匹配
                    cout << p.second;         
                    encodestr += p.second;    // 将编码追加到编码字符串中
                }
            }
        }
        cout << endl;
    }

    // 解码
    void decode(string s) {
        Node* current = root;              // 从根节点开始解码
        for (char c : s) {                
            if (c == '0') {                // 如果是 '0'，进入左子树
                current = current->left;
            }
            else if (c == '1') {           // 如果是 '1'，进入右子树
                current = current->right;
            }
            if (!current->left && !current->right) { // 如果叶节点
                cout << current->ch;   // 输出叶节点的字符
                current = root;           // 返回到根节点
            }
        }
        cout << endl;
    }
};

int main() {
    string s;                      
    cin >> s;                      
    HuffmanTree huffman(s);        
    huffman.printTree();           
    cout << "编码后:" << endl;
    huffman.code(s);               
    cout << "解码后:" << endl;
    huffman.decode(huffman.encodestr); 
    return 0;                      
}
