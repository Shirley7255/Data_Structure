#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
    Graph(int n) : n(n), List(n + 1) {}

    void addEdge(int u,int v) {
        List[u].push_back(v);
       
    }

    vector<vector<int>> undirectedTC() {
        vector<int> component(n + 1, -1); // �洢ÿ���������ͨ�������
        int compID = 0; // ��ǰ��ͨ�������

        // ����������������ͨ����
        for (int i = 1; i <= n; ++i) {
            if (component[i] == -1) {
                dfs(i, compID++, component);
            }
        }

        // ���촫�ݱհ�����
        vector<vector<int>> tc(n + 1, vector<int>(n + 1, 0));
        //����ÿһ�Զ��� (i, j)
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                // ������� i �Ͷ��� j ����ͬһ����ͨ����
                if (component[i] == component[j]) {
                    tc[i][j] = 1;//
                }
            }
        }

        return tc;
    }

private:
    int n;                              // ͼ�Ķ�����
    vector<vector<int>> List;        // �ڽӱ�

    void dfs(int node, int compID, vector<int>& component) {
        component[node] = compID;       // ��ǵ�ǰ�ڵ�Ϊ��ǰ��ͨ����
        // �����뵱ǰ�ڵ����ڵ����нڵ�
        for (int i = 0; i < List[node].size(); ++i) {
            int neighbor = List[node][i];
            // ����ھӽڵ���δ�����ʣ�δ�����Ϊ�κ���ͨ������
            if (component[neighbor] == -1) {
                dfs(neighbor, compID, component); // ���ھӽڵ���еݹ���ã����������������
            }
        }

    }
};

int main() {
    int n = 6; // ������
    Graph g(n);

    
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(4, 5);

    
    vector<vector<int>> tc = g.undirectedTC();

    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << tc[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
