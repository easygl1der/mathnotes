/**************************************
   ��Ӧ�̲� 2.7.2�ڣ�һԪ����ʽ���
***************************************/
#include <iostream>       
#include <fstream>
using namespace std;

struct Node                                  //�������ʽ����Ľ��
{
	int coef, exp;                          // coef��ʾϵ����exp��ʾָ��
	Node* next;
};

class Polynomial
{
public:
	Polynomial();                          //���캯��
	~Polynomial();                         //����������ͬ��������������
	Polynomial(const Polynomial& B);          //�������캯�� 
	Polynomial & operator=(Polynomial &L);  //���ظ�ֵ�����
	Polynomial & operator + (Polynomial& B);   //�������㷨������ʽ���
	void Print();                           //��ӡһԪ����ʽ
private:
	Node* first;
};

Polynomial::~Polynomial()
{
	Node* q = NULL;
	while (first != NULL)        //�ͷŵ������ÿһ�����Ĵ洢�ռ�
	{
		q = first;                 //�ݴ汻�ͷŽ��
		first = first->next;         // firstָ���ͷŽ�����һ�����
		delete q;
	}
}

/*Polynomial::Polynomial(const Polynomial& B) {
	first = B.first;
}
*/
//���ƹ��캯�����㷨
//template <class DataType>
//LinkList<DataType>::LinkList(LinkList<DataType>& L)    //���ƹ��캯��,��ͷ�ڵ�
Polynomial::Polynomial(const Polynomial & B)
{
	Node* s, *srcptr = B.first;              //�����Ʊ��ͷ�ڵ�
	Node* destptr = new Node;
	first = destptr;            //$$$�ر�ע������Ҫ��firstָ�������ɵĽڵ�
	while (srcptr->next != NULL) {     //����ڵ㸴��
		  s = new Node;         //�����½ڵ�
		  s->coef = srcptr->next->coef;
		  s->exp = srcptr->next->exp;
		  destptr->next = s;
		  destptr = destptr->next;
		  srcptr = srcptr->next;

	}
	destptr->next = NULL;//���һ���ڵ��nextҪ�ÿ�   
}


//���ظ�ֵ��������㷨
//template <class DataType>
//LinkList<DataType>& LinkList<DataType>::operator=(LinkList<DataType>& L)    //���ظ�ֵ������ʵ��A=B��ֵ
Polynomial & Polynomial::operator=(Polynomial &L)  //���磺LA=L
{
	Node * s,*q, * srcptr = L.first;              //�����Ʊ�L��ͷ�ڵ�
	Node * destptr =first ;   //$$���ñ���ֵ�����ͷ�ڵ�
	if (first == L.first) return *this;   //$$����Լ���ֵ���Լ�������:A=A,ֱ�ӷ���
	s = first->next;
	while (s != NULL) {     //$$�ͷű���ֵ������ǰ�Ŀռ�
		q = s; s = s->next;
		delete q;
	};
	
	while (srcptr->next != NULL) {     //����ڵ㸴��
		  s = new Node ;         //�����½ڵ�
	      s->coef = srcptr->next->coef;
	      s->exp = srcptr->next->exp;
		  destptr->next = s;
		  destptr = destptr->next;
		  srcptr = srcptr->next;

	}
	destptr->next = NULL; //���һ���ڵ��nextҪ�ÿ�  
	return *this;     //���ظ�ֵ���
}



Polynomial::Polynomial()
{
	Node* r = NULL, * s = NULL;
	int coef, exp;
	first = new Node;                          //create head node
	r = first; r->next = NULL;             //build linked list using tail insertion
	
	// ���ļ���ȡ����
	ifstream inFile("input.txt");
	if (!inFile) {
		cout << "�޷��������ļ���" << endl;
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

Polynomial& Polynomial :: operator + (Polynomial& B)    //$$ע�ⷵ��ֵ�������������� 
{
	Node* pre = first, * p = pre->next;               //����ָ��pre��p��ʼ��
	Node* qre = B.first, * q = qre->next;             //����ָ��qre��q��ʼ��
	Node* qtemp = NULL;
	while (p != NULL && q != NULL)
	{
		if (p->exp < q->exp) {                     //��1�����
			pre = p; p = p->next;
		}
		else if (p->exp > q->exp) {                 //��2�����
			qtemp = q->next;
			pre->next = q;                     //�����q���뵽���p֮ǰ
			q->next = p;
			pre = q;     //$$ 
			q = qtemp;
			//pre = q;
			qre->next = q;
		}
		else {                             //��3�����
			p->coef = p->coef + q->coef;
			if (p->coef == 0) {                //ϵ�����Ϊ0����ɾ�����p
				pre->next = p->next;
				delete p;
				p = pre->next;
			}
			else {                          //ϵ����Ϊ0
				pre = p; p = p->next;
			}
			qre->next = q->next;             //��3�������Ҫɾ�����q
			delete q;
			q = qre->next;
		}
	}
	if (q != NULL) pre->next = q;          //�����q�����ڵ�һ��������ĺ���
	B.first->next = NULL;
	return *this;
}

void Polynomial::Print()
{
	Node* p = first->next;
	if (p != NULL) {                            /*�����һ��*/
		cout << p->coef << "x^" << p->exp;
		p = p->next;
		while (p != NULL)
		{
			if (p->coef > 0)                           /*���ϵ�������Ż򸺺�*/
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
