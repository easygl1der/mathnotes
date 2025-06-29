/*************************************************
    ��Ӧ�̲�2.4.2��, ��������LinkList��ʹ�÷��� 
**************************************************/
#include <iostream>                  //�������������
#define endl '\n'
using namespace std;

template <typename DataType>
struct Node
{
	DataType data;               //������
    Node<DataType> *next;       //ָ����
};

template <typename DataType>
class LinkList
{
public:
	LinkList( );                      //�޲ι��캯��������ֻ��ͷ���Ŀ�����
	LinkList(DataType a[ ], int n);       //�вι��캯����������n��Ԫ�صĵ�����
	~LinkList( );                     //��������
	Node<DataType> *Getfirst();       //**��ȡ����ͷָ��
	int Length( );                     //������ĳ���
	int Empety();
	DataType Get(int i);               //��λ���ҡ����ҵ�i������Ԫ��ֵ
	int Locate(DataType x);            //��ֵ���ҡ�����ֵΪx��Ԫ�����
	void Insert(int i, DataType x);       //�����������i��λ�ò���ֵΪx�Ľ��
	DataType Delete(int i);            //ɾ��������ɾ����i�����
	void PrintList( );                  //������������������������Ԫ��
    LinkList(const LinkList<DataType> &L);    //**���ƹ��캯�� 
    LinkList<DataType>& operator=(LinkList<DataType>& L);  //**������ֵ�������� 
private:
	Node<DataType> *first;           //�������ͷָ��
};

template <typename DataType>
LinkList<DataType> :: LinkList( )
{
	first = new Node<DataType>;              //����ͷ���
  	first->next = NULL;                      //ͷ����ָ�����ÿ�
}

template <class DataType>
LinkList<DataType> :: ~LinkList( )
{
  	Node<DataType> *q = NULL;
  	while (first != NULL)        //�ͷŵ������ÿһ�����Ĵ洢�ռ�
  	{
    	q = first;                 //�ݴ汻�ͷŽ��
    	first = first->next;         // firstָ���ͷŽ�����һ�����
    	delete q;    
 	}
}

template <class DataType>
Node<DataType> *LinkList<DataType> ::Getfirst()       //**��ȡ����ͷָ��
{ return first; }

template <typename DataType>
int LinkList<DataType> :: Empety()
{
	if(first->next == NULL)
		return 1;
	else 
		return 0;
}

template <typename DataType>
void LinkList<DataType> :: PrintList( )
{
	Node<DataType> *p = first->next;                //����ָ��p��ʼ��
  	while (p != NULL)
  	{
    	cout << p->data << " ";
    	p = p->next;                 //����ָ��p���ƣ�ע�ⲻ��д��p++
  	}
}

template <typename DataType>
int LinkList<DataType> :: Length( )
{
   	Node<DataType> *p = first->next;   //����ָ��p��ʼ��Ϊ��ʼ�ӵ�
   	int count = 0;                    //�ۼ���count��ʼ��
   	while (p != NULL)
   	{
    	p = p->next;
    	count++;
   	}
    return count;              //ע��count�ĳ�ʼ���ͷ���ֵ֮��Ĺ�ϵ
}

template <typename DataType>  
DataType LinkList<DataType> :: Get(int i) 
{
	Node<DataType> *p = first->next;    //����ָ��p��ʼ��
	int count = 1;                     //�ۼ���count��ʼ��
  	while (p != NULL && count < i)    
  	{
		p = p->next;                   //����ָ��p����
		count++;
	}
	if (p == NULL) throw "λ��";
	else return p->data;
}

template <typename DataType>  
int LinkList<DataType> :: Locate(DataType x) 
{
	Node<DataType> *p = first->next;   //����ָ��p��ʼ��
  	int count = 1;                     //�ۼ���count��ʼ��
  	while (p != NULL)    
  	{
  		if (p->data == x) return count;     //���ҳɹ��������������������
  		p = p->next;                   
  		count++;
  	}
  	return 0;                        //�˳�ѭ����������ʧ��
}

template <typename DataType>  
void LinkList<DataType> :: Insert(int i, DataType x)
{
	Node<DataType> *p = first, *s = NULL ;        //����ָ��p��ʼ��
	int count = 0;               
    while (p != NULL && count < i - 1)            //���ҵ�i �C 1�����
    {
    	p = p->next;                              //����ָ��p����
      	count++;
    }
    if (p == NULL) throw "λ��";        //û���ҵ���i �C 1�����
    else { 
      	s = new Node<DataType>; s->data = x;      //������s��������Ϊx
      	s->next = p->next; p->next = s;     //�����s���뵽���p֮��
    }
 }

// ͷ�巨���� 
//template <typename DataType>  
//LinkList<DataType> :: LinkList(DataType a[ ], int n)
//{
//	first = new Node<DataType>; first->next = NULL;     //��ʼ��һ��������
//	for (int i = 0; i < n; i++)
//	{ 
//		Node<DataType> *s;
//		s = new Node<DataType>; s->data = a[i];    
// 		s->next = first->next; first->next = s;    //�����s���뵽ͷ���֮��
//	}
//}

