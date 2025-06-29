/******************************************* 
   ��Ӧ�̲�2.6.2�ڣ�˳���Ķ�̬���䷽ʽ 
********************************************/
#include <iostream>
using namespace std; 

const int InitSize = 100;                     //˳���ĳ�ʼ����
const int IncreSize = 10;                     //˳���洢�ռ�ÿ����չ�ĳ���
template <typename DataType>
class SeqList
{
public:
	SeqList( );                     //�޲ι��캯���������յ�˳���
   	SeqList(DataType a[ ], int n);      //�вι��캯������������Ϊn��˳���
   	~SeqList( );                    //��������
   	int Length( );                   //�����Ա�ĳ���
   	int Empety();                    //�ж����Ա��Ƿ�Ϊ��
   	DataType Get(int i);              //��λ���ң����ҵ�i��Ԫ�ص�ֵ
   	int Locate(DataType x );          //��ֵ���ң�����ֵΪx��Ԫ�����
   	void Insert(int i, DataType x);      //����������ڵ�i��λ�ò���ֵΪx��Ԫ��
   	DataType Delete(int i);            //ɾ��������ɾ����i��Ԫ��
   	void PrintList( );                 //������������������������Ԫ��
	// ��Ԫ�� x ���뵽���У�������˳������������
	void SortedInsert(DataType x);  //���������������ֱ��������
	// ɾ������ֵΪx��Ԫ��
	void DeleteValueAll(DataType x);    //ɾ������ֵΪx��Ԫ��
	// ��˳�������
	void Reverse();                     //��˳�������
private:
  DataType *data;                       //��̬��������ռ���׵�ַ
  int maxSize;                          //��ǰ����ռ����󳤶�
  int length;                           //���Ա�ĳ���
};

template <typename DataType>  
SeqList<DataType> :: SeqList( )
{
	data = new DataType[InitSize];      //��̬�����ʼ�ռ�
	maxSize = InitSize;                 //������󳤶�Ϊ��ʼ����
	length = 0;                         //��ʼ������Ϊ0
}

template <typename DataType>  
SeqList<DataType> :: SeqList(DataType a[ ], int n)
{
	data = new DataType[2 * n];         //����2n�Ĵ洢�ռ�
	maxSize = 2 * n;                    //������󳤶�Ϊ2n
  	for (int i = 0; i < n; i++)         //��������Ԫ�ص�˳���
		data[i] = a[i];
	length = n;                         //����˳�����Ϊn
}

template <typename DataType>  
SeqList<DataType> ::~SeqList( )
{
	delete[ ] data;                     //�ͷŶ�̬������ڴ�ռ�
}

template <class DataType>
int SeqList<DataType> :: Empety()
{
	if(length == 0)                     //�������Ϊ0����ʾΪ��
		return 1;
	else
		return 0;                       //����Ϊ��
}

template <class DataType>
int SeqList<DataType> :: Length()
{
	return length;                      //����˳���ĳ���
}

template <class DataType>  
void SeqList<DataType>::PrintList()
{
    for (int i = 0; i < length; i++)    // ����˳���
        cout << data[i] << " ";         // ����������Ա��Ԫ��ֵ
    cout << endl;                       // ��ӻ���
}

template <class DataType>  
int SeqList<DataType> :: Locate(DataType x)
{
   	for (int i = 0; i < length; i++)    //����˳���
    	if (data[i] == x) return i+1;   //�ҵ�Ԫ��x�����������i+1
   	return 0;                           //�˳�ѭ����˵������ʧ��
}

template <class DataType>  
DataType SeqList<DataType> :: Get(int i)
{
	if (i < 1 && i > length)            //���λ���Ƿ�Ϸ�
		throw "����λ�÷Ƿ�";
	else 
		return data[i - 1];             //���ص�i��Ԫ�ص�ֵ
}

template <class DataType>  
DataType SeqList<DataType> :: Delete(int i)
{
	if (length == 0)                    //����Ƿ�Ϊ�ձ�
		throw "����";
	if (i < 1 || i > length)            //���λ���Ƿ�Ϸ�
		throw "λ��";
	int x = data[i - 1];                //ȡ��λ��i��Ԫ��
	for (int j = i; j < length; j++)    //�������Ԫ��ǰ��
		data[j - 1] = data[j];          //�˴�j�Ѿ���Ԫ�����ڵ������±�
	length--;                           //���ȼ�1
	return x;                           //���ر�ɾ����Ԫ��
}

