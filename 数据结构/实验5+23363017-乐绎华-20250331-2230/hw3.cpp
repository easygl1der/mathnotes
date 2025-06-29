#include <iostream>
using namespace std;

// 链表节点结构
struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

class OrderedSet {
private:
    Node* head;

    // 释放链表内存
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // 构造函数
    OrderedSet() : head(nullptr) {}
    
    // 析构函数
    ~OrderedSet() {
        clear();
    }

    // 插入元素（保持有序） - O(n)
    void insert(int x) {
        Node* newNode = new Node(x);
        
        // 空链表或插入值小于头节点
        if (head == nullptr || x < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // 查找插入位置
        Node* current = head;
        while (current->next != nullptr && current->next->data < x) {
            current = current->next;
        }

        // 检查重复元素
        if (current->data == x || (current->next && current->next->data == x)) {
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // 判等运算 - O(n)
    bool equals(const OrderedSet& other) const {
        Node* p1 = head;
        Node* p2 = other.head;

        while (p1 && p2) {
            if (p1->data != p2->data) return false;
            p1 = p1->next;
            p2 = p2->next;
        }

        return p1 == nullptr && p2 == nullptr;
    }

    // 交集运算 - O(n)
    OrderedSet intersection(const OrderedSet& other) const {
        OrderedSet result;
        Node* p1 = head;
        Node* p2 = other.head;

        while (p1 && p2) {
            if (p1->data < p2->data) {
                p1 = p1->next;
            } else if (p2->data < p1->data) {
                p2 = p2->next;
            } else {
                result.insert(p1->data);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        return result;
    }

    // 并集运算 - O(n)
    OrderedSet union_with(const OrderedSet& other) const {
        OrderedSet result;
        Node* p1 = head;
        Node* p2 = other.head;

        while (p1 && p2) {
            if (p1->data < p2->data) {
                result.insert(p1->data);
                p1 = p1->next;
            } else if (p2->data < p1->data) {
                result.insert(p2->data);
                p2 = p2->next;
            } else {
                result.insert(p1->data);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        // 处理剩余元素
        while (p1) {
            result.insert(p1->data);
            p1 = p1->next;
        }
        while (p2) {
            result.insert(p2->data);
            p2 = p2->next;
        }

        return result;
    }

    // 差集运算 - O(n)
    OrderedSet difference(const OrderedSet& other) const {
        OrderedSet result;
        Node* p1 = head;
        Node* p2 = other.head;

        while (p1 && p2) {
            if (p1->data < p2->data) {
                result.insert(p1->data);
                p1 = p1->next;
            } else if (p2->data < p1->data) {
                p2 = p2->next;
            } else {
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        // 添加剩余元素
        while (p1) {
            result.insert(p1->data);
            p1 = p1->next;
        }

        return result;
    }

    // 打印集合
    void print() const {
        Node* current = head;
        cout << "{ ";
        while (current) {
            cout << current->data;
            if (current->next) cout << ", ";
            current = current->next;
        }
        cout << " }" << endl;
    }
};

// 测试代码
int main() {
    OrderedSet s1, s2;
    
    // 插入测试数据
    s1.insert(1);
    s1.insert(3);
    s1.insert(5);
    s1.insert(7);
    
    s2.insert(3);
    s2.insert(5);
    s2.insert(6);
    s2.insert(8);

    cout << "集合 s1: ";
    s1.print();
    cout << "集合 s2: ";
    s2.print();

    cout << "s1 和 s2 是否相等: " << (s1.equals(s2) ? "是" : "否") << endl;

    cout << "交集: ";
    s1.intersection(s2).print();

    cout << "并集: ";
    s1.union_with(s2).print();

    cout << "差集 (s1 - s2): ";
    s1.difference(s2).print();

    return 0;
}
