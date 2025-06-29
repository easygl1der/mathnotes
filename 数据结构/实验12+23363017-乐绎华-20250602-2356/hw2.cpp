#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const int MaxSize = 20;  // 最多顶点个数

template <class DataType>
class MGraph
{
public:
    MGraph(int n);  // 构造函数，建立具有n个顶点的图
    ~MGraph() {};
    void Prim(int v);  // Prim算法构造最小生成树
    void Dijkstra(int start);  // Dijkstra算法求单源最短路径
    void readMatrixFromFile(const string& filename);  // 从文件读取邻接矩阵
    void displayMatrix();  // 显示邻接矩阵
    void setVertexName(int index, const DataType& name);  // 设置顶点名称

private:
    DataType vertex[MaxSize];     // 存放图中顶点的数组
    int edge[MaxSize][MaxSize];   // 存放图中边的数组  
    int vertexNum;                // 图的顶点数
    
    int MinEdge(int lowcost[], int n);  // 找最小边
    int MinDistance(int dist[], bool visited[], int n);  // Dijkstra中找最小距离
};

template <class DataType>
MGraph<DataType>::MGraph(int n)
{
    vertexNum = n;
    
    // 初始化顶点名称为v0, v1, v2, ...
    for (int i = 0; i < vertexNum; i++) {
        vertex[i] = "v" + to_string(i);  // 生成v0, v1, v2, ...
    }
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            edge[i][j] = (i == j) ? 0 : INT_MAX;
}

template <class DataType>
void MGraph<DataType>::setVertexName(int index, const DataType& name)
{
    if (index >= 0 && index < vertexNum) {
        vertex[index] = name;
    }
}

template <class DataType>
void MGraph<DataType>::readMatrixFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filename << endl;
        return;
    }
    
    string line;
    int row = 0;
    
    while (getline(file, line) && row < vertexNum) {
        stringstream ss(line);
        string value;
        int col = 0;
        
        while (ss >> value && col < vertexNum) {
            if (value == "∞" || value == "INF" || value == "inf") {
                edge[row][col] = INT_MAX;
            } else {
                int weight = stoi(value);
                edge[row][col] = weight;
            }
            col++;
        }
        row++;
    }
    
    file.close();
    cout << "成功读取 " << row << "x" << row << " 的邻接矩阵" << endl;
}

