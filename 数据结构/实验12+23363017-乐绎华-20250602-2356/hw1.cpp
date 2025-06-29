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

const int MaxSize = 20;  // 增大数组大小以容纳11个城市

template <class DataType>
class MGraph
{
public:
    MGraph(DataType cities[], int n);  // 从文件读取的构造函数
    ~MGraph() {};
    void Prim(int v);  // Prim算法构造最小生成树
    void readDataFromFile(const string& filename);  // 从文件读取数据
    void displayMatrix();  // 显示邻接矩阵

private:
    DataType vertex[MaxSize];     // 存放图中顶点的数组
    int edge[MaxSize][MaxSize];   // 存放图中边的数组  
    int vertexNum;                // 图的顶点数
    
    int MinEdge(int lowcost[], int n);  // 找最小边
};

template <class DataType>
MGraph<DataType>::MGraph(DataType cities[], int n)
{
    vertexNum = n;
    for (int i = 0; i < vertexNum; i++)
        vertex[i] = cities[i];
    
    // 初始化邻接矩阵
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            edge[i][j] = (i == j) ? 0 : INT_MAX;
}

template <class DataType>
void MGraph<DataType>::readDataFromFile(const string& filename)
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
        string cityName;
        ss >> cityName;  // 读取城市名称
        
        // 读取该行的距离数据
        for (int col = 0; col < vertexNum; col++) {
            string distance;
            if (ss >> distance) {
                if (distance == "0") {
                    edge[row][col] = 0;
                } else if (distance == "　" || distance.empty()) {
                    // 对于空值，我们需要从对称位置获取数据
                    edge[row][col] = INT_MAX;
                } else {
                    edge[row][col] = stoi(distance);
                }
            }
        }
        row++;
    }
    
    // 由于原始数据是上三角矩阵，我们需要补全下三角矩阵
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (edge[i][j] == INT_MAX && edge[j][i] != INT_MAX) {
                edge[i][j] = edge[j][i];
            }
        }
    }
    
    file.close();
}

template <class DataType>
void MGraph<DataType>::displayMatrix()
{
    cout << "\n大湾区城市距离矩阵：" << endl;
    cout << "==============================================================================" << endl;
    
    // 打印城市编号对应关系
    cout << "城市编号对应关系：" << endl;
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]" << vertex[i] << "  ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    if (vertexNum % 3 != 0) cout << endl;
    cout << "==============================================================================" << endl;
    
    // 打印表头
    cout << "编号\\编号\t";
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]\t";
    }
    cout << endl;
    
    // 打印邻接矩阵
    for (int i = 0; i < vertexNum; i++) {
        cout << "[" << i << "]\t\t";
        for (int j = 0; j < vertexNum; j++) {
            if (edge[i][j] == INT_MAX) {
                cout << "∞\t";
            } else if (edge[i][j] == 0) {
                cout << "0\t";
            } else {
                cout << edge[i][j] << "\t";  // 直接显示米数
            }
        }
        cout << endl;
    }
    cout << "==============================================================================" << endl;
    cout << "注：距离单位为米，0表示同一城市，∞表示无直接连接" << endl;
}

template <class DataType>
void MGraph<DataType>::Prim(int startVertex)
{
    int adjvex[MaxSize], lowcost[MaxSize];
    int totalCost = 0;  // 记录总成本
    
    cout << "\n使用Prim算法构造大湾区最小生成树：" << endl;
    cout << "起始城市：" << vertex[startVertex] << endl;
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
        
        cout << k << ". " << vertex[adjvex[j]] << " -- " << vertex[j] 
             << " (距离: " << lowcost[j] << " 米)" << endl;
        
        totalCost += lowcost[j];
        lowcost[j] = 0;  // 顶点j加入集合U
        
        // 调整辅助数组
        for (int i = 0; i < vertexNum; i++) {
            if (edge[j][i] != INT_MAX && edge[j][i] < lowcost[i]) {
                lowcost[i] = edge[j][i];
                adjvex[i] = j;
            }
        }
    }
    
    cout << "\n最小生成树构造完成！" << endl;
    cout << "总连接成本：" << totalCost << " 米" << endl;
    cout << "实现了大湾区" << vertexNum << "个城市的最小成本互联互通！" << endl;
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

int main()
{
#ifdef _WIN32
    // 设置控制台代码页为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // 设置本地化
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif

    cout << "=== 大湾区城市互联互通最小生成树构造 ===" << endl;
    
    // 大湾区11个城市
    string cities[] = {"肇庆市", "佛山市", "广州市", "东莞市", "惠州市", 
                       "江门市", "中山市", "深圳市", "澳门", "香港", "珠海市"};
    
    int cityCount = 11;
    
    // 创建图对象
    MGraph<string> bayAreaGraph(cities, cityCount);
    
    // 从文件读取数据
    cout << "\n正在从文件读取大湾区连接数据..." << endl;
    bayAreaGraph.readDataFromFile("大湾区连接图数据.txt");
    
    // 显示邻接矩阵
    bayAreaGraph.displayMatrix();
    
    // 使用Prim算法构造最小生成树
    // 从广州市开始构造（索引为2）
    bayAreaGraph.Prim(2);
    
    cout << "\n分析结果：" << endl;
    cout << "通过最小生成树，我们用最少的基础设施投资实现了大湾区所有城市的互联互通。" << endl;
    cout << "这种连接方案能够以最小的总距离（成本）连接所有11个城市。" << endl;
    
    return 0;
}
