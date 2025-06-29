#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const int MaxSize = 20;

// 邻接表节点
struct AdjNode {
    int vertex;          // 邻接顶点
    AdjNode* next;       // 指向下一个邻接顶点
    
    AdjNode(int v) : vertex(v), next(nullptr) {}
};

// 邻接表存储的有向图
class ALGraph {
private:
    string vertex[MaxSize];      // 顶点数组
    AdjNode* adjList[MaxSize];   // 邻接表数组
    int vertexNum;               // 顶点数

public:
    ALGraph(int n);
    ~ALGraph();
    void addEdge(int from, int to);                    // 添加边
    void createFromMatrix(const string& filename);     // 从邻接矩阵文件创建图
    void displayGraph();                              // 显示邻接表
    
    // DFS路径查找
    bool DFS_Path(int start, int end, vector<int>& path);
    bool DFS_Helper(int current, int end, vector<int>& path, vector<bool>& visited);
    
    // BFS路径查找
    bool BFS_Path(int start, int end, vector<int>& path);
    
    // 辅助函数
    void setVertexName(int index, const string& name);
    string getVertexName(int index) const;
    int getVertexNum() const { return vertexNum; }
};

ALGraph::ALGraph(int n) {
    vertexNum = n;
    // 初始化顶点名称
    for (int i = 0; i < vertexNum; i++) {
        vertex[i] = "v" + to_string(i);
        adjList[i] = nullptr;
    }
}

ALGraph::~ALGraph() {
    // 释放邻接表内存
    for (int i = 0; i < vertexNum; i++) {
        AdjNode* current = adjList[i];
        while (current) {
            AdjNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void ALGraph::setVertexName(int index, const string& name) {
    if (index >= 0 && index < vertexNum) {
        vertex[index] = name;
    }
}

string ALGraph::getVertexName(int index) const {
    if (index >= 0 && index < vertexNum) {
        return vertex[index];
    }
    return "";
}

void ALGraph::addEdge(int from, int to) {
    if (from >= 0 && from < vertexNum && to >= 0 && to < vertexNum) {
        AdjNode* newNode = new AdjNode(to);
        newNode->next = adjList[from];
        adjList[from] = newNode;
    }
}

void ALGraph::createFromMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filename << endl;
        return;
    }
    
    // 读取邻接矩阵并转换为邻接表
    string line;
    int row = 0;
    
    while (getline(file, line) && row < vertexNum) {
        stringstream ss(line);
        string value;
        int col = 0;
        
        while (ss >> value && col < vertexNum) {
            if (value != "∞" && value != "INF" && value != "inf") {
                int weight = stoi(value);
                if (weight > 0 && row != col) {  // 有边且不是自环
                    addEdge(row, col);
                }
            }
            col++;
        }
        row++;
    }
    
    file.close();
    cout << "成功从邻接矩阵创建邻接表 (" << row << "个顶点)" << endl;
}

void ALGraph::displayGraph() {
    cout << "\n邻接表表示：" << endl;
    cout << "==========================================" << endl;
    
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]" << vertex[i] << ": ";
        
        AdjNode* current = adjList[i];
        if (!current) {
            cout << "无邻接顶点";
        } else {
            while (current) {
                cout << "[" << current->vertex << "]" << vertex[current->vertex];
                if (current->next) cout << " → ";
                current = current->next;
            }
        }
        cout << endl;
    }
    cout << "==========================================" << endl;
}

// DFS路径查找
bool ALGraph::DFS_Path(int start, int end, vector<int>& path) {
    vector<bool> visited(vertexNum, false);
    path.clear();
    
    cout << "\n=== 深度优先搜索(DFS)路径查找 ===" << endl;
    cout << "从 " << vertex[start] << " 到 " << vertex[end] << endl;
    
    bool found = DFS_Helper(start, end, path, visited);
    
    if (found) {
        cout << "找到路径: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << vertex[path[i]];
            if (i < path.size() - 1) cout << " → ";
        }
        cout << endl;
        cout << "路径长度: " << path.size() - 1 << " 条边" << endl;
    } else {
        cout << "不存在从 " << vertex[start] << " 到 " << vertex[end] << " 的路径" << endl;
    }
    
    return found;
}