template <class DataType>
void MGraph<DataType>::displayMatrix()
{
    cout << "\n邻接矩阵表示（有向图）：" << endl;
    cout << "==============================================================================" << endl;
    
    // 打印顶点编号对应关系
    cout << "顶点编号对应关系：" << endl;
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]" << vertex[i] << "  ";
        if ((i + 1) % 5 == 0) cout << endl;
    }
    if (vertexNum % 5 != 0) cout << endl;
    cout << "==============================================================================" << endl;
    
    // 打印表头
    cout << "From\\To\t";
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]\t";
    }
    cout << endl;
    
    // 打印邻接矩阵
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]\t";
        for (int j = 0; j < vertexNum; j++) {
            if (edge[i][j] == INT_MAX) {
                cout << "∞\t";
            } else {
                cout << edge[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << "==============================================================================" << endl;
    cout << "注：∞表示无直接连接的边，0表示自环" << endl;
}

template <class DataType>
void MGraph<DataType>::Prim(int startVertex)
{
    int adjvex[MaxSize], lowcost[MaxSize];
    int totalCost = 0;  // 记录总成本
    
    cout << "\n使用Prim算法构造最小生成树（有向图）：" << endl;
    cout << "起始顶点：[" << startVertex << "]" << vertex[startVertex] << endl;
    cout << "\n生成树的边：" << endl;
    
    // 初始化辅助数组
    for (int i = 0; i < vertexNum; i++) {
        if (edge[startVertex][i] != INT_MAX) {
            lowcost[i] = edge[startVertex][i];
        } else {
            lowcost[i] = INT_MAX;
        }
        adjvex[i] = startVertex;
    }
    lowcost[startVertex] = 0;  // 将起始顶点加入集合U
    
    // 迭代 vertexNum-1 次，每次添加一条边
    for (int k = 1; k < vertexNum; k++) {
        int j = MinEdge(lowcost, vertexNum);  // 寻找最短边的邻接点j
        
        if (j == -1) {
            cout << "图不连通，无法构造生成树！" << endl;
            return;
        }
        
        cout << k << ". [" << adjvex[j] << "]" << vertex[adjvex[j]] << " -> [" 
             << j << "]" << vertex[j] << " (权重: " << lowcost[j] << ")" << endl;
        
        totalCost += lowcost[j];
        lowcost[j] = 0;  // 顶点j加入集合U
        
        // 调整辅助数组 - 有向图处理
        for (int i = 0; i < vertexNum; i++) {
            if (edge[j][i] != INT_MAX && edge[j][i] < lowcost[i]) {
                lowcost[i] = edge[j][i];
                adjvex[i] = j;
            }
        }
    }
    
    cout << "\n最小生成树构造完成！" << endl;
    cout << "总权重：" << totalCost << endl;
    cout << "连接了" << vertexNum << "个顶点！" << endl;
}

template <class DataType>
int MGraph<DataType>::MinEdge(int lowcost[], int n)
{
    int index = -1;
    int min = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (lowcost[i] != 0 && lowcost[i] < min) {
            min = lowcost[i];
            index = i;
        }
    }
    return index;
}

template <class DataType>
void MGraph<DataType>::Dijkstra(int start)
{
    int dist[MaxSize];      // 存储最短距离
    bool visited[MaxSize];  // 标记是否已访问
    int prev[MaxSize];      // 记录前驱顶点，用于输出路径
    
    cout << "\n使用Dijkstra算法求单源最短路径：" << endl;
    cout << "起始顶点：[" << start << "]" << vertex[start] << endl;
    cout << "===========================================" << endl;
    
    // 初始化
    for (int i = 0; i < vertexNum; i++) {
        dist[i] = edge[start][i];  // 初始距离
        visited[i] = false;        // 都未访问
        if (edge[start][i] != INT_MAX && i != start) {
            prev[i] = start;       // 如果有直接边，前驱是起始点
        } else {
            prev[i] = -1;          // 无前驱
        }
    }
    
    dist[start] = 0;        // 起始点到自己距离为0
    visited[start] = true;  // 标记起始点已访问
    
    // 找到所有顶点的最短路径
    for (int count = 1; count < vertexNum; count++) {
        int u = MinDistance(dist, visited, vertexNum);
        
        if (u == -1) break;  // 剩余顶点不可达
        
        visited[u] = true;
        
        // 更新通过u到达其他顶点的距离
        for (int v = 0; v < vertexNum; v++) {
            if (!visited[v] && edge[u][v] != INT_MAX && 
                dist[u] != INT_MAX && dist[u] + edge[u][v] < dist[v]) {
                dist[v] = dist[u] + edge[u][v];
                prev[v] = u;
            }
        }
    }
    
    // 输出结果
    cout << "最短路径结果：" << endl;
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << start << "]" << vertex[start] << " 到 [" << i << "]" << vertex[i] << ": ";
        
        if (dist[i] == INT_MAX) {
            cout << "不可达" << endl;
        } else if (i == start) {
            cout << "距离 = 0 (起始点)" << endl;
        } else {
            cout << "距离 = " << dist[i];
            
            // 输出路径
            cout << ", 路径: ";
            vector<int> path;
            int current = i;
            while (current != -1) {
                path.push_back(current);
                current = prev[current];
            }
            
            // 反向输出路径
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << "[" << path[j] << "]" << vertex[path[j]];
                if (j > 0) cout << " → ";
            }
            cout << endl;
        }
    }
}

template <class DataType>
int MGraph<DataType>::MinDistance(int dist[], bool visited[], int n)
{
    int min = INT_MAX;
    int minIndex = -1;
    
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    
    return minIndex;
}

int main()
{
#ifdef _WIN32
    // 设置控制台代码页为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // 设置本地化
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif

    cout << "=== 有向图单源最短路径算法（Dijkstra） ===" << endl;
    
    // 固定参数：6个顶点，使用test_matrix.txt文件，从顶点0开始
    int vertexCount = 6;
    int startVertex = 0;
    string filename = "test_matrix.txt";
    
    cout << "顶点数量: " << vertexCount << endl;
    cout << "邻接矩阵文件: " << filename << endl;
    cout << "起始顶点: [" << startVertex << "]" << endl;
    cout << "============================================" << endl;
    
    // 创建图对象
    MGraph<string> graph(vertexCount);
    
    // 从文件读取邻接矩阵
    graph.readMatrixFromFile(filename);
    
    // 显示邻接矩阵
    graph.displayMatrix();
    
    // 使用Dijkstra算法求单源最短路径
    graph.Dijkstra(startVertex);
    
    cout << "\n程序结束。" << endl;
    
    return 0;
}
