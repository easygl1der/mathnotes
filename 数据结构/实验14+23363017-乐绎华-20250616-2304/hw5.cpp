/*
 * 线性探测散列表的懒惰删除算法
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 定义散列表的状态
const int EMPTY = 0;   // 空单元
const int ACTIVE = 1;  // 活跃单元
const int DELETED = 2; // 已删除单元

class HashTable 
{
private:
    // 散列表的元素结构
    struct HashEntry 
    {
        int data;     // 存储的数据
        int status;   // 单元状态

        HashEntry() : data(0), status(EMPTY) {}
    };

    vector<HashEntry> ht;  // 散列表
    int tableSize;         // 表大小
    int currentSize;       // 当前元素个数

    // 散列函数
    int hash(int key) 
    {
        return key % tableSize;
    }

public:
    // 构造函数
    HashTable(int size = 101) : tableSize(size), currentSize(0) 
    {
        ht.resize(tableSize);
    }

    // 插入元素
    bool insert(int x) 
    {
        // 如果表已满，返回false
        if (currentSize >= tableSize / 2) return false;

        int pos = hash(x);
        int i = 0;

        // 线性探测寻找插入位置
        while (i < tableSize) 
        {
            int j = (pos + i) % tableSize;
            
            // 找到空单元或已删除单元
            if (ht[j].status == EMPTY || ht[j].status == DELETED) 
            {
                ht[j].data = x;
                ht[j].status = ACTIVE;
                currentSize++;
                return true;
            }
            
            // 如果元素已存在
            if (ht[j].status == ACTIVE && ht[j].data == x) 
            {
                return false;
            }
            
            i++;
        }

        return false;
    }

    // 懒惰删除
    bool lazyDelete(int x) 
    {
        int pos = hash(x);
        int i = 0;

        // 线性探测查找元素
        while (i < tableSize) 
        {
            int j = (pos + i) % tableSize;
            
            // 遇到空单元，说明元素不存在
            if (ht[j].status == EMPTY) 
            {
                return false;
            }
            
            // 找到目标元素
            if (ht[j].status == ACTIVE && ht[j].data == x) 
            {
                // 懒惰删除：只改变状态，不实际删除
                ht[j].status = DELETED;
                currentSize--;
                return true;
            }
            
            i++;
        }

        return false;
    }

    // 查找元素
    bool search(int x) 
    {
        int pos = hash(x);
        int i = 0;

        // 线性探测查找元素
        while (i < tableSize) 
        {
            int j = (pos + i) % tableSize;
            
            // 遇到空单元，说明元素不存在
            if (ht[j].status == EMPTY) 
            {
                return false;
            }
            
            // 找到目标元素（必须是活跃状态）
            if (ht[j].status == ACTIVE && ht[j].data == x) 
            {
                return true;
            }
            
            i++;
        }

        return false;
    }

    // 打印散列表
    void printHashTable() 
    {
        cout << "散列表内容：" << endl;
        for (int i = 0; i < tableSize; i++) 
        {
            cout << "位置 " << i << ": ";
            if (ht[i].status == ACTIVE) 
            {
                cout << ht[i].data << " (活跃)" << endl;
            }
            else if (ht[i].status == DELETED) 
            {
                cout << ht[i].data << " (已删除)" << endl;
            }
            else 
            {
                cout << "空" << endl;
            }
        }
    }
};

int main() 
{
    HashTable hashTable(11);  // 创建大小为11的散列表

    // 插入元素
    int insertElements[] = {23, 34, 45, 12, 56, 67};
    for (int x : insertElements) 
    {
        if (hashTable.insert(x)) 
        {
            cout << "插入 " << x << " 成功" << endl;
        }
        else 
        {
            cout << "插入 " << x << " 失败" << endl;
        }
    }

    cout << "\n初始散列表：" << endl;
    hashTable.printHashTable();

    // 演示懒惰删除
    int deleteElement = 34;
    if (hashTable.lazyDelete(deleteElement)) 
    {
        cout << "\n删除 " << deleteElement << " 成功" << endl;
    }
    else 
    {
        cout << "\n删除 " << deleteElement << " 失败" << endl;
    }

    cout << "\n删除后散列表：" << endl;
    hashTable.printHashTable();

    // 查找元素
    int searchElement = 34;
    if (hashTable.search(searchElement)) 
    {
        cout << "\n查找 " << searchElement << " 失败（仍被标记为已删除）" << endl;
    }
    else 
    {
        cout << "\n查找 " << searchElement << " 成功（元素不可用）" << endl;
    }

    return 0;
}
