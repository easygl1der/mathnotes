// 3. 针对无向图，设计如下算法：
// （1）将无向图的邻接矩阵转换为邻接表（参考实验书第103页）
// （2）将无向图的邻接表转换为邻接矩阵（参考实验书第103页）
// （3）求无向图的深度优先生成树（参考实验书第92页）



#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 邻接表节点
struct AdjNode {
    int vertex;
    AdjNode* next;
    AdjNode(int v) : vertex(v), next(nullptr) {}
};

// 邻接表
struct AdjList {
    AdjNode* head;
    AdjList() : head(nullptr) {}
};

// （1）邻接矩阵转邻接表
void matrixToList(const vector<vector<int>>& matrix, vector<AdjList>& adjList) {
    int n = matrix.size();
    adjList.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) { // 逆序插入，方便头插法
            if (matrix[i][j]) {
                AdjNode* node = new AdjNode(j);
                node->next = adjList[i].head;
                adjList[i].head = node;
            }
        }
    }
}

// （2）邻接表转邻接矩阵
void listToMatrix(const vector<AdjList>& adjList, vector<vector<int>>& matrix) {
    int n = adjList.size();
    matrix.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        AdjNode* curr = adjList[i].head;
        while (curr) {
            matrix[i][curr->vertex] = 1;
            curr = curr->next;
        }
    }
}

// （3）求无向图的深度优先生成树（DFS生成树）
void DFSUtil(int u, vector<AdjList>& adjList, vector<bool>& visited, vector<pair<int, int>>& treeEdges) {
    visited[u] = true;
    AdjNode* curr = adjList[u].head;
    while (curr) {
        int v = curr->vertex;
        if (!visited[v]) {
            treeEdges.push_back({u, v});
            DFSUtil(v, adjList, visited, treeEdges);
        }
        curr = curr->next;
    }
}

vector<pair<int, int>> DFSTree(vector<AdjList>& adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<pair<int, int>> treeEdges;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            DFSUtil(i, adjList, visited, treeEdges);
        }
    }
    return treeEdges;
}

// 辅助函数：打印邻接表
void printAdjList(const vector<AdjList>& adjList) {
    for (int i = 0; i < adjList.size(); ++i) {
        cout << i << ":";
        AdjNode* curr = adjList[i].head;
        while (curr) {
            cout << " " << curr->vertex;
            curr = curr->next;
        }
        cout << endl;
    }
}

// 辅助函数：打印邻接矩阵
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// 辅助函数：打印DFS生成树的边
void printDFSTree(const vector<pair<int, int>>& treeEdges) {
    cout << "DFS Tree Edges:" << endl;
    for (const auto& edge : treeEdges) {
        cout << edge.first << " - " << edge.second << endl;
    }
}

// 示例主函数
int main() {

    // The graph structure:
    //
    //      0
    //     / \
    //    1---2
    //    |   |
    //    3---4
    //
    // Adjacency matrix for reference:
    vector<vector<int>> matrix = {
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,0,1},
        {0,1,0,0,1},
        {0,0,1,1,0}
    };

    // 1. 邻接矩阵转邻接表
    vector<AdjList> adjList;
    matrixToList(matrix, adjList);
    cout << "Adjacency List:" << endl;
    printAdjList(adjList);

    // 2. 邻接表转邻接矩阵
    vector<vector<int>> matrix2;
    listToMatrix(adjList, matrix2);
    cout << "Adjacency Matrix:" << endl;
    printMatrix(matrix2);

    // 3. 求DFS生成树
    vector<pair<int, int>> treeEdges = DFSTree(adjList);
    printDFSTree(treeEdges);

    // 释放邻接表内存
    for (auto& list : adjList) {
        AdjNode* curr = list.head;
        while (curr) {
            AdjNode* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }

    return 0;
}






