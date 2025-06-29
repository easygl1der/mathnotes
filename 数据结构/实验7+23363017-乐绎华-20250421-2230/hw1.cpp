#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// 判断运算符优先级
int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else
        return 0;
}

// 执行运算
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// 1. 中缀表达式求值
double evaluateInfix(string expr) {
    stack<double> operands;
    stack<char> operators;
    
    for (int i = 0; i < expr.length(); i++) {
        // 跳过空格
        if (expr[i] == ' ')
            continue;
        
        // 处理数字
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--; // 回退一位，因为循环会自增
            operands.push(stod(num));
        }
        // 处理左括号
        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        // 处理右括号
        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                
                operands.push(calculate(a, b, op));
            }
            
            if (!operators.empty())
                operators.pop(); // 弹出左括号
        }
        // 处理运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (!operators.empty() && operators.top() != '(' && 
                   priority(operators.top()) >= priority(expr[i])) {
                char op = operators.top();
                operators.pop();
                
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                
                operands.push(calculate(a, b, op));
            }
            operators.push(expr[i]);
        }
    }
    
    // 处理剩余的运算符
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        
        double b = operands.top();
        operands.pop();
        double a = operands.top();
        operands.pop();
        
        operands.push(calculate(a, b, op));
    }
    
    return operands.top();
}

// 2. 中缀表达式转为后缀表达式
string infixToPostfix(string expr) {
    stack<char> operators;
    string postfix = "";
    
    for (int i = 0; i < expr.length(); i++) {
        // 跳过空格
        if (expr[i] == ' ')
            continue;
        
        // 处理数字
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--; // 回退一位，因为循环会自增
            postfix += num + " ";
        }
        // 处理左括号
        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        // 处理右括号
        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            
            if (!operators.empty())
                operators.pop(); // 弹出左括号
        }
        // 处理运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (!operators.empty() && operators.top() != '(' && 
                   priority(operators.top()) >= priority(expr[i])) {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.push(expr[i]);
        }
    }
    
    // 处理剩余的运算符
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += " ";
        operators.pop();
    }
    
    return postfix;
}

// 3. 后缀表达式求值
double evaluatePostfix(string expr) {
    stack<double> operands;
    
    for (int i = 0; i < expr.length(); i++) {
        // 跳过空格
        if (expr[i] == ' ')
            continue;
        
        // 处理数字
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--; // 回退一位，因为循环会自增
            operands.push(stod(num));
        }
        // 处理运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            double b = operands.top();
            operands.pop();
            double a = operands.top();
            operands.pop();
            
            operands.push(calculate(a, b, expr[i]));
        }
    }
    
    return operands.top();
}

int main() {
    string infix;
    cout << "Please enter an infix expression: ";
    getline(cin, infix);
    
    // 1. Evaluate infix expression
    cout << "Result of infix expression evaluation: " << evaluateInfix(infix) << endl;
    
    // 2. Convert infix expression to postfix
    string postfix = infixToPostfix(infix);
    cout << "Converted to postfix expression: " << postfix << endl;
    
    // 3. Evaluate postfix expression
    cout << "Result of postfix expression evaluation: " << evaluatePostfix(postfix) << endl;
    
    return 0;
}
