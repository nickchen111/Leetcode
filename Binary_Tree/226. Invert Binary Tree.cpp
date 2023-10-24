/*
226. Invert Binary Tree
*/


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//我寫的方式利用bfs tc: o(n) sc: o(w) w為最寬的層級的節點數
class Solution1 {
public:
//bfs
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        queue<TreeNode*> q; 
        q.push(root);
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            TreeNode* temp = node->left;
            node->left = node->right;
            node->right = temp;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        return root;
    }
};

//bst兩大思維 1. 能否用遍歷方式得出解答 2.能否自己定義遞歸 用遞歸分解問題解答

//遍歷方式 跟我寫的bfs類似 tc: o(n) sc:o(h) h 為樹的高度
class Solution2 {
public:
// 主函数
TreeNode* invertTree(TreeNode* root) {
    // 遍历二叉树，交换每个节点的子节点
    traverse(root);
    return root;
}

// 二叉树遍历函数
void traverse(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    /**** 前序位置 ****/
    // 每一个节点需要做的事就是交换它的左右子节点
    TreeNode* tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    // 遍历框架，去遍历左右子树的节点
    traverse(root->left);
    traverse(root->right);
}
};


//dfs 用遞歸的方式 分解問題 tc: o(n) sc:o(h) h 為樹的高度
// 定义：将以 root 为根的这棵二叉树翻转，返回翻转后的二叉树的根节点
class Solution3 {
public:
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    // 利用函数定义，先翻转左右子树
    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);

    // 然后交换左右子节点
    root->left = right;
    root->right = left;

    // 和定义逻辑自恰：以 root 为根的这棵二叉树已经被翻转，返回 root
    return root;
}
};
