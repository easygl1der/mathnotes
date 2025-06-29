#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


// 什么是欧拉回路问题?对于一个矩阵，如果矩阵中每个顶点的度为偶数，则存在欧拉回路
// 什么是矩阵的顶点的度数?矩阵的顶点的度数是指矩阵中每个顶点连接的边数
// 举个例子，对于一个3x3的矩阵，如果矩阵中每个顶点的度为偶数，则存在欧拉回路


using namespace std;

const int MaxSize = 4;

class EulerCircuit{
public:
	EulerCircuit(int a[][MaxSize], int n);     //构造函数
    ~EulerCircuit( ){ }                        //析构函数为空
    int oddVertexNum( );        	          //求图中度为奇数的顶点个数
private:
	int mat[MaxSize][MaxSize];	           	 //二维数组存储图
    int vertexNum;	         	              //顶点个数
};

EulerCircuit :: EulerCircuit(int a[][MaxSize], int n)
{
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = a[i][j];
    vertexNum = n;
}
int EulerCircuit :: oddVertexNum( ) 
{
    int count = 0, i, j, degree;		
    for (i = 0; i < vertexNum; i++) 		// 依次累加每一行元素
    {
    	degree = 0;				        	// 记录通过顶点i的边数
      	for (j = 0; j < vertexNum; j++) 
        	degree = degree + mat[i][j];
      	if (degree % 2 != 0)	 
		  	count++;
    }
    return count;		
}

int main() {
    ifstream inFile("./data.txt");
    if (!inFile) {
        cout << "无法打开文件 data.txt" << endl;
        return 1;
    }

    vector<vector<int>> a;
    int value;
    string line;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        vector<int> row;
        istringstream iss(line);
        
        while (iss >> value) {
            row.push_back(value);
        }
        
        if (!row.empty()) {
            a.push_back(row);
        }
    }

    inFile.close();

    // 将vector转换为二维数组
    int mat[MaxSize][MaxSize];
    for(size_t i = 0; i < a.size(); i++)
        for(size_t j = 0; j < a[i].size(); j++)
            mat[i][j] = a[i][j];
            
    // 这里的4表示图中顶点的个数，对应MaxSize常量
    // 如果需要动态确定顶点数量，可以使用a.size()
    EulerCircuit G(mat, 4);
	int num = G.oddVertexNum( );          //调用函数得到通奇数桥的顶点个数
    if (num >= 2)                         //两个以上的顶点通奇数桥
      	cout << num << "个地方通奇数桥，不存在欧拉回路" << endl; 
    else                                 //没有顶点通奇数桥 
	  	cout << "存在欧拉回路" << endl;       

    return 0;
}
