/*
 * 折半插入排序算法
 * 通过折半查找来确定插入位置，减少比较次数
 */
#include <iostream>
using namespace std;

// 折半插入排序
void BinaryInsertSort(int r[], int n)
{
    // 从第2个元素开始，第1个元素默认已排序
    for (int i = 1; i < n; i++)
    {
        // 保存当前待插入的元素
        int temp = r[i];
        
        // 折半查找插入位置
        int low = 0, high = i - 1;
        int mid;
        
        // 折半查找
        while (low <= high)
        {
            mid = (low + high) / 2;
            
            // 如果temp小于mid位置的元素，在左半区查找
            if (temp < r[mid])
                high = mid - 1;
            // 如果temp大于等于mid位置的元素，在右半区查找
            else
                low = mid + 1;
        }
        
        // low即为插入位置
        // 将low之后i-1位置的元素后移
        for (int j = i - 1; j >= low; j--)
        {
            r[j + 1] = r[j];
        }
        
        // 插入元素
        r[low] = temp;
    }
}

// 打印数组
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    // 测试数据
    int arr[] = {54, 38, 96, 15, 68, 82, 27, 41};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前数组：";
    printArray(arr, n);

    // 执行折半插入排序
    BinaryInsertSort(arr, n);

    cout << "排序后数组：";
    printArray(arr, n);

    return 0;
}
