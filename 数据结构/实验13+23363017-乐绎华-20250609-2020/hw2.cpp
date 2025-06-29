
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight;
};

const int N = 9; // 顶点数
const int E = 11; // 边数

// 边的定义
Edge edges[E] = {
    {0, 1, 6},  // a1
    {0, 2, 4},  // a2
    {0, 3, 5},  // a3
    {1, 4, 1},  // a4
    {2, 4, 1},  // a5
    {3, 5, 2},  // a6
    {4, 6, 9},  // a7
    {4, 7, 7},  // a8
    {5, 7, 4},  // a9
    {6, 8, 2},  // a10
    {7, 8, 4}   // a11
};

vector<pair<int, int>> G[N]; // 邻接表，pair<终点, 权重>
vector<pair<int, int>> invG[N]; // 逆邻接表

int ve[N]; // 最早发生时间
int vl[N]; // 最迟发生时间
int inDegree[N] = {0}; // 入度
int outDegree[N] = {0}; // 出度
vector<int> topo; // 拓扑序列

void buildGraph() {
    for (int i = 0; i < E; ++i) {
        G[edges[i].from].push_back({edges[i].to, edges[i].weight});
        invG[edges[i].to].push_back({edges[i].from, edges[i].weight});
        inDegree[edges[i].to]++;
        outDegree[edges[i].from]++;
    }
}

bool topologicalSort() {
    queue<int> q;
    for (int i = 0; i < N; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        cnt++;
        for (auto &e : G[u]) {
            int v = e.first;
            if (--inDegree[v] == 0)
                q.push(v);
        }
    }
    return cnt == N;
}

void criticalPath() {
    // 1. 正向计算ve
    fill(ve, ve + N, 0);
    for (int i = 0; i < topo.size(); ++i) {
        int u = topo[i];
        for (auto &e : G[u]) {
            int v = e.first, w = e.second;
            ve[v] = max(ve[v], ve[u] + w);
        }
    }

    // 2. 逆向计算vl
    fill(vl, vl + N, ve[topo.back()]);
    for (int i = topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        for (auto &e : G[u]) {
            int v = e.first, w = e.second;
            vl[u] = min(vl[u], vl[v] - w);
        }
    }

    // 3. 输出关键活动
    cout << "关键路径上的活动（边）为：" << endl;
    for (int i = 0; i < E; ++i) {
        int u = edges[i].from, v = edges[i].to, w = edges[i].weight;
        int ee = ve[u];
        int el = vl[v] - w;
        if (ee == el) {
            cout << "v" << (u+1) << " -> v" << (v+1) << " (权重=" << w << ")" << endl;
        }
    }
    cout << "关键路径长度（项目工期）为：" << ve[topo.back()] << endl;
}

int main() {
    buildGraph();
    if (!topologicalSort()) {
        cout << "图中存在环，无法进行关键路径分析！" << endl;
        return 0;
    }
    criticalPath();
    return 0;
}