bool ALGraph::DFS_Helper(int current, int end, vector<int>& path, vector<bool>& visited) {
    visited[current] = true;
    path.push_back(current);
    
    // 如果到达目标顶点
    if (current == end) {
        return true;
    }
    
    // 遍历当前顶点的所有邻接顶点
    AdjNode* adjNode = adjList[current];
    while (adjNode) {
        int next = adjNode->vertex;
        if (!visited[next]) {
            if (DFS_Helper(next, end, path, visited)) {
                return true;
            }
        }
        adjNode = adjNode->next;
    }
    
    // 回溯
    path.pop_back();
    return false;
}

// BFS路径查找
bool ALGraph::BFS_Path(int start, int end, vector<int>& path) {
    path.clear();
    
    cout << "\n=== 广度优先搜索(BFS)路径查找 ===" << endl;
    cout << "从 " << vertex[start] << " 到 " << vertex[end] << endl;
    
    if (start == end) {
        path.push_back(start);
        cout << "起点和终点相同: " << vertex[start] << endl;
        return true;
    }
    
    vector<bool> visited(vertexNum, false);
    vector<int> parent(vertexNum, -1);  // 记录路径
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    bool found = false;
    
    while (!q.empty() && !found) {
        int current = q.front();
        q.pop();
        
        // 遍历当前顶点的所有邻接顶点
        AdjNode* adjNode = adjList[current];
        while (adjNode) {
            int next = adjNode->vertex;
            
            if (!visited[next]) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
                
                if (next == end) {
                    found = true;
                    break;
                }
            }
            adjNode = adjNode->next;
        }
    }
    
    if (found) {
        // 重构路径
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        
        cout << "找到路径: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << vertex[path[i]];
            if (i < path.size() - 1) cout << " → ";
        }
        cout << endl;
        cout << "路径长度: " << path.size() - 1 << " 条边" << endl;
    } else {
        cout << "不存在从 " << vertex[start] << " 到 " << vertex[end] << " 的路径" << endl;
    }
    
    return found;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif

    cout << "=== 有向图路径查找算法(DFS & BFS) ===" << endl;
    
    // 固定参数
    int vertexCount = 6;
    string filename = "test_matrix.txt";
    
    cout << "顶点数量: " << vertexCount << endl;
    cout << "邻接矩阵文件: " << filename << endl;
    cout << "========================================" << endl;
    
    // 创建邻接表图
    ALGraph graph(vertexCount);
    
    // 从文件创建图
    graph.createFromMatrix(filename);
    
    // 显示邻接表
    graph.displayGraph();
    
    // 测试多组路径查找
    vector<pair<int, int>> testCases = {
        {0, 3},  // v0 到 v3
        {0, 5},  // v0 到 v5  
        {1, 4},  // v1 到 v4
        {2, 5},  // v2 到 v5
        {3, 1},  // v3 到 v1
        {4, 0}   // v4 到 v0
    };
    
    for (auto& testCase : testCases) {
        int start = testCase.first;
        int end = testCase.second;
        
        cout << "\n" << string(50, '=') << endl;
        cout << "测试: 从 " << graph.getVertexName(start) << " 到 " << graph.getVertexName(end) << endl;
        
        vector<int> dfsPath, bfsPath;
        
        // DFS查找
        bool dfsFound = graph.DFS_Path(start, end, dfsPath);
        
        // BFS查找  
        bool bfsFound = graph.BFS_Path(start, end, bfsPath);
        
        // 比较结果
        if (dfsFound && bfsFound) {
            cout << "\n结果比较:" << endl;
            cout << "DFS路径长度: " << dfsPath.size() - 1 << " 条边" << endl;
            cout << "BFS路径长度: " << bfsPath.size() - 1 << " 条边" << endl;
            if (dfsPath.size() == bfsPath.size()) {
                cout << "两种算法找到相同长度的路径" << endl;
            } else {
                cout << "BFS找到的是最短路径" << endl;
            }
        }
    }
    
    cout << "\n程序结束。" << endl;
    return 0;
}
