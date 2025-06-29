/*
3.算法设计
（1）已知顺序表L中的元素递增有序排列，设计算法将元素x插人到表L中并保持
表L仍递增有序。
（2）在顺序表中删除所有元素值为x的元素，要求空间复杂度为0（1）
（3）试分别以顺序表和单链表作存储结构，各编写一个实现线性表就地逆置的算法。
（4）设计算法判断非空单链表是否递增有序。
（5）给定一个带头结点的单链表，设计算法按递增次序输出单链表中各结点的数据
元素，并释放结点所占的存储空间（要求：不允许使用数组作辅助空间）。
（6）设单链表以非递减有序排列，设计算法实现在单链表中删去值相同的多余结点。
（7）已知单链表中各结点的元素值为整型且递增有序，设计算法删除链表中大于
mink且于maxk的所有元素，并释放被删结点的存储空间。
*/

#include <iostream>
using namespace std;

// 顺序表类
template <typename DataType>
class SeqList {
public:
    SeqList(int size = 100) {
        maxSize = size;
        length = 0;
        data = new DataType[maxSize];
    }
    ~SeqList() {
        delete[] data;
    }
    
    // (1) 在递增有序顺序表中插入元素x
    void InsertOrdered(DataType x) {
        if (length >= maxSize) throw "上溢";
        int i;
        // 找到插入位置
        for (i = 0; i < length && data[i] <= x; i++);
        // 将元素后移
        for (int j = length; j > i; j--) {
            data[j] = data[j-1];
        }
        data[i] = x;
        length++;
    }
    
    // (2) 删除所有值为x的元素，空间复杂度O(1)
    void DeleteAllX(DataType x) {
        int k = 0;  // k记录不等于x的元素个数
        for (int i = 0; i < length; i++) {
            if (data[i] != x) {
                data[k] = data[i];
                k++;
            }
        }
        length = k;
    }
    
    // (3) 顺序表就地逆置
    void Reverse() {
        for (int i = 0; i < length/2; i++) {
            DataType temp = data[i];
            data[i] = data[length-1-i];
            data[length-1-i] = temp;
        }
    }
    
    void PrintList() {
        for (int i = 0; i < length; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
private:
    DataType *data;
    int maxSize;
    int length;
};

// 单链表类
template <typename DataType>
struct Node {
    DataType data;
    Node<DataType> *next;
};

template <typename DataType>
class LinkList {
public:
    LinkList() {
        first = new Node<DataType>;
        first->next = NULL;
    }
    ~LinkList() {
        Node<DataType> *p = first;
        while (first != NULL) {
            first = first->next;
            delete p;
            p = first;
        }
    }
    
    // 插入元素
    void Insert(DataType x) {
        Node<DataType> *s = new Node<DataType>;
        s->data = x;
        s->next = first->next;
        first->next = s;
    }
    
    // (3) 单链表就地逆置
    void Reverse() {
        Node<DataType> *p = first->next;
        first->next = NULL;
        Node<DataType> *q;
        while (p != NULL) {
            q = p->next;
            p->next = first->next;
            first->next = p;
            p = q;
        }
    }
    
    // (4) 判断是否递增有序
    bool IsIncreasing() {
        if (first->next == NULL) return true;
        Node<DataType> *p = first->next;
        while (p->next != NULL) {
            if (p->data > p->next->data) return false;
            p = p->next;
        }
        return true;
    }
    
    // (5) 按递增次序输出并释放空间
    void PrintAndFree() {
        while (first->next != NULL) {
            // 找到最小值节点
            Node<DataType> *minPrev = first;
            Node<DataType> *p = first->next;
            Node<DataType> *minNode = p;
            
            while (p->next != NULL) {
                if (p->next->data < minNode->data) {
                    minPrev = p;
                    minNode = p->next;
                }
                p = p->next;
            }
            
            // 输出并删除最小值节点
            cout << minNode->data << " ";
            minPrev->next = minNode->next;
            delete minNode;
        }
        cout << endl;
    }
    
    // (6) 删除值相同的多余节点
    void RemoveDuplicates() {
        if (first->next == NULL || first->next->next == NULL) return;
        Node<DataType> *p = first->next;
        while (p != NULL && p->next != NULL) {
            if (p->data == p->next->data) {
                Node<DataType> *temp = p->next;
                p->next = p->next->next;
                delete temp;
            } else {
                p = p->next;
            }
        }
    }
    
    // (7) 删除大于mink且小于maxk的元素
    void DeleteRange(DataType mink, DataType maxk) {
        Node<DataType> *pre = first;
        Node<DataType> *cur = first->next;
        
        while (cur != NULL) {
            if (cur->data > mink && cur->data < maxk) {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
            } else {
                pre = cur;
                cur = cur->next;
            }
        }
    }
    
    void PrintList() {
        Node<DataType> *p = first->next;
        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    
private:
    Node<DataType> *first;
};

int main() {
    // 测试顺序表算法
    cout << "顺序表测试：" << endl;
    SeqList<int> seq(10);
    seq.InsertOrdered(3);
    seq.InsertOrdered(1);
    seq.InsertOrdered(4);
    seq.InsertOrdered(2);
    cout << "原始顺序表：";
    seq.PrintList();
    
    seq.DeleteAllX(2);
    cout << "删除所有2后：";
    seq.PrintList();
    
    seq.Reverse();
    cout << "逆置后：";
    seq.PrintList();
    
    // 测试单链表算法
    cout << "\n单链表测试：" << endl;
    LinkList<int> list;
    list.Insert(3);
    list.Insert(1);
    list.Insert(4);
    list.Insert(2);
    cout << "原始链表：";
    list.PrintList();
    
    cout << "是否递增：" << (list.IsIncreasing() ? "是" : "否") << endl;
    
    list.Reverse();
    cout << "逆置后：";
    list.PrintList();
    
    cout << "按递增次序输出并释放：";
    list.PrintAndFree();
    
    return 0;
}