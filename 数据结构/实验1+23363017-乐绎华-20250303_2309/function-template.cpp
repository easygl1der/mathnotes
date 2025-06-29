/*
>1.定义三角形类，给定三边长，计算周长和面积
>2.用类模板，编写一个数组类并测试相应功能
>3.用函数模板，用选择排序法和指针操作，实现降序排序。
 */

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
void selectionSort(T* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        T* maxPtr = arr + i;
        for (size_t j = i + 1; j < size; ++j) {
            if (*(arr + j) > *maxPtr) {
                maxPtr = arr + j;
            }
        }
        if (maxPtr != arr + i) {
            T temp = *maxPtr;
            *maxPtr = *(arr + i);
            *(arr + i) = temp;
        }
    }
}

template <typename T>
void printArray(T* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec;
    string input;

    cout << "请输入数组元素: ";
    getline(cin, input); // 读取整行输入

    stringstream ss(input); // 用字符串流处理输入
    int num;
    while (ss >> num) {
        vec.push_back(num);
    }

    size_t size = vec.size();
    int* arr = new int[size];

    for (size_t i = 0; i < size; ++i) {
        arr[i] = vec[i];
    }

    cout << "排序前的数组: ";
    printArray(arr, size);

    selectionSort(arr, size);

    cout << "降序排序后的数组: ";
    printArray(arr, size);

    delete[] arr;
    return 0;
}