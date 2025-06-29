#include <iostream>
#include <string>
using namespace std;

// 定义链栈节点结构
template <typename DataType>
struct Node {
    DataType data;
    Node<DataType> *next;
};

// 定义链栈类
template <typename DataType>
class LinkStack {
public:
    LinkStack();                     // 构造函数
    ~LinkStack();                    // 析构函数
    void Push(DataType x);           // 入栈操作
    DataType Pop();                  // 出栈操作
    DataType GetTop();               // 获取栈顶元素
    int Empty();                     // 判断栈是否为空
private:
    Node<DataType> *top;             // 栈顶指针
};

// 构造函数
template <typename DataType>
LinkStack<DataType>::LinkStack() {
    top = NULL;
}

// 析构函数
template <typename DataType>
LinkStack<DataType>::~LinkStack() {
    Node<DataType> *q = NULL;
    while (top != NULL) {
        q = top;
        top = top->next;
        delete q;
    }
}

// 入栈操作
template <typename DataType>
void LinkStack<DataType>::Push(DataType x) {
    Node<DataType> *s = new Node<DataType>;
    s->data = x;
    s->next = top;
    top = s;
}

// 出栈操作
template <typename DataType>
DataType LinkStack<DataType>::Pop() {
    if (Empty())
        throw "栈为空，无法出栈";
    
    DataType x = top->data;
    Node<DataType> *p = top;
    top = top->next;
    delete p;
    return x;
}

// 获取栈顶元素
template <typename DataType>
DataType LinkStack<DataType>::GetTop() {
    if (Empty())
        throw "栈为空，无法获取栈顶元素";
    
    return top->data;
}

// 判断栈是否为空
template <typename DataType>
int LinkStack<DataType>::Empty() {
    return top == NULL;
}

// 十进制转换为指定进制
string decimalToBase(int decimal, int base) {
    if (base < 2 || base > 9) {
        return "进制范围应为2-9";
    }
    
    if (decimal == 0) {
        return "0";
    }
    
    LinkStack<int> stack;
    string result = "";
    
    // 处理负数
    bool isNegative = false;
    if (decimal < 0) {
        isNegative = true;
        decimal = -decimal;
    }
    
    // 进行进制转换
    while (decimal > 0) {
        stack.Push(decimal % base);
        decimal /= base;
    }
    
    // 从栈中弹出结果
    while (!stack.Empty()) {
        result += to_string(stack.Pop());
    }
    
    // 如果是负数，添加负号
    if (isNegative) {
        result = "-" + result;
    }
    
    return result;
}

int main() {
    int decimal, base;
    
    cout << "Please enter a decimal integer: ";
    cin >> decimal;
    
    cout << "Please enter the target base (2-9): ";
    cin >> base;
    
    if (base < 2 || base > 9) {
        cout << "Error: base must be between 2 and 9" << endl;
        return 1;
    }
    
    string result = decimalToBase(decimal, base);
    cout << "Conversion result: " << result << endl;
    
    return 0;
}
