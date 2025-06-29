/*
 * 在二叉排序树上找出任意两个不同结点的公共祖先
 */
#include <iostream>
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
    BiNode<int>* getRoot() { return root; }       // 获取根节点

    BiNode<int>* SearchBST(int k);                // 查找值为k的结点
    BiNode<int>* Ancestor(BiNode<int>* A, BiNode<int>* B);  // 找公共祖先

private:
    void Release(BiNode<int>* bt);
    BiNode<int>* InsertBST(BiNode<int>* & bt, int x);
    BiNode<int>* SearchBST(BiNode<int>* & bt, int k);
    BiNode<int>* ancestorHelper(BiNode<int>* A, BiNode<int>* B, BiNode<int>* root);

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

BiNode<int>* BiSortTree::SearchBST(int k)
{
    return SearchBST(root, k);
}

BiNode<int>* BiSortTree::SearchBST(BiNode<int>* & bt, int k)
{
    if (bt == NULL) return NULL;
    if (bt->data == k) return bt;
    else if (bt->data > k) return SearchBST(bt->lchild, k);
    else return SearchBST(bt->rchild, k);
}

BiNode<int>* BiSortTree::Ancestor(BiNode<int>* A, BiNode<int>* B)
{
    return ancestorHelper(A, B, root);
}

BiNode<int>* BiSortTree::ancestorHelper(BiNode<int>* A, BiNode<int>* B, BiNode<int>* root)
{
    if (root == NULL) return NULL;
    
    // Case 1: If either A or B is the root
    if (A == root || B == root) return root;
    
    // Case 2: If A's value is less than root and B's value is greater than root
    if ((A->data < root->data) && (B->data > root->data)) return root;
    
    // Case 3: If A's value is greater than root and B's value is less than root
    if ((A->data > root->data) && (B->data < root->data)) return root;
    
    // Case 4: If both A and B are less than root, search left subtree
    if ((A->data < root->data) && (B->data < root->data))
        return ancestorHelper(A, B, root->lchild);
    
    // Case 5: If both A and B are greater than root, search right subtree
    if ((A->data > root->data) && (B->data > root->data))
        return ancestorHelper(A, B, root->rchild);
    
    // If none of the above conditions match, return root
    return root;
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
    int key1, key2;
    cout << "请输入两个不同的元素：";
    cin >> key1 >> key2;
    
    BiNode<int>* A = B.SearchBST(key1);
    BiNode<int>* B_node = B.SearchBST(key2);
    
    if (A == NULL || B_node == NULL) {
        cout << "输入的元素不存在于二叉排序树中" << endl;
        return 0;
    }
    
    BiNode<int>* ancestor = B.Ancestor(A, B_node);
    cout << "公共祖先的值为：" << ancestor->data << endl;
    
    return 0;
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


