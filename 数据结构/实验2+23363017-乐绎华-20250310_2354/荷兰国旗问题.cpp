// 4.（选做）荷兰国旗问题。要求重新排列一个由字符R，W，B（R代表红色，W代表白色，B代表蓝色，这都是荷兰国旗的颜色）构成的数组，使得所有的R都排在最前面，W排在其次，B排在最后。设计时间性能O（n）的算法。

#include<iostream>
#include <ctime>    // 为了使用 time()
#include <cstdlib>  // 为了使用 rand() 和 srand()
using namespace std;

// 扫描三遍数组，第一遍将R放在最前面，第二遍将W放在R后面，第三遍将B放在W后面

template<typename T>
class DutchFlag
{
    private:
        T *a;
        int n;
    public:
        T *temp;
        
        DutchFlag(T arr[], int size) {  // 构造函数
            a = arr;
            n = size;
            temp = new T[n];
        }
        
        void sort() {  // 成员函数
            // 第一遍将R放在最前面
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 'R')
                {
                    temp[j] = a[i];
                    j++;
                }
            }
            // 第二遍将W放在R后面
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 'W')
                {
                    temp[j] = a[i];
                    j++;
                }
            };
            // 第三遍将B放在W后面
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 'B')
                {
                    temp[j] = a[i];
                    j++;
                }
            }
            for (int i = 0; i < n; i++)
            {
                a[i] = temp[i];
            }
        }
};



int main() {
    srand(time(0));  // 添加随机数种子
    
    int n = 100;
    char *arr = new char[n + 1];  // 分配内存，+1用于存放字符串结束符
    char letters[] = {'R', 'W', 'B'};
    
    // 生成随机字符串
    for (int i = 0; i < n; i++) {
        arr[i] = letters[rand() % 3];
    }
    arr[n] = '\0';  // 添加字符串结束符
    
    cout << "排序前：" << arr << endl;
    
    DutchFlag<char> flag(arr, n);
    flag.sort();
    
    cout << "排序后：" << arr << endl;
    
    delete[] arr;  // 释放内存
    return 0;
}
