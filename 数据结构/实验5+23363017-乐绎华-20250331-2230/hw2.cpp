/**************************************
   对应教材 2.7.2节，一元多项式求和
***************************************/
#include <iostream>       
#include <fstream>
using namespace std;

struct Node                                  //定义多项式链表的结点
{
	int coef, exp;                          // coef表示系数，exp表示指数
	Node* next;
};

class Polynomial
{
public:
	Polynomial();                          //构造函数
	~Polynomial();                         //析构函数，同单链表析构函数
	Polynomial(const Polynomial& B);          //拷贝构造函数 
	Polynomial & operator=(Polynomial &L);  //重载赋值运算符
	Polynomial & operator + (Polynomial& B);   //重载运算法，多项式相加
	void Print();                           //打印一元多项式
private:
	Node* first;
};

Polynomial::~Polynomial()
{
	Node* q = NULL;
	while (first != NULL)        //释放单链表的每一个结点的存储空间
	{
		q = first;                 //暂存被释放结点
		first = first->next;         // first指向被释放结点的下一个结点
		delete q;
	}
}

/*Polynomial::Polynomial(const Polynomial& B) {
	first = B.first;
}
*/
//复制构造函数的算法
//template <class DataType>
//LinkList<DataType>::LinkList(LinkList<DataType>& L)    //复制构造函数,带头节点
Polynomial::Polynomial(const Polynomial & B)
{
	Node* s, *srcptr = B.first;              //被复制表的头节点
	Node* destptr = new Node;
	first = destptr;            //$$$特别注意这里要把first指向新生成的节点
	while (srcptr->next != NULL) {     //逐个节点复制
		  s = new Node;         //生成新节点
		  s->coef = srcptr->next->coef;
		  s->exp = srcptr->next->exp;
		  destptr->next = s;
		  destptr = destptr->next;
		  srcptr = srcptr->next;

	}
	destptr->next = NULL;//最后一个节点的next要置空   
}


//重载赋值运算符的算法
//template <class DataType>
//LinkList<DataType>& LinkList<DataType>::operator=(LinkList<DataType>& L)    //重载赋值函数，实现A=B赋值
Polynomial & Polynomial::operator=(Polynomial &L)  //例如：LA=L
{
	Node * s,*q, * srcptr = L.first;              //被复制表L的头节点
	Node * destptr =first ;   //$$利用被赋值链表的头节点
	if (first == L.first) return *this;   //$$如果自己赋值给自己，比如:A=A,直接返回
	s = first->next;
	while (s != NULL) {     //$$释放被赋值链表以前的空间
		q = s; s = s->next;
		delete q;
	};
	
	while (srcptr->next != NULL) {     //逐个节点复制
		  s = new Node ;         //生成新节点
	      s->coef = srcptr->next->coef;
	      s->exp = srcptr->next->exp;
		  destptr->next = s;
		  destptr = destptr->next;
		  srcptr = srcptr->next;

	}
	destptr->next = NULL; //最后一个节点的next要置空  
	return *this;     //返回赋值结果
}



Polynomial::Polynomial()
{
	Node* r = NULL, * s = NULL;
	int coef, exp;
	first = new Node;                          //create head node
	r = first; r->next = NULL;             //build linked list using tail insertion
	
	// 从文件读取数据
	ifstream inFile("input.txt");
	if (!inFile) {
		cout << "无法打开输入文件！" << endl;
		return;
	}
	
	while (inFile >> coef >> exp) {
		if (coef == 0 && exp == 0) break;
		s = new Node; s->coef = coef; s->exp = exp;
		r->next = s; r = s;
	}
	r->next = NULL;
	inFile.close();
}

Polynomial& Polynomial :: operator + (Polynomial& B)    //$$注意返回值类型是引用类型 
{
	Node* pre = first, * p = pre->next;               //工作指针pre和p初始化
	Node* qre = B.first, * q = qre->next;             //工作指针qre和q初始化
	Node* qtemp = NULL;
	while (p != NULL && q != NULL)
	{
		if (p->exp < q->exp) {                     //第1种情况
			pre = p; p = p->next;
		}
		else if (p->exp > q->exp) {                 //第2种情况
			qtemp = q->next;
			pre->next = q;                     //将结点q插入到结点p之前
			q->next = p;
			pre = q;     //$$ 
			q = qtemp;
			//pre = q;
			qre->next = q;
		}
		else {                             //第3种情况
			p->coef = p->coef + q->coef;
			if (p->coef == 0) {                //系数相加为0，则删除结点p
				pre->next = p->next;
				delete p;
				p = pre->next;
			}
			else {                          //系数不为0
				pre = p; p = p->next;
			}
			qre->next = q->next;             //第3种情况都要删除结点q
			delete q;
			q = qre->next;
		}
	}
	if (q != NULL) pre->next = q;          //将结点q链接在第一个单链表的后面
	B.first->next = NULL;
	return *this;
}

void Polynomial::Print()
{
	Node* p = first->next;
	if (p != NULL) {                            /*输出第一项*/
		cout << p->coef << "x^" << p->exp;
		p = p->next;
		while (p != NULL)
		{
			if (p->coef > 0)                           /*输出系数的正号或负号*/
				cout << " + " << p->coef << "x^" << p->exp;
			else
				cout << p->coef << "x^" << p->exp;
			p = p->next;
		}
	}
	cout << endl;
}

int main()
{
	cout << "Reading polynomial A from file:" << endl;
	Polynomial A;
	A.Print();
	
	cout << "Reading polynomial B from file:" << endl;
	Polynomial B;
	B.Print();
	
	cout << "Result of A + B:" << endl;
	A + B;
	A.Print();
	
	return 0;
}
