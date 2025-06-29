#include <iostream>
#include <vector>
#include <string>
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

class TSP_NearestNeighbor {
private:
    string cities[MaxSize];      // 城市名称数组
    int adjMatrix[MaxSize][MaxSize];  // 邻接矩阵，存储城市间距离
    int numCities;

public:
    TSP_NearestNeighbor(int n);
    void initializeGraph();     // 初始化图15-1的数据
    void displayAdjMatrix();    // 显示邻接矩阵
    void solve(int startCityIndex); // 执行最近邻点贪心算法
    void setCityName(int index, const string& name);
    string getCityName(int index) const;
};

TSP_NearestNeighbor::TSP_NearestNeighbor(int n) {
    numCities = n;
    // 初始化城市名称和邻接矩阵
    for (int i = 0; i < numCities; i++) {
        cities[i] = to_string(i + 1); // 默认城市名称为 1, 2, 3...
        for (int j = 0; j < numCities; j++) {
            if (i == j) {
                adjMatrix[i][j] = 0;
            } else {
                adjMatrix[i][j] = INF;
            }
        }
    }
}

void TSP_NearestNeighbor::setCityName(int index, const string& name) {
    if (index >= 0 && index < numCities) {
        cities[index] = name;
    }
}

string TSP_NearestNeighbor::getCityName(int index) const {
    if (index >= 0 && index < numCities) {
        return cities[index];
    }
    return "";
}

void TSP_NearestNeighbor::initializeGraph() {
    // 根据图15-1(a)的代价矩阵初始化图数据 (6个城市)
    // 城市索引: 0->1, 1->2, 2->3, 3->4, 4->5, 5->6
    // 我们这里用0-5代表城市1-6
    if (numCities != 6) {
        cout << "错误：此初始化函数仅适用于6个城市的情况，当前城市数为 " << numCities << endl;
        return;
    }

    int C[6][6] = {
        {INF, 3,   7,   3,   2,   6  },
        {3,   INF, 7,   INF, 2,   5  },
        {7,   7,   INF, 2,   INF, 3  },
        {3,   INF, 2,   INF, INF, 3  },
        {2,   2,   INF, INF, INF, 3  },
        {6,   5,   3,   3,   3,   INF}
    };

    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            adjMatrix[i][j] = C[i][j];
        }
    }
    cout << "已加载图15-1的示例数据（6个城市）" << endl;
}

void TSP_NearestNeighbor::displayAdjMatrix() {
    cout << "\n邻接矩阵 (城市间距离)：" << endl;
    cout << string(numCities * 8 + 10, '=') << endl;
    cout << setw(8) << "城市";
    for (int i = 0; i < numCities; i++) {
        cout << setw(8) << getCityName(i);
    }
    cout << endl;

    for (int i = 0; i < numCities; i++) {
        cout << setw(8) << getCityName(i);
        for (int j = 0; j < numCities; j++) {
            if (adjMatrix[i][j] == INF) {
                cout << setw(8) << "∞";
            } else {
                cout << setw(8) << adjMatrix[i][j];
            }
        }
        cout << endl;
    }
    cout << string(numCities * 8 + 10, '=') << endl;
}

void TSP_NearestNeighbor::solve(int startCityIndex) {
    if (startCityIndex < 0 || startCityIndex >= numCities) {
        cout << "错误：无效的起始城市索引。" << endl;
        return;
    }

    cout << "\n=== TSP 最近邻点贪心算法 ===" << endl;
    cout << "起始城市: " << getCityName(startCityIndex) << endl;
    cout << string(50, '-') << endl;

    vector<int> path;
    vector<bool> visited(numCities, false);
    int currentCity = startCityIndex;
    long long totalDistance = 0;

    path.push_back(currentCity);
    visited[currentCity] = true;
    int citiesVisited = 1;

    cout << "访问路径构建过程:" << endl;
    cout << "1. 从城市 " << getCityName(currentCity) << " 出发" << endl;

    while (citiesVisited < numCities) {
        int nearestCity = -1;
        int minDistance = INF;

        cout << "   当前在城市 " << getCityName(currentCity) << ". 查找下一个最近的未访问城市:" << endl;

        for (int nextCity = 0; nextCity < numCities; ++nextCity) {
            if (!visited[nextCity] && adjMatrix[currentCity][nextCity] < minDistance) {
                minDistance = adjMatrix[currentCity][nextCity];
                nearestCity = nextCity;
                cout << "     - 候选: " << getCityName(nextCity) << " (距离: " << minDistance << ")" << endl;
            }
        }

        if (nearestCity != -1) {
            cout << "   选择城市 " << getCityName(nearestCity) << " 作为下一个城市 (距离: " << minDistance << ")" << endl;
            totalDistance += minDistance;
            currentCity = nearestCity;
            path.push_back(currentCity);
            visited[currentCity] = true;
            citiesVisited++;
            cout << (citiesVisited +1) << ". 访问城市 " << getCityName(currentCity) << ". 总距离: " << totalDistance << endl;
        } else {
            // 如果找不到未访问的城市（图不连通或只剩一个城市）
            cout << "   错误：无法找到下一个可达的未访问城市。TSP路径无法完成。" << endl;
            return; // 提前终止
        }
    }

    // 返回起始城市
    if (adjMatrix[currentCity][startCityIndex] != INF) {
        cout << "   所有城市已访问。返回起始城市 " << getCityName(startCityIndex) 
             << " (距离: " << adjMatrix[currentCity][startCityIndex] << ")" << endl;
        totalDistance += adjMatrix[currentCity][startCityIndex];
        path.push_back(startCityIndex);
    } else {
        cout << "   错误：无法从最后一个城市返回起始城市。TSP路径无法完成。" << endl;
        return; // 提前终止
    }

    cout << string(50, '-') << endl;
    cout << "最终TSP路径: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << getCityName(path[i]);
        if (i < path.size() - 1) {
            cout << " → ";
        }
    }
    cout << endl;
    cout << "总距离: " << totalDistance << endl;
    cout << "==============================" << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif

    cout << "====================================" << endl;
    cout << "🌍 TSP 最近邻点贪心算法求解器 🌍" << endl;
    cout << "====================================" << endl;

    // 使用图15-1的数据 (6个城市)
    int num_cities = 6;
    TSP_NearestNeighbor tsp_solver(num_cities);
    tsp_solver.initializeGraph(); // 加载示例数据

    // 显示邻接矩阵
    tsp_solver.displayAdjMatrix();

    // 尝试从不同的起始城市求解
    // 图15-1中的示例是从城市1 (索引0)开始
    tsp_solver.solve(0); 
    
    // 你可以尝试其他起始城市，例如城市3 (索引2)
    // tsp_solver.solve(2);

    cout << "\n程序结束。" << endl;
    return 0;
}
