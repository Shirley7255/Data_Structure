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
        int i = ++size;                        // �Ӷ�β����

        // �ϸ�������ά����С������
        while (i != 1 && node->weight < heap[i / 2]->weight) {
            heap[i] = heap[i / 2];             // ���ڵ�����
            i /= 2;                            // ���µ�ǰ�ڵ�λ��Ϊ���ڵ�λ��
        }
        heap[i] = node;                        // ���ڵ���뵽��ȷλ��
    }

    
    Node* removeMin() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return NULL;
        }
        Node* minNode = heap[1];               // ����Ѷ��ڵ�
        Node* lastNode = heap[size--];         // �ö�β�ڵ��滻�Ѷ��������ٶѴ�С
        // ��ʼ�����ڵ�����ӽڵ�λ��
        int parent = 1;
        int   child = 2; 
        
        
        // �³�������ά����С������
        while (child <= size) {  // �������ӽڵ�ʱ
            if (child < size && heap[child]->weight > heap[child + 1]->weight)
                ++child;  
            // ������ӽڵ��С��ѡ�����ӽڵ�
            if (lastNode->weight <= heap[child]->weight)
                break;                         
            // �����β�ڵ�С���ӽڵ㣬ֹͣ�³�
            heap[parent] = heap[child];        // �ӽڵ�����
            parent = child;                    // ���¸��ڵ�λ��
            child *= 2;                        // �����ӽڵ�λ��
        }
        heap[parent] = lastNode;               // ����β�ڵ������ȷλ��
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
        for (char c : s) {             // �����ַ���
            if (isalpha(c)) m[c]++;    // ͳ��ÿ����ĸ�ĳ���Ƶ��
        }
        for (char c : s) {             // ��ʼ���ַ�����Ϊ "0"
            if (isalpha(c))
                m2[c] = "0";
        }
        for (auto& p : m) {            
            heap.insert(new Node(p.first, p.second));
        }
        while (heap.size > 1) {        
            Node* left = heap.removeMin();      // ɾ���Ѷ�����СȨ�ؽڵ㣩��Ϊ���ӽڵ�
            Node* right = heap.removeMin();     // �ٴ�ɾ���Ѷ���Ϊ���ӽڵ�
            Node* parent = new Node('\0', left->weight + right->weight);
            // �������ڵ㣬Ȩ��Ϊ�����ӽڵ�Ȩ��֮��
            parent->left = left;             
            parent->right = right;           
            heap.insert(parent);             
        }
        root = heap.removeMin();            
    }

    
    void printTree(Node* node, string prefix = "") {
        if (!node) return;                  
        if (!node->left && !node->right) {  // �����Ҷ�ӽڵ�
            cout << node->ch << ": " << prefix << endl; // ��ӡ�ַ��������
            m2[node->ch] = prefix;      
        }
        else {                             // �������Ҷ�ӽڵ㣬�ݹ鴦����������
            printTree(node->left, prefix + "0");
            printTree(node->right, prefix + "1");
        }
    }
    void printTree() {                     
        printTree(root);
    }

    // ���ַ�������ɹ�����
    void code(string s) {
        for (int i = 0; i < s.length(); i++) { 
            for (auto& p : m2) {              
                if (s[i] == p.first) {        // ����ַ�ƥ��
                    cout << p.second;         
                    encodestr += p.second;    // ������׷�ӵ������ַ�����
                }
            }
        }
        cout << endl;
    }

    // ����
    void decode(string s) {
        Node* current = root;              // �Ӹ��ڵ㿪ʼ����
        for (char c : s) {                
            if (c == '0') {                // ����� '0'������������
                current = current->left;
            }
            else if (c == '1') {           // ����� '1'������������
                current = current->right;
            }
            if (!current->left && !current->right) { // ���Ҷ�ڵ�
                cout << current->ch;   // ���Ҷ�ڵ���ַ�
                current = root;           // ���ص����ڵ�
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
    cout << "�����:" << endl;
    huffman.code(s);               
    cout << "�����:" << endl;
    huffman.decode(huffman.encodestr); 
    return 0;                      
}
