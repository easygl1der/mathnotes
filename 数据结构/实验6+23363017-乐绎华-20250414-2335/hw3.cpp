#include <iostream>
using namespace std;

const int StackSize = 100;  // 栈的最大容量
const int QueueSize = 100;  // 队列的最大容量

// 顺序栈类定义
template <typename DataType>
class SeqStack {
public:
    SeqStack();                  // 构造函数
    ~SeqStack();                 // 析构函数
    void Push(DataType x);       // 入栈操作
    DataType Pop();              // 出栈操作
    DataType GetTop();           // 获取栈顶元素
    int Empty();                 // 判断栈是否为空
    int GetSize();               // 获取栈中元素个数
private:
    DataType data[StackSize];    // 存放栈元素的数组
    int top;                     // 栈顶指针
};

// 循环队列类定义
template <typename DataType>
class CircularQueue {
public:
    CircularQueue();             // 构造函数
    ~CircularQueue();            // 析构函数
    void EnQueue(DataType x);    // 入队操作
    DataType DeQueue();          // 出队操作
    DataType GetFront();         // 获取队头元素
    int Empty();                 // 判断队列是否为空
private:
    DataType data[QueueSize];    // 存放队列元素的数组
    int front, rear;             // 队头和队尾指针
};

// 顺序栈的实现
template <typename DataType>
SeqStack<DataType>::SeqStack() {
    top = -1;
}

template <typename DataType>
SeqStack<DataType>::~SeqStack() {
}

template <typename DataType>
void SeqStack<DataType>::Push(DataType x) {
    if (top == StackSize - 1)
        throw "栈上溢";
    data[++top] = x;
}

template <typename DataType>
DataType SeqStack<DataType>::Pop() {
    if (top == -1)
        throw "栈下溢";
    return data[top--];
}

template <typename DataType>
DataType SeqStack<DataType>::GetTop() {
    if (top == -1)
        throw "栈为空";
    return data[top];
}

template <typename DataType>
int SeqStack<DataType>::Empty() {
    return top == -1;
}

template <typename DataType>
int SeqStack<DataType>::GetSize() {
    return top + 1;
}

// 循环队列的实现
template <typename DataType>
CircularQueue<DataType>::CircularQueue() {
    front = rear = 0;
}

template <typename DataType>
CircularQueue<DataType>::~CircularQueue() {
}

template <typename DataType>
void CircularQueue<DataType>::EnQueue(DataType x) {
    if ((rear + 1) % QueueSize == front)
        throw "队列上溢";
    data[rear] = x;
    rear = (rear + 1) % QueueSize;
}

template <typename DataType>
DataType CircularQueue<DataType>::DeQueue() {
    if (front == rear)
        throw "队列下溢";
    DataType x = data[front];
    front = (front + 1) % QueueSize;
    return x;
}

template <typename DataType>
DataType CircularQueue<DataType>::GetFront() {
    if (front == rear)
        throw "队列为空";
    return data[front];
}

template <typename DataType>
int CircularQueue<DataType>::Empty() {
    return front == rear;
}

// 重新排列栈中元素的函数
void rearrangeStack(SeqStack<int>& S) {
    int size = S.GetSize();
    if (size % 2 != 0) {
        cout << "栈中元素个数必须为偶数" << endl;
        return;
    }
    
    int n = size / 2;
    int* temp = new int[size];  // 创建临时数组存储栈中元素
    
    // 将栈中元素保存到临时数组
    for (int i = size - 1; i >= 0; i--) {
        temp[i] = S.Pop();
    }
    
    // 直接操作top指针，重新排列元素
    for (int i = 0; i < n; i++) {
        // 先放奇数位置的元素（从栈底算起的第1,3,5...个）
        S.Push(temp[2*i ]);
    }
    
    // 再放偶数位置的元素（从栈底算起的第2,4,6...个）
    for (int i = 0; i < n; i++) {
        S.Push(temp[2*i+1]);
    }
    
    delete[] temp;  // 释放临时数组
}

int main() {
    SeqStack<int> stack;
    int n;
    
    cout << "Please enter the value of n (stack has 2n elements): ";
    cin >> n;
    
    cout << "Please input " << 2*n << " elements (from bottom to top of stack):" << endl;
    for (int i = 1; i <= 2*n; i++) {
        int value;
        cin >> value;
        stack.Push(value);
    }
    
    cout << "Elements from top to bottom before rearrangement: ";
    SeqStack<int> tempStack;
    while (!stack.Empty()) {
        int value = stack.Pop();
        cout << value << " ";
        tempStack.Push(value);
    }
    cout << endl;
    
    // Restore original stack
    while (!tempStack.Empty()) {
        stack.Push(tempStack.Pop());
    }
    
    // Rearrange elements in the stack
    rearrangeStack(stack);
    
    cout << "Elements from top to bottom after rearrangement: ";
    while (!stack.Empty()) {
        cout << stack.Pop() << " ";
    }
    cout << endl;
    
    return 0;
}
