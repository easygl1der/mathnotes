/*
 * 判断一棵二叉树是否为二叉排序树
 */
#include <iostream>
#include <climits>
using namespace std;

template <typename DataType>
struct BiNode
{
    DataType data;
    BiNode<DataType>* lchild, * rchild;
};

class BiSortTree 
{
public:
    BiSortTree(int a[], int n);                   // 建立查找集合a[n]的二叉排序树
    ~BiSortTree() { Release(root); }              // 析构函数
    
    int SortBiTree(BiNode<int>* root);            // 判断是否为二叉排序树
    BiNode<int>* getRoot() { return root; }       // 获取根节点

private:
    void Release(BiNode<int>* bt);
    BiNode<int>* InsertBST(BiNode<int>* & bt, int x);

    BiNode<int>* root;                            // 二叉排序树的根指针
};

BiSortTree::BiSortTree(int a[], int n)
{
    root = NULL;
    for (int i = 0; i < n; i++)
        root = InsertBST(root, a[i]);
}

BiNode<int>* BiSortTree::InsertBST(BiNode<int>* & bt, int x)
{
    if (bt == NULL) {                         
        BiNode<int>* s = new BiNode<int>;
        s->data = x;
        s->lchild = NULL; s->rchild = NULL;
        bt = s;
    }
    else if (bt->data > x) bt->lchild = InsertBST(bt->lchild, x);
    else bt->rchild = InsertBST(bt->rchild, x);
    return bt;
}

int BiSortTree::SortBiTree(BiNode<int>* root)
{
    // 记录上一个遍历的结点值，初始为负无穷
    static int pre = INT_MIN;
    
    // 空树认为是二叉排序树
    if (root == NULL) return 1;
    
    // 递归遍历左子树
    int b1 = SortBiTree(root->lchild);
    
    // 如果左子树不是二叉排序树，返回0
    if (b1 == 0) return 0;
    
    // 检查当前节点是否大于前一个节点
    if (root->data <= pre) return 0;
    
    // 更新pre为当前节点的值
    pre = root->data;
    
    // 递归遍历右子树
    int b2 = SortBiTree(root->rchild);
    
    return b2;
}

void BiSortTree::Release(BiNode<int>* bt)
{
    if (bt == NULL) return;
    else {
        Release(bt->lchild);                   
        Release(bt->rchild);                   
        delete bt;                            
    }
}

int main()
{
    int arr[10] = { 7, 2, 3, 10, 5, 6, 1, 8, 9, 4 };
    BiSortTree B(arr, 10);
    
    // 打印树的结构
    cout << "二叉排序树的结构：" << endl;
    cout << "        7" << endl;
    cout << "       / \\" << endl;
    cout << "      2   10" << endl;
    cout << "     / \\  /" << endl;
    cout << "    1   3 8" << endl;
    cout << "         \\ \\" << endl;
    cout << "          5 9" << endl;
    cout << "         / \\" << endl;
    cout << "        4   6" << endl;
    
    // 判断是否为二叉排序树
    int result = B.SortBiTree(B.getRoot());
    
    if (result) {
        cout << "该二叉树是二叉排序树" << endl;
    } else {
        cout << "该二叉树不是二叉排序树" << endl;
    }
    
    return 0;
}
