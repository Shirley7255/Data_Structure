#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    // ��ȡ��������
    int numberOfV() const { return List.size(); }

    
    void addEdge(int u, int v) {
        List[u].push_back(v);
        
    }

    // ʹ��BFSѰ�����·��
    int* findSPath(int theSource, int theDestination) {
        int n = numberOfV(); // ��ȡ��������

        // �洢ǰ���ڵ� ���ڳ�ʼ��Ϊ-1
        vector<int> parent(n + 1, -1);

        // ��¼�ڵ��Ƿ��ѷ��� ���ڳ�ʼ��ΪF
        vector<bool> visited(n + 1, false);

        // ��������BFS
        queue<int> q;

        // ����������в����Ϊ�ѷ���
        visited[theSource] = true;
        q.push(theSource);

        // BFS����·��
        while (!q.empty()) {
            int current = q.front();
            q.pop();

            // ����ҵ�Ŀ�궥�㣬ֹͣ����
            if (current == theDestination) break;

            // ������ǰ�ڵ�������ڽӵ�
            for (int i = 0; i < List[current].size(); ++i) {
                int neighbor = List[current][i]; // ��ȡ�ڽڵ�
                if (!visited[neighbor]) {          // ֻ����δ���ʵĽڵ�
                    visited[neighbor] = true;      // ���Ϊ�ѷ���
                    parent[neighbor] = current;    // ��¼ǰ���ڵ�
                    q.push(neighbor);              // ���ڵ�������
                }
            }

        }

        // ����Ƿ��ҵ���·��
        if (!visited[theDestination]) return NULL;

        // ����·�������յ���ݵ����
        vector<int> tempPath;
        for (int at = theDestination; at != -1; at = parent[at]) {
            tempPath.push_back(at);
        }
        reverse(tempPath.begin(), tempPath.end()); // ��ת·�����õ�����

        // ��·��ת��Ϊ��̬�����ʽ
        int* path = new int[tempPath.size() + 1];
        path[0] = tempPath.size() - 1; // ·�����ȴ洢��path[0]
        for (int i = 0; i < tempPath.size(); ++i) {
            path[i + 1] = tempPath[i]; // ·�����path[1]��ʼ
        }
        return path; // ����·������
    }

private:
    // �ڽӱ�
    vector<vector<int>> List = vector<vector<int>>(101);
};

int main() {
    Graph g;
    //1--2--3
    //|    /
    //4-- 5
    
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(1, 3);
    
    
    int* path = g.findSPath(1, 3);

    
    if (path) {
        cout << "Path length: " << path[0] <<endl;
        cout << "Path:";
        for (int i = 1; i <= path[0] + 1; ++i) {
            cout << path[i] << " ";
        }
        cout << endl;

        
        delete[] path;
    }
    else {
        cout << "No path found!" << endl;
    }

    return 0;
}
