/**************************************
     对应教材 2.7.1节，约瑟夫环问题 
***************************************/
#include <iostream>              
using namespace std;

struct Node                            //定义约瑟夫环的结点Node
{
	int data;
  	struct Node *next;
};

class JosephRing
{
public:
	JosephRing( );                      //构造函数，初始化空循环链表 
  	JosephRing(int n);                 //构造函数，初始化n个结点的环
  	~JosephRing( );                    //析构函数，同单链表析构函数 
  	void Joseph(int m);                //密码为m，打印出环的顺序
private:
	Node *rear;
};

JosephRing :: JosephRing( ) 
{
	rear = NULL;
}
 
JosephRing :: JosephRing(int n)                             
{
  	Node *s = NULL;  
	rear = new Node;     
 	rear->data = 1; rear->next = rear;     //建立长度为1的循环单链表
 	for (int i = 2; i <= n; i++)           //依次插入数据域为2、3、…、n的结点
   	{
    	s = new Node; s->data = i;
     	s->next = rear->next;               //将结点s插入尾结点rear的后面
		rear->next = s;
    	rear = s;                         //指针rear指向当前的尾结点
   	}
}

JosephRing :: ~JosephRing()
{
	if (rear != NULL){
		Node *p = rear->next;
		while(rear->next != rear)
		{
			rear->next = p->next;
			delete p;
			p = rear->next;
		}
		delete rear;
	}
}

void JosephRing :: Joseph(int m)  
{    
  	Node *pre = rear, *p = rear->next;        //初始化工作指针p和pre
  	int count = 1;                         
  	cout << "The order of the Joseph Ring is: ";
  	while (p->next != p)                   //循环直到循环链表中只剩一个结点
  	{
    	if (count < m) {                     //计数器未累加到密码值
      		pre = p; p = p->next;               //将工作指针pre和p分别后移
      		count++;                                     
    	}
    	else {                             //计数器已经累加到密码值
    		cout << p->data<< " ";             //输出出环的编号
      		pre->next = p->next;               //将结点p摘链
      		delete p;                     
			p = pre->next;                    //工作指针p后移，但pre不动
      		count = 1;                        //计数器从1开始重新计数
    	}
	}
  	cout << p->data << "\t";                //输出最后一个结点的编号
  	delete p;                              //释放最后一个结点
	rear = NULL;
}

int main( )
{
  	int n, m;
  	cout << "Please enter the length of the Joseph Ring: ";  
  	cin >> n;
  	cout << "Please enter the password: ";            
  	cin >> m;
  	JosephRing R(n);
  	R.Joseph(m); 
  	return 0;                  
}
