#include <iostream>
#include <cmath>
using namespace std;


/*
>1.定义三角形类，给定三边长，计算周长和面积
>2.用类模板，编写一个数组类并测试相应功能
>3.用函数模板，用选择排序法和指针操作，实现降序排序。
 */


class Triangle {
private:
 double a, b, c;
public:
 Triangle(double side1, double side2, double side3) {
  a = side1;
  b = side2;
  c = side3;
 }
 double getPerimeter() const {
  return a + b + c;
 }
 double getArea() const {
  double s = getPerimeter() / 2.0;
  return sqrt(s * (s - a) * (s - b) * (s - c));
 }
 void display() const {
  cout << "edges: a=" << a << ", b=" << b << ", c=" << c << endl;
  cout << "Perimeter: " << getPerimeter() << endl;
  cout << "Square: " << getArea() << endl;
 }
};

int main() {
 double a, b, c;
 cout << "input the length of edges of the triangle: ";
 cin >> a >> b >> c;

 if (a + b > c && a + c > b && b + c > a) {
  Triangle triangle(a, b, c);
  triangle.display();
 } else {
  cout << "the edges don't form a triangle" << endl;
 }

 return 0;
}
