#include<iostream>
#include<ctime>    // 添加时间头文件
#include<cstdlib>  // 添加随机数头文件
using namespace std;

// 建立类模板，实现将数组a[n]中所有元素循环左移k个位置
template<typename T>
class ArrayShift
{
	private:
		T *a;
		int k;
		int n;
	public:
        T* temp;
        
        ArrayShift(T arr[], int size, int shift) {  // 构造函数
            a = arr;
            n = size;
            k = shift;
            temp = new T[k];
        }
        
        void shift() {  // 成员函数
            for (int i = 0; i < k; i++) {
                temp[i] = a[i];
            }
            for (int i = 0; i < n-k; i++) {
                a[i] = a[i+k];
            }
            for (int i = n-k; i < n; i++) {
                a[i] = temp[i-(n-k)];
            }
        }
};


int main()
{
	srand(time(0));  // 设置随机数种子
	
	// 随机获取生成数组a 
    int n = 10;
    int arr[n];
    int k = 3;
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;  // 生成0-99的随机数
    }
    // 输出移动前的数组
    cout << "移动前的数组为：";
    for (int i = 0; i < n; i++)
    {
        cout   << arr[i] << " ";
    }
    cout << endl;

    ArrayShift<int> shift(arr, n, k);
    shift.shift();
    
    // 输出移动后的数组
    cout << "移动后的数组为：";
    for (int i = 0; i < n; i++)
    {
        cout  << arr[i] << " ";
    }
    cout << endl;
    
	return 0;
}
