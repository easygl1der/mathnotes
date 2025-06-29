#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const int MaxSize = 20;
const int INF = 999999;  // 表示无穷大

class HospitalLocation {
private:
    string vertex[MaxSize];      // 顶点名称数组
    int adjMatrix[MaxSize][MaxSize];  // 邻接矩阵
    int dist[MaxSize][MaxSize];  // Floyd算法结果矩阵
    int vertexNum;               // 顶点数

public:
    HospitalLocation(int n);
    void initializeGraph();     // 初始化图15-3的数据
    void readFromMatrix(const string& filename);  // 从文件读取邻接矩阵
    void displayAdjMatrix();    // 显示邻接矩阵
    void Floyd();              // Floyd算法求所有顶点对最短路径
    void displayDistMatrix();  // 显示最短距离矩阵
    void calculateEccentricity(); // 计算偏心度并找到中心点
    void setVertexName(int index, const string& name);
    string getVertexName(int index) const;
};

HospitalLocation::HospitalLocation(int n) {
    vertexNum = n;
    
    // 初始化顶点名称
    for (int i = 0; i < vertexNum; i++) {
        vertex[i] = "v" + to_string(i);
    }
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (i == j) {
                adjMatrix[i][j] = 0;
                dist[i][j] = 0;
            } else {
                adjMatrix[i][j] = INF;
                dist[i][j] = INF;
            }
        }
    }
}

void HospitalLocation::setVertexName(int index, const string& name) {
    if (index >= 0 && index < vertexNum) {
        vertex[index] = name;
    }
}

string HospitalLocation::getVertexName(int index) const {
    if (index >= 0 && index < vertexNum) {
        return vertex[index];
    }
    return "";
}

void HospitalLocation::initializeGraph() {
    // 根据图15-3(a)初始化图的数据
    // 顶点：a, b, c, d, e (对应索引 0, 1, 2, 3, 4)
    setVertexName(0, "a");
    setVertexName(1, "b");
    setVertexName(2, "c");
    setVertexName(3, "d");
    setVertexName(4, "e");
    
    // 添加边（根据图15-3(a)）
    adjMatrix[0][1] = 1;  // a -> b: 1
    adjMatrix[1][2] = 2;  // b -> c: 2
    adjMatrix[1][3] = 1;  // b -> d: 1
    adjMatrix[2][4] = 4;  // c -> e: 4
    adjMatrix[2][3] = 3;  // c -> d: 3
    adjMatrix[3][4] = 5;  // d -> e: 5
    adjMatrix[4][2] = 2;  // e -> c: 2
    
    cout << "已加载图15-3的示例数据" << endl;
}

void HospitalLocation::displayAdjMatrix() {
    cout << "\n原始邻接矩阵：" << endl;
    cout << string(60, '=') << endl;
    
    // 打印表头
    cout << setw(8) << "顶点\\顶点";
    for (int i = 0; i < vertexNum; i++) {
        cout << setw(8) << vertex[i];
    }
    cout << endl;
    
    // 打印矩阵
    for (int i = 0; i < vertexNum; i++) {
        cout << setw(8) << vertex[i];
        for (int j = 0; j < vertexNum; j++) {
            if (adjMatrix[i][j] == INF) {
                cout << setw(8) << "∞";
            } else {
                cout << setw(8) << adjMatrix[i][j];
            }
        }
        cout << endl;
    }
    cout << string(60, '=') << endl;
}

void HospitalLocation::Floyd() {
    // 初始化距离矩阵
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            dist[i][j] = adjMatrix[i][j];
        }
    }
    
    // Floyd算法核心
    for (int k = 0; k < vertexNum; k++) {
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

void HospitalLocation::displayDistMatrix() {
    // 简化：不再显示最短距离矩阵
}

void HospitalLocation::calculateEccentricity() {
    vector<int> eccentricity(vertexNum);
    int minEccentricity = INF;
    int centerVertex = -1;
    
    for (int j = 0; j < vertexNum; j++) {  // 对每个顶点j
        int maxDist = 0;
        bool hasIncomingPath = false;
        
        for (int i = 0; i < vertexNum; i++) {
            if (i != j && dist[i][j] != INF) {
                maxDist = max(maxDist, dist[i][j]);
                hasIncomingPath = true;
            }
        }
        
        if (!hasIncomingPath) {
            eccentricity[j] = INF;
        } else {
            eccentricity[j] = maxDist;
            if (eccentricity[j] < minEccentricity) {
                minEccentricity = eccentricity[j];
                centerVertex = j;
            }
        }
    }
    
    // 输出最终结果
    cout << "\n=== 医院选址 ===" << endl;
    if (centerVertex != -1) {
        cout << "推荐医院位置: 顶点 " << vertex[centerVertex] << endl;
        cout << "该位置的偏心度 (最大到达距离): " << minEccentricity << endl;
    } else {
        cout << "无法找到合适的医院位置 (图可能不连通或所有顶点不可达)" << endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif

    int vertexCount = 5;
    HospitalLocation hospital(vertexCount);
    hospital.initializeGraph(); // 使用图15-3数据
    
    hospital.Floyd();
    hospital.calculateEccentricity(); // 计算并直接输出结果
    
    return 0;
}
