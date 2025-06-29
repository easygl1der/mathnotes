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

// 检查表达式中的括号是否匹配
bool checkBrackets(const string& expr) {
    LinkStack<char> stack;
    
    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        // 遇到左括号，入栈
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.Push(ch);
        }
        // 遇到右括号，检查是否匹配
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.Empty()) {
                return false;  // 右括号多于左括号
            }
            
            char top = stack.Pop();
            
            // 检查括号是否匹配
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;  // 括号不匹配
            }
        }
    }
    
    // 检查是否还有未匹配的左括号
    return stack.Empty();
}

int main() {
    string expr;
    cout << "Please enter an arithmetic expression: ";
    getline(cin, expr);
    
    if (checkBrackets(expr)) {
        cout << "Brackets match correctly!" << endl;
    } else {
        cout << "Brackets do not match correctly!" << endl;
    }
    
    return 0;
}
