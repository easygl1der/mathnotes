#include <iostream>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 复制二叉树
TreeNode* copyTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    
    // 创建新节点
    TreeNode* newNode = new TreeNode(root->data);
    
    // 递归复制左右子树
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    
    return newNode;
}

// 判断两棵二叉树是否相似
bool isSimilar(TreeNode* root1, TreeNode* root2) {
    // 两棵树都为空，认为相似
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    
    // 一棵树为空，另一棵不为空，不相似
    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }
    
    // 递归判断左右子树是否相似
    return isSimilar(root1->left, root2->left) && 
           isSimilar(root1->right, root2->right);
}

// 创建一棵测试二叉树
TreeNode* createTestTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

// 创建另一棵相似但值不同的二叉树
TreeNode* createSimilarTree() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->right = new TreeNode(30);
    root->left->left = new TreeNode(40);
    root->left->right = new TreeNode(50);
    return root;
}

// 创建一棵结构不同的二叉树
TreeNode* createDifferentTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4); // 结构不同
    return root;
}

// 层序遍历打印二叉树
void printTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    
    TreeNode* queue[100]; // 简单队列实现
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        TreeNode* node = queue[front++];
        cout << node->data << " ";
        
        if (node->left) {
            queue[rear++] = node->left;
        }
        
        if (node->right) {
            queue[rear++] = node->right;
        }
    }
    cout << endl;
}

// 释放二叉树内存
void freeTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    // Create the original binary tree
    cout << "Creating the original binary tree" << endl;
    TreeNode* originalTree = createTestTree();
    cout << "Level-order traversal of the original tree: ";
    printTree(originalTree);

    // Test copying the binary tree
    cout << "\nTesting tree copy" << endl;
    TreeNode* copiedTree = copyTree(originalTree);
    cout << "Level-order traversal of the copied tree: ";
    printTree(copiedTree);

    // Test similarity check
    cout << "\nTesting binary tree similarity check" << endl;
    TreeNode* similarTree = createSimilarTree();
    TreeNode* differentTree = createDifferentTree();

    cout << "Are the original tree and the copied tree similar? " 
         << (isSimilar(originalTree, copiedTree) ? "Yes" : "No") << endl;
    cout << "Are the original tree and the similar tree similar? " 
         << (isSimilar(originalTree, similarTree) ? "Yes" : "No") << endl;
    cout << "Are the original tree and the different tree similar? " 
         << (isSimilar(originalTree, differentTree) ? "Yes" : "No") << endl;

    // Free memory
    freeTree(originalTree);
    freeTree(copiedTree);
    freeTree(similarTree);
    freeTree(differentTree);

    return 0;
}
