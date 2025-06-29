/*
2.建立一个递增单链表，增加函数
（1）插人元素值为×的结点，插入后单链表仍然有序递增。
(2)求单链表实际长度。
(3)删除单链表中数据域相同的多余结点。
(4)删除大于P且小于Q的所有元素，并释放被删结点的存储空间。
*/
#include <iostream>
using namespace std;

template <typename DataType>
struct Node
{
    DataType data;
    Node<DataType> *next;
};

template <typename DataType>
class SortedLinkList
{
public:
    SortedLinkList();
    ~SortedLinkList();
    void Insert(DataType x);
    int Length();
    void RemoveDuplicates();
    void DeleteBetween(DataType p, DataType q);
    void PrintList();
private:
    Node<DataType> *first;
};

template <typename DataType>
SortedLinkList<DataType> :: SortedLinkList()
{
    first = new Node<DataType>;
    first->next = NULL;
}   

template <typename DataType>
SortedLinkList<DataType> :: ~SortedLinkList()
{
    Node<DataType> *p = first;
    while (first != NULL)
    {   
        first = first->next;
        delete p;
        p = first;
    }
}

template <typename DataType>
void SortedLinkList<DataType>::Insert(DataType x)
{
    Node<DataType> *p = first;
    while (p->next != NULL && p->next->data < x)
    {
        p = p->next;
    }
    Node<DataType> *s = new Node<DataType>;
    s->data = x;
    s->next = p->next;
    p->next = s;
}

template <typename DataType>
int SortedLinkList<DataType>::Length()
{
    int count = 0;
    Node<DataType> *p = first->next;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

template <typename DataType>
void SortedLinkList<DataType>::RemoveDuplicates()
{
    if (first->next == NULL || first->next->next == NULL) return;
    
    Node<DataType> *p = first->next;
    while (p != NULL && p->next != NULL)
    {
        if (p->data == p->next->data)
        {
            Node<DataType> *temp = p->next;
            p->next = p->next->next;
            delete temp;
        } else {
            p = p->next;
        }
    }
}

template <typename DataType>
void SortedLinkList<DataType>::DeleteBetween(DataType p, DataType q)
{
    Node<DataType> *pre = first;
    Node<DataType> *cur = first->next;
    
    while (cur != NULL)
    {
        if (cur->data > p && cur->data < q)
        {
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
}

template <typename DataType>
void SortedLinkList<DataType>::PrintList()
{
    Node<DataType> *p = first->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    SortedLinkList<int> list;
    
    cout << "插入元素：3, 1, 4, 1, 5, 9, 2, 6" << endl;
    list.Insert(3);
    list.Insert(1);
    list.Insert(4);
    list.Insert(1);
    list.Insert(5);
    list.Insert(9);
    list.Insert(2);
    list.Insert(6);
    
    cout << "原始链表：";
    list.PrintList();
    
    cout << "链表长度：" << list.Length() << endl;
    
    cout << "删除重复节点后：";
    list.RemoveDuplicates();
    list.PrintList();
    
    cout << "删除(2,6)之间的元素后：";
    list.DeleteBetween(2, 6);
    list.PrintList();
    
    return 0;
}