template <typename DataType>  
void SeqList<DataType> :: Insert(int i, DataType x)
{
	if (i < 1 || i > length + 1) throw "����λ�ô���";  //���λ���Ƿ�Ϸ�
	if (length == maxSize) {                              //�������磬����洢�ռ�
		DataType *oldData = data;                         //����ԭ����ָ��
		maxSize += IncreSize;                             //���Ӵ洢�ռ�
		data = new DataType[maxSize];                     //���·������Ŀռ�
		for (int j = 0; j < length; j++)                  //����ԭ������
  			data[j] = oldData[j];
		delete[ ] oldData;                                //�ͷ�ԭ���Ŀռ�
   	}
	for (int j = length; j >= i; j--)                     //��Ԫ�غ��ƣ�j��ʾԪ�����
		data[j] = data[j - 1]; 
	data[i - 1] = x;                                      //��λ��i������Ԫ��
	length++;                                             //���ȼ�1
}

	// ��Ԫ�� x ���뵽���У�������˳������������

template <typename DataType>  
void SeqList<DataType>::SortedInsert(DataType x)  // ��������޶�
{
    for (int i = 0; i < length; i++) {
        if (data[i] > x) {
            Insert(i+1, x);
            return;
        }
    }
    // ���û�ҵ���x���Ԫ�أ����뵽ĩβ
    Insert(length+1, x);
}
// ɾ������ֵΪx��Ԫ��

template <typename DataType>  
void SeqList<DataType>::DeleteValueAll(DataType x)  // ��������޶�
{
    int i = 0;
    while (i < length) {
        if (data[i] == x) {
            Delete(i+1);  // Delete����ʹ��1-based����
        } else {
            i++;
        }
    }
}


	// ��˳�������
template <typename DataType>  
void SeqList<DataType>::Reverse()  // ��������޶�
{
    for (int i = 0; i < length/2; i++) {
        DataType temp = data[i];
        data[i] = data[length-1-i];
        data[length-1-i] = temp;
    }
}


int main( )
{
	int r[5] = {1, 2, 3, 4, 5}, i, x;                    //�����������ͱ���
   	SeqList<int> L(r, 5);                                //��������5��Ԫ�ص�˳���
   	cout << "the first list is:";
   	L.PrintList( );                                      //�����ǰ���Ա�1 2 3 4 5
  
  	SeqList<int> L2,L3;                                  //����������˳���
  	L3=L2;                                               //��L2��ֵ��L3
   	cout << "the second list is:";
   	L3.PrintList( );                                     //���L3������
	cout << endl;
	// ��������������
  try
  {
    cout << "test the SortedInsert function:" << endl;
    L.SortedInsert(3);
    cout << "after the sorted insert operation, the data is:";
    L.PrintList();
    cout << endl;
  }
  catch(const char* str)
  {
    cout << str << "the sorted insert operation error!" << endl;
  }
	// ����ɾ������ֵΪ3��Ԫ��
  try
  {
    cout << "test the DeleteValueAll function:" << endl;
    L.DeleteValueAll(3);
    cout << "after the delete operation, the data is:";
    L.PrintList();
    cout << endl;
  }
  catch(const char* str)
  {
    cout << str << "the delete operation error!" << endl;
  }
	// �������ò���
  try
  {
    cout << "test the Reverse function:" << endl;
    L.Reverse();
    cout << "after the reverse operation, the data is:";
    L.PrintList();
    cout << endl;
  }
  catch(const char* str)
  {
    cout << str << "the reverse operation error!" << endl;
  }
  /* 	try 
   	{
   		L.Insert(2, 8);                        //�ڵ�2��λ�ò���ֵΪ8��Ԫ��
   		cout << endl << "ִ�в������������Ϊ��";
   		L.PrintList( );                        //������������Ա�1 8 2 3 4 5
   		cout << endl;
   	}catch(const char* str){
   		cout << str << "�����������" << endl;
   	}
   
   	cout << "��ǰ���Ա�ĳ���Ϊ��" << L.Length( );    //������Ա�ĳ���6
   	cout << endl;
   	cout << "��������ҵ�Ԫ��ֵ��";
   	cin >> x;
   	i = L.Locate(x);
   	if (0 == i) cout << "����ʧ��" << endl;
   	else cout << "Ԫ��" << x << "��λ��Ϊ��" << i << endl;          
   	try
   	{
   		cout << "��������ҵڼ���Ԫ��ֵ��";
   		cin >> i;
   		cout << "��" << i << "��Ԫ��ֵ��" << L.Get(i) << endl;
   	}catch(const char* str){
   		cout << "���Ա���û�и�Ԫ��" << endl;
   	} 
   	try 
   	{
		cout << "������Ҫɾ���ڼ���Ԫ�أ�";
	   	cin >> i;
	   	x = L.Delete(i);                              //ɾ����i��Ԫ��
	   	cout << "ɾ����Ԫ����" << x <<"��ɾ��������Ϊ��";
   	   	L.PrintList( );                           //���ɾ��������Ա�
   	}catch(const char* str){
   		cout << "ɾ������" << endl;
   	} 
   	*/
   
	return 0;                                           //������������
}
