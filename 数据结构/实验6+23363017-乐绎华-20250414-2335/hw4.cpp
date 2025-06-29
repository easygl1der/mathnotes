#include <iostream>
using namespace std;

const int QueueSize = 100;  // 队列的最大容量

// 带标志位的循环队列类定义
template <typename DataType>
class CircularQueue {
public:
    CircularQueue();             // 构造函数
    ~CircularQueue();            // 析构函数
    void EnQueue(DataType x);    // 入队操作
    DataType DeQueue();          // 出队操作
    DataType GetFront();         // 获取队头元素
    int Empty();                 // 判断队列是否为空
    int Full();                  // 判断队列是否已满
private:
    DataType data[QueueSize];    // 存放队列元素的数组
    int front, rear;             // 队头和队尾指针
    int flag;                    // 标志位，0表示队空，1表示队满（当front=rear时）
};

// 循环队列的实现
template <typename DataType>
CircularQueue<DataType>::CircularQueue() {
    front = rear = 0;
    flag = 0;  // 初始为空队列
}

template <typename DataType>
CircularQueue<DataType>::~CircularQueue() {
}

template <typename DataType>
void CircularQueue<DataType>::EnQueue(DataType x) {
    if (front == rear && flag == 1)
        throw "队列上溢";
    
    data[rear] = x;
    rear = (rear + 1) % QueueSize;
    
    if (front == rear)  // 入队后如果front=rear，说明队列已满
        flag = 1;
}

template <typename DataType>
DataType CircularQueue<DataType>::DeQueue() {
    if (front == rear && flag == 0)
        throw "队列下溢";
    
    DataType x = data[front];
    front = (front + 1) % QueueSize;
    
    if (front == rear)  // 出队后如果front=rear，说明队列已空
        flag = 0;
    
    return x;
}

template <typename DataType>
DataType CircularQueue<DataType>::GetFront() {
    if (front == rear && flag == 0)
        throw "队列为空";
    
    return data[front];
}

template <typename DataType>
int CircularQueue<DataType>::Empty() {
    return (front == rear && flag == 0);
}

template <typename DataType>
int CircularQueue<DataType>::Full() {
    return (front == rear && flag == 1);
}

int main() {
    CircularQueue<int> queue;
    int choice, value;
    
    cout << "Circular Queue with Flag Demonstration" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. View Front Element" << endl;
    cout << "4. Check if Queue is Empty" << endl;
    cout << "5. Check if Queue is Full" << endl;
    cout << "0. Exit" << endl;
    
    while (true) {
        cout << "\nPlease select an operation: ";
        cin >> choice;
        
        switch (choice) {
            case 0:
                cout << "Program exited" << endl;
                return 0;
            case 1:
                cout << "Enter element to enqueue: ";
                cin >> value;
                try {
                    queue.EnQueue(value);
                    cout << "Enqueue successful: " << value << endl;
                } catch (const char* msg) {
                    cout << "Error: " << msg << endl;
                }
                break;
            case 2:
                try {
                    value = queue.DeQueue();
                    cout << "Dequeued element: " << value << endl;
                } catch (const char* msg) {
                    cout << "Error: " << msg << endl;
                }
                break;
            case 3:
                try {
                    value = queue.GetFront();
                    cout << "Front element: " << value << endl;
                } catch (const char* msg) {
                    cout << "Error: " << msg << endl;
                }
                break;
            case 4:
                if (queue.Empty())
                    cout << "Queue is empty" << endl;
                else
                    cout << "Queue is not empty" << endl;
                break;
            case 5:
                if (queue.Full())
                    cout << "Queue is full" << endl;
                else
                    cout << "Queue is not full" << endl;
                break;
            default:
                cout << "Invalid choice, please try again" << endl;
        }
    }
    
    return 0;
}
