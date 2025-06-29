#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 顺序查找算法，哨兵在高端
int Search(int r[], int n, int k) {
    int i = 0;
    r[n] = k; // 哨兵
    while (r[i] != k) {
        i++;
    }
    // 如果 i < n，说明在原数组中找到了；否则没找到
    return (i < n) ? i : -1;
}

int main() {
    int N;
    cout << "Enter N (>10000): ";
    cin >> N;
    if (N <= 10000) {
        cout << "N must be greater than 10000." << endl;
        return 1;
    }

    // 随机生成 N 个整数
    srand((unsigned)time(0));
    int* arr = new int[N + 1]; // 多开一个空间用于哨兵
    for (int i = 0; i < N; ++i) {
        arr[i] = rand();
    }

    int key;
    cout << "Enter the key to search: ";
    cin >> key;

    int result = Search(arr, N, key);
    if (result != -1) {
        cout << "Found at index: " << result << endl;
    } else {
        cout << "Not found." << endl;
    }

    delete[] arr;
    return 0;
}
