#include <iostream>
using namespace std;

// 树的结点结构 - 孩子兄弟表示法
struct TreeNode {
    int data;               // 结点数据
    TreeNode* firstChild;   // 指向第一个孩子
    TreeNode* nextSibling;  // 指向下一个兄弟
    
    TreeNode(int val) : data(val), firstChild(nullptr), nextSibling(nullptr) {}
};

// 查找结点x的第i个孩子（i从1开始计数）
TreeNode* findIthChild(TreeNode* x, int i) {
    if (x == nullptr || i < 1) {
        return nullptr;
    }
    
    // 找到第一个孩子
    TreeNode* child = x->firstChild;
    if (child == nullptr) {
        return nullptr; // 没有孩子
    }
    
    // 查找第i个孩子
    int count = 1;
    while (count < i && child != nullptr) {
        child = child->nextSibling;
        count++;
    }
    
    // 如果count等于i，说明找到了第i个孩子
    if (count == i) {
        return child;
    } else {
        return nullptr; // 孩子数量少于i
    }
}

// 创建一棵示例树
TreeNode* createSampleTree() {
    /*
           1
         / | \
        2  3  4
       /|  |  |\
      5 6  7  8 9
    */
    
    TreeNode* root = new TreeNode(1);
    
    // 第一层子结点
    root->firstChild = new TreeNode(2);
    root->firstChild->nextSibling = new TreeNode(3);
    root->firstChild->nextSibling->nextSibling = new TreeNode(4);
    
    // 第二层子结点
    root->firstChild->firstChild = new TreeNode(5);
    root->firstChild->firstChild->nextSibling = new TreeNode(6);
    
    root->firstChild->nextSibling->firstChild = new TreeNode(7);
    
    root->firstChild->nextSibling->nextSibling->firstChild = new TreeNode(8);
    root->firstChild->nextSibling->nextSibling->firstChild->nextSibling = new TreeNode(9);
    
    return root;
}

// 打印树结构（前序遍历）
void printTree(TreeNode* node, int level = 0) {
    if (node == nullptr) {
        return;
    }
    
    // 打印当前结点
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << "|--" << node->data << endl;
    
    // 递归打印所有子节点
    printTree(node->firstChild, level + 1);
    
    // 递归打印所有兄弟节点
    printTree(node->nextSibling, level);
}

// 释放树内存
void freeTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    
    // 释放所有子节点
    freeTree(node->firstChild);
    
    // 释放所有兄弟节点
    freeTree(node->nextSibling);
    
    // 释放当前节点
    delete node;
}

int main() {
    TreeNode* root = createSampleTree();

    cout << "Tree structure:" << endl;
    printTree(root);

    cout << "\nExample: Find the children of nodes:" << endl;

    // Find the children of the root node
    for (int i = 1; i <= 4; i++) {
        TreeNode* child = findIthChild(root, i);
        if (child) {
            cout << "The " << i << "th child of node " << root->data << " is: " << child->data << endl;
        } else {
            cout << "Node " << root->data << " does not have a " << i << "th child" << endl;
        }
    }

    // Find the children of an internal node
    TreeNode* node2 = root->firstChild; // Node 2
    for (int i = 1; i <= 3; i++) {
        TreeNode* child = findIthChild(node2, i);
        if (child) {
            cout << "The " << i << "th child of node " << node2->data << " is: " << child->data << endl;
        } else {
            cout << "Node " << node2->data << " does not have a " << i << "th child" << endl;
        }
    }

    // Find the children of a leaf node
    TreeNode* leaf = root->firstChild->firstChild; // Node 5
    TreeNode* child = findIthChild(leaf, 1);
    if (child) {
        cout << "The 1st child of node " << leaf->data << " is: " << child->data << endl;
    } else {
        cout << "Node " << leaf->data << " has no children" << endl;
    }

    // Free memory
    freeTree(root);

    return 0;
}
