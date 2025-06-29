// 4. 对于有向图，设计算法

// (4) 设有向图 G采用邻接矩阵存储，计算图中出度为零的顶点个数：实验书 p104
// (5) 设有向图G采用邻接表存储，设计算法求图G中每个顶点的入度
// (6) 己知一个有向图的邻接表，建立其逆邻接表。实验书 p104



#include <iostream>
#include <vector>
using namespace std;

// (4) 设有向图 G采用邻接矩阵存储，计算图中出度为零的顶点个数
int countZeroOutDegree(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    int count = 0;
    for (int i = 0; i < n; ++i) {
        bool hasOut = false;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0) {
                hasOut = true;
                break;
            }
        }
        if (!hasOut) count++;
    }
    return count;
}

// (5) 设有向图G采用邻接表存储，设计算法求图G中每个顶点的入度
vector<int> calculateInDegree(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<int> inDegree(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            inDegree[v]++;
        }
    }
    return inDegree;
}

// (6) 已知一个有向图的邻接表，建立其逆邻接表
vector<vector<int>> buildReverseAdjList(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<vector<int>> reverseAdjList(n);
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            reverseAdjList[v].push_back(u);
        }
    }
    return reverseAdjList;
}

// 辅助函数：打印邻接矩阵
void printMatrix(const vector<vector<int>>& matrix) {
    cout << "邻接矩阵：" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// 辅助函数：打印邻接表
void printAdjList(const vector<vector<int>>& adjList) {
    cout << "邻接表：" << endl;
    for (int i = 0; i < adjList.size(); ++i) {
        cout << i << ":";
        for (int v : adjList[i]) {
            cout << " " << v;
        }
        cout << endl;
    }
}

// 辅助函数：打印入度数组
void printInDegree(const vector<int>& inDegree) {
    cout << "各顶点入度：" << endl;
    for (int i = 0; i < inDegree.size(); ++i) {
        cout << "顶点" << i << "的入度：" << inDegree[i] << endl;
    }
}

int main() {
    // 测试有向图
    // 图结构：
    //   0 → 1 → 2
    //   ↓       ↑
    //   3 ------↗
    
    // (4) 测试邻接矩阵存储的有向图，计算出度为零的顶点个数
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 1},  // 顶点0指向顶点1和3
        {0, 0, 1, 0},  // 顶点1指向顶点2
        {0, 0, 0, 0},  // 顶点2没有出边（出度为0）
        {0, 0, 1, 0}   // 顶点3指向顶点2
    };
    
    printMatrix(adjMatrix);
    int zeroOutCount = countZeroOutDegree(adjMatrix);
    cout << "出度为零的顶点个数：" << zeroOutCount << endl << endl;
    
    // (5) 测试邻接表存储的有向图，计算各顶点入度
    vector<vector<int>> adjList = {
        {1, 3},  // 顶点0的邻接表：指向1和3
        {2},     // 顶点1的邻接表：指向2
        {},      // 顶点2的邻接表：空（出度为0）
        {2}      // 顶点3的邻接表：指向2
    };
    
    printAdjList(adjList);
    vector<int> inDegree = calculateInDegree(adjList);
    printInDegree(inDegree);
    cout << endl;
    
    // (6) 测试建立逆邻接表
    vector<vector<int>> reverseAdjList = buildReverseAdjList(adjList);
    cout << "逆邻接表：" << endl;
    printAdjList(reverseAdjList);
    
    return 0;
}










