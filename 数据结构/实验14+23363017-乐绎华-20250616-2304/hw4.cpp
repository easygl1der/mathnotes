/*
 * 计算二叉树各结点的平衡因子
 */
#include <iostream>
#include <algorithm>
using namespace std;

// 定义AVL树节点结构
template <typename DataType>
struct AVLNode
{
    DataType data;
    AVLNode<DataType>* lchild, * rchild;
    int bf;  // 平衡因子
};

class AVLTree 
{
public:
    AVLTree(int a[], int n);                   // 构造AVL树
    ~AVLTree() { Release(root); }              // 析构函数
    
    // 计算树的高度
    int getHeight(AVLNode<int>* node);
    
    // 计算平衡因子
    void calculateBalanceFactor();
    
    // 打印树的平衡因子
    void printBalanceFactor();
    
    // 获取根节点
    AVLNode<int>* getRoot() { return root; }

private:
    void Release(AVLNode<int>* bt);
    AVLNode<int>* InsertAVL(AVLNode<int>* & bt, int x);
    void calculateBalanceFactorHelper(AVLNode<int>* node);

    AVLNode<int>* root;                        // AVL树的根指针
};

AVLTree::AVLTree(int a[], int n)
{
    root = NULL;
    for (int i = 0; i < n; i++)
        root = InsertAVL(root, a[i]);
}

AVLNode<int>* AVLTree::InsertAVL(AVLNode<int>* & bt, int x)
{
    if (bt == NULL) {                         
        AVLNode<int>* s = new AVLNode<int>;
        s->data = x;
        s->lchild = NULL; 
        s->rchild = NULL;
        s->bf = 0;  // 初始平衡因子为0
        bt = s;
    }
    else if (bt->data > x) bt->lchild = InsertAVL(bt->lchild, x);
    else bt->rchild = InsertAVL(bt->rchild, x);
    return bt;
}

// 计算节点高度
int AVLTree::getHeight(AVLNode<int>* node)
{
    if (node == NULL) return 0;
    
    int leftHeight = getHeight(node->lchild);
    int rightHeight = getHeight(node->rchild);
    
    return max(leftHeight, rightHeight) + 1;
}

// 计算平衡因子的辅助函数
void AVLTree::calculateBalanceFactorHelper(AVLNode<int>* node)
{
    if (node == NULL) return;
    
    // 先计算左右子树高度
    int leftHeight = getHeight(node->lchild);
    int rightHeight = getHeight(node->rchild);
    
    // 平衡因子 = 左子树高度 - 右子树高度
    node->bf = leftHeight - rightHeight;
    
    // 递归计算左右子树的平衡因子
    calculateBalanceFactorHelper(node->lchild);
    calculateBalanceFactorHelper(node->rchild);
}

// 计算整棵树的平衡因子
void AVLTree::calculateBalanceFactor()
{
    calculateBalanceFactorHelper(root);
}

// 打印平衡因子的递归辅助函数
void printBalanceFactorRecursive(AVLNode<int>* node)
{
    if (node == NULL) return;
    
    // 中序遍历：左-根-右
    printBalanceFactorRecursive(node->lchild);
    cout << "节点 " << node->data << " 的平衡因子：" << node->bf << endl;
    printBalanceFactorRecursive(node->rchild);
}

// 打印平衡因子
void AVLTree::printBalanceFactor()
{
    printBalanceFactorRecursive(root);
}

void AVLTree::Release(AVLNode<int>* bt)
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
    AVLTree tree(arr, 10);
    
    // 打印树的结构
    cout << "AVL树的结构：" << endl;
    cout << "        7" << endl;
    cout << "       / \\" << endl;
    cout << "      2   10" << endl;
    cout << "     / \\  /" << endl;
    cout << "    1   3 8" << endl;
    cout << "         \\ \\" << endl;
    cout << "          5 9" << endl;
    cout << "         / \\" << endl;
    cout << "        4   6" << endl;
    
    // 计算并打印平衡因子
    tree.calculateBalanceFactor();
    cout << "\n各节点的平衡因子：" << endl;
    tree.printBalanceFactor();
    
    return 0;
}
