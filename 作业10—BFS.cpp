#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    // 获取顶点数量
    int numberOfV() const { return List.size(); }

    
    void addEdge(int u, int v) {
        List[u].push_back(v);
        
    }

    // 使用BFS寻找最短路径
    int* findSPath(int theSource, int theDestination) {
        int n = numberOfV(); // 获取顶点数量

        // 存储前驱节点 现在初始化为-1
        vector<int> parent(n + 1, -1);

        // 记录节点是否已访问 现在初始化为F
        vector<bool> visited(n + 1, false);

        // 队列用于BFS
        queue<int> q;

        // 将起点加入队列并标记为已访问
        visited[theSource] = true;
        q.push(theSource);

        // BFS搜索路径
        while (!q.empty()) {
            int current = q.front();
            q.pop();

            // 如果找到目标顶点，停止搜索
            if (current == theDestination) break;

            // 遍历当前节点的所有邻接点
            for (int i = 0; i < List[current].size(); ++i) {
                int neighbor = List[current][i]; // 获取邻节点
                if (!visited[neighbor]) {          // 只访问未访问的节点
                    visited[neighbor] = true;      // 标记为已访问
                    parent[neighbor] = current;    // 记录前驱节点
                    q.push(neighbor);              // 将节点加入队列
                }
            }

        }

        // 检查是否找到了路径
        if (!visited[theDestination]) return NULL;

        // 构建路径，从终点回溯到起点
        vector<int> tempPath;
        for (int at = theDestination; at != -1; at = parent[at]) {
            tempPath.push_back(at);
        }
        reverse(tempPath.begin(), tempPath.end()); // 反转路径，得到正序

        // 将路径转换为动态数组格式
        int* path = new int[tempPath.size() + 1];
        path[0] = tempPath.size() - 1; // 路径长度存储在path[0]
        for (int i = 0; i < tempPath.size(); ++i) {
            path[i + 1] = tempPath[i]; // 路径点从path[1]开始
        }
        return path; // 返回路径数组
    }

private:
    // 邻接表
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
