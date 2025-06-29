/*
 * 单链表的直接插入排序算法
 */
#include <iostream>
using namespace std;

// 定义单链表节点结构
struct Node 
{
    int data;       // 数据域
    Node* next;     // 指针域

    // 构造函数
    Node(int val = 0) : data(val), next(NULL) {}
};

class LinkedList 
{
private:
    Node* first;  // 头指针

public:
    // 构造函数
    LinkedList() : first(NULL) {}

    // 在链表头插入元素
    void insertFront(int val) 
    {
        Node* newNode = new Node(val);
        newNode->next = first;
        first = newNode;
    }

    // 打印链表
    void printList() 
    {
        Node* current = first;
        while (current != NULL) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // 直接插入排序
    void StraightSort() 
    {
        // 如果链表为空或只有一个元素，无需排序
        if (first == NULL || first->next == NULL) return;

        Node* pre = first;     // 已排序部分的最后一个节点
        Node* p = first->next; // 待插入的当前节点
        Node* q;               // 用于查找插入位置的指针

        while (p != NULL) 
        {
            q = first;
            // 在已排序部分找插入位置
            while (q != p && q->data < p->data) 
            {
                q = q->next;
            }

            // 如果找到的位置不是p本身，需要调整链表
            if (q != p) 
            {
                // 从已排序部分删除p
                pre->next = p->next;

                // 将p插入到q之前
                p->next = q;

                // 特殊情况：插入到表头
                if (q == first) 
                {
                    first = p;
                }
                else 
                {
                    // 找到q之前的节点
                    Node* temp = first;
                    while (temp->next != q) 
                    {
                        temp = temp->next;
                    }
                    temp->next = p;
                }

                // 更新p
                p = pre->next;
            }
            else 
            {
                // 不需要移动，继续下一个节点
                pre = p;
                p = p->next;
            }
        }
    }

    // 析构函数，释放内存
    ~LinkedList() 
    {
        while (first != NULL) 
        {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }
};

int main() 
{
    LinkedList list;

    // 插入测试数据（逆序，便于观察排序过程）
    int arr[] = {54, 38, 96, 15, 68, 82, 27, 41};
    for (int i = sizeof(arr)/sizeof(arr[0]) - 1; i >= 0; i--) 
    {
        list.insertFront(arr[i]);
    }

    cout << "排序前链表：";
    list.printList();

    // 执行直接插入排序
    list.StraightSort();

    cout << "排序后链表：";
    list.printList();

    return 0;
}
