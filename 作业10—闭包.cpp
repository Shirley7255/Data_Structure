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
        vector<int> component(n + 1, -1); // 存储每个顶点的连通分量编号
        int compID = 0; // 当前连通分量编号

        // 深度优先搜索标记连通分量
        for (int i = 1; i <= n; ++i) {
            if (component[i] == -1) {
                dfs(i, compID++, component);
            }
        }

        // 构造传递闭包矩阵
        vector<vector<int>> tc(n + 1, vector<int>(n + 1, 0));
        //遍历每一对顶点 (i, j)
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                // 如果顶点 i 和顶点 j 属于同一个连通分量
                if (component[i] == component[j]) {
                    tc[i][j] = 1;//
                }
            }
        }

        return tc;
    }

private:
    int n;                              // 图的顶点数
    vector<vector<int>> List;        // 邻接表

    void dfs(int node, int compID, vector<int>& component) {
        component[node] = compID;       // 标记当前节点为当前连通分量
        // 遍历与当前节点相邻的所有节点
        for (int i = 0; i < List[node].size(); ++i) {
            int neighbor = List[node][i];
            // 如果邻居节点尚未被访问（未被标记为任何连通分量）
            if (component[neighbor] == -1) {
                dfs(neighbor, compID, component); // 对邻居节点进行递归调用，继续深度优先搜索
            }
        }

    }
};

int main() {
    int n = 6; // 顶点数
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
