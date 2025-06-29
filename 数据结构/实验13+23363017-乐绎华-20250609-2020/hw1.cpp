#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void topologicalSort();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::topologicalSort() {
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int cnt = 0;
    vector<int> top_order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
        cnt++;
    }

    if (cnt != V) {
        cout << "There exists a cycle in the graph\n";
        return;
    }

    cout << "Topological Sort: ";
    for (int i = 0; i < top_order.size(); i++) {
        cout << top_order[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== 拓扑排序演示 ===" << endl;
    
    // 情况1: 有向无环图(DAG)
    {
        cout << "\n情况1: 有向无环图" << endl;
        int V = 6;  // 6个顶点
        int E = 8;  // 8条边
        
        Graph g1(V);
        
        // 添加预定义的边
        g1.addEdge(5, 2);
        g1.addEdge(5, 0);
        g1.addEdge(4, 0);
        g1.addEdge(4, 1);
        g1.addEdge(2, 3);
        g1.addEdge(3, 1);
        g1.addEdge(0, 3);
        g1.addEdge(1, 3);
        
        cout << "图中顶点数: " << V << endl;
        cout << "图中边数: " << E << endl;
        cout << "已添加的边:" << endl;
        cout << "5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1" << endl;
        cout << "2 -> 3, 3 -> 1, 0 -> 3, 1 -> 3" << endl;
        
        // 执行拓扑排序
        g1.topologicalSort();
    }
    
    // 情况2: 有向图中存在环
    {
        cout << "\n情况2: 有向图中存在环" << endl;
        int V = 4;  // 4个顶点
        int E = 4;  // 4条边
        
        Graph g2(V);
        
        // 添加形成环的边
        g2.addEdge(0, 1);
        g2.addEdge(1, 2);
        g2.addEdge(2, 3);
        g2.addEdge(3, 0);  // 这条边形成了环
        
        cout << "图中顶点数: " << V << endl;
        cout << "图中边数: " << E << endl;
        cout << "已添加的边:" << endl;
        cout << "0 -> 1, 1 -> 2, 2 -> 3, 3 -> 0 (形成环)" << endl;
        
        // 执行拓扑排序
        g2.topologicalSort();
    }
    
    // 情况3: 单路径图
    {
        cout << "\n情况3: 单路径图" << endl;
        int V = 5;  // 5个顶点
        int E = 4;  // 4条边
        
        Graph g3(V);
        
        // 添加单路径的边
        g3.addEdge(0, 1);
        g3.addEdge(1, 2);
        g3.addEdge(2, 3);
        g3.addEdge(3, 4);
        
        cout << "图中顶点数: " << V << endl;
        cout << "图中边数: " << E << endl;
        cout << "已添加的边:" << endl;
        cout << "0 -> 1, 1 -> 2, 2 -> 3, 3 -> 4" << endl;
        
        // 执行拓扑排序
        g3.topologicalSort();
    }
    
    // 情况4: 没有边的图
    {
        cout << "\n情况4: 没有边的图" << endl;
        int V = 4;  // 4个顶点
        int E = 0;  // 0条边
        
        Graph g4(V);
        
        cout << "图中顶点数: " << V << endl;
        cout << "图中边数: " << E << endl;
        cout << "图中没有边" << endl;
        
        // 执行拓扑排序
        g4.topologicalSort();
    }

    return 0;
}