template <typename DataType>  
LinkList<DataType> :: LinkList(DataType a[ ], int n)
{
  	first = new Node<DataType>;                    //����ͷ���
  	Node<DataType> *r = first, *s = NULL;           //βָ���ʼ��
  	for (int i = 0; i < n; i++)
  	{	 
  		s = new Node<DataType>; s->data = a[i]; 
  		r->next = s; r = s;                 //�����s���뵽�ն˽��֮��
  	}
	r->next = NULL;        //����������ϣ����ն˽���ָ�����ÿ�
}

template <typename DataType>  
DataType LinkList<DataType> :: Delete(int i)
{
	DataType x;
  	Node<DataType> *p = first, *q = NULL;        //����ָ��pָ��ͷ���
  	int count = 0;               
  	while (p != NULL && count < i - 1)           //���ҵ�i-1�����
  	{
    	p = p->next;
    	count++;
  	}
  	if (p == NULL || p->next == NULL)  //���p�����ڻ�p�ĺ�̽�㲻����
  		throw "λ��"; 
  	else {
   		q = p->next; x = q->data;         //�ݴ汻ɾ���
   		p->next = q->next;              //ժ��
   		delete q; 
   		return x;
  	}
}

template <class DataType>
LinkList<DataType>::LinkList(const LinkList<DataType> &L)    //���ƹ��캯��,��ͷ�ڵ�
{
	first = new Node<DataType>;
	first->next = NULL;
	Node<DataType> *p = L.first->next;
	Node<DataType> *r = first;
	while(p != NULL)
	{
		Node<DataType> *s = new Node<DataType>;
		s->data = p->data;
		s->next = NULL;
		r->next = s;
		r = s;
		p = p->next;
	}
	r->next = NULL;
}

template <class DataType>
LinkList<DataType>& LinkList<DataType>::operator=(LinkList<DataType>& L)    //���ظ�ֵ������ʵ��A=B��ֵ
{
	// ����Ը�ֵ
	if (this == &L)
		return *this;
	
	// �ͷ�ԭ�������ڴ�
	Node<DataType> *p = first->next;
	while (p != NULL)
	{
		Node<DataType> *temp = p;
		p = p->next;
		delete temp;
	}
	
	// ����L������
	p = L.first->next;
	Node<DataType> *r = first;
	while (p != NULL)
	{
		Node<DataType> *s = new Node<DataType>;
		s->data = p->data;
		s->next = NULL;
		r->next = s;
		r = s;
		p = p->next;
	}
	r->next = NULL;
	
	return *this;
}

int main( )
{
    int r[6] = { 1, 2, 3,4, 4, 5 };  // , i, x;
    //LinkList<int>* p;
    //p = new LinkList<int>[3];

  	LinkList<int> L(r, 6);
  	cout << "The current linear list data is: ";
  	L.PrintList( );                         //�����ǰ����1 2 3 4 5
    cout << endl; 
   //���Ը��ƹ��캯��
   	cout << "\nThe data of the copied linear list is: ";
	LinkList<int>  L1(L);    //����L1
	L1.PrintList( ); 
   
    //���Ը�ֵ�����
    cout << "\nThe data of the assigned linear list is: ";
    LinkList<int>  L2;    //����L2
    L2 = L;
    L2.PrintList();
  	cout << endl; 
  /*	    //ɾ����ͬԪ��ʾ�� 
  		try 
	    {
	      	//L.Purge();                //���ó�Ա����ɾ����ͬԪ��                       
	      	//Purge(L.Getfirst());     //**������ͨ��ɾ������ 
	      	Purge(L);     //**������ͨ��ɾ������ 
	      	cout << "ִ��ɾ������������Ϊ��"; 
	      	L.PrintList( );                         //������������1 2 3 4 5
	      	cout << endl;
	    } 
		catch(const char* str){
	    		cout << str << endl;
	    }
  */
  	    //***
  /*	try 
  	{
    	L.Insert(2, 8);                         //�ڵ�2��λ�ò���ֵΪ8�Ľ��
    	cout << "ִ�в������������Ϊ��"; 
    	L.PrintList( );                         //������������1 8 2 3 4 5
    	cout << endl;
  	} catch(const char* str){
  		cout << str << endl;
  	}
  
	cout << "��ǰ������ĳ���Ϊ��" << L.Length( ) << endl;      //�����������6
	cout << "��������ҵ�Ԫ��ֵ��";
	cin >> x;
	i = L.Locate(x); 
    if (1 <= i) cout << "Ԫ��" << x << "��Ԫ��λ��Ϊ��" << i << endl;   
    else cout << "��������û��Ԫ��" << x << endl;
    try
    {
    	cout << "������Ҫɾ���ڼ���Ԫ�أ�";
    	cin >> i;
    	x = L.Delete(i);                                 //ɾ����i��Ԫ��
    	cout << "ɾ����Ԫ��ֵ��" << x << "ִ��ɾ������������Ϊ��";
    	L.PrintList( );                                 //���ɾ��������
    } catch(const char* str) {
  		cout << str << endl;
  }
  */
  return 0;
}
