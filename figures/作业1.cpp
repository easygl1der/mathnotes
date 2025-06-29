#include <iostream>
using namespace std;

template <typename DataType>
struct Node
{
    DataType data;               //数据域
    Node<DataType> *next;       //指针域
};

template <typename DataType>
class LinkList
{
public:
    LinkList();                      //无参构造函数，建立只有头结点的空链表
    LinkList(DataType a[], int n);   //有参构造函数，建立有n个元素的单链表
    ~LinkList();                     //析构函数
    void PrintList();                //遍历操作，按序号依次输出各元素
    
    // 新增功能
    bool IsIncreasing();             //判断是否为递增序列
    void Reverse();                  //就地逆置
    LinkList<DataType> Clone();      //克隆复制单链表
    void PrintIncreasing();          //按递增次序输出

private:
    Node<DataType> *first;          //单链表的头指针
};

// 构造函数
template <typename DataType>
LinkList<DataType>::LinkList()
{
    first = new Node<DataType>;
    first->next = NULL;
}

// 有参构造函数
template <typename DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
    first = new Node<DataType>;
    first->next = NULL;
    Node<DataType> *r = first;
    for (int i = 0; i < n; i++)
    {
        Node<DataType> *s = new Node<DataType>;
        s->data = a[i];
        s->next = NULL;
        r->next = s;
        r = s;
    }
}

// 析构函数
template <typename DataType>
LinkList<DataType>::~LinkList()
{
    Node<DataType> *p = first;
    while (first != NULL)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

// 打印链表
template <typename DataType>
void LinkList<DataType>::PrintList()
{
    Node<DataType> *p = first->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 判断是否为递增序列
template <typename DataType>
bool LinkList<DataType>::IsIncreasing()
{
    if (first->next == NULL) return true;
    Node<DataType> *p = first->next;
    while (p->next != NULL)
    {
        if (p->data > p->next->data)
            return false;
        p = p->next;
    }
    return true;
}

// 就地逆置
template <typename DataType>
void LinkList<DataType>::Reverse()
{
    Node<DataType> *p = first->next;
    first->next = NULL;
    Node<DataType> *q;
    while (p != NULL)
    {
        q = p->next;
        p->next = first->next;
        first->next = p;
        p = q;
    }
}

// 克隆复制单链表
template <typename DataType>
LinkList<DataType> LinkList<DataType>::Clone()
{
    LinkList<DataType> newList;
    Node<DataType> *p = first->next;
    Node<DataType> *r = newList.first;
    
    while (p != NULL)
    {
        Node<DataType> *s = new Node<DataType>;
        s->data = p->data;
        s->next = NULL;
        r->next = s;
        r = s;
        p = p->next;
    }
    return newList;
}

// 按递增次序输出
template <typename DataType>
void LinkList<DataType>::PrintIncreasing()
{
    // 创建临时数组存储数据
    int len = 0;
    Node<DataType> *p = first->next;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    
    DataType *arr = new DataType[len];
    p = first->next;
    
    // 复制数据到数组
    for (int i = 0; i < len; i++)
    {
        arr[i] = p->data;
        p = p->next;
    }
    
    // 冒泡排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                DataType temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    // 输出排序后的数据
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
}

int main()
{
    // 测试代码
    int arr[] = {5, 2, 8, 1, 9};
    LinkList<int> list(arr, 5);
    
    cout << "原始链表：";
    list.PrintList();
    
    cout << "是否递增：" << (list.IsIncreasing() ? "是" : "否") << endl;
    
    cout << "逆置后：";
    list.Reverse();
    list.PrintList();
    
    cout << "克隆链表：";
    LinkList<int> clonedList = list.Clone();
    clonedList.PrintList();
    
    cout << "按递增次序输出：";
    list.PrintIncreasing();
    
    return 0;
}
