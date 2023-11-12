/*
101. Symmetric Tree
*/

// Recursion with serialize conceopt TC:O(n) SC:O(lgn)
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        string left = traverseLeft(root->left);
        string right = traverseRight(root->right);
        if(left != right) return false;
        else return true;

    }
    string traverseLeft(TreeNode* root){
        if(root == NULL){
            return "#";
        }
        string cur = to_string(root->val);
        cur+= traverseLeft(root->right) + traverseLeft(root->left);
        return cur;
    }
    string traverseRight(TreeNode* root){
        if(root == NULL){
            return "#";
        }
        string cur = to_string(root->val);
        cur+= traverseRight(root->left) + traverseRight(root->right);
        return cur;
    }
};

// 分解問題概念
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;

        return isSymmetry(root->left, root->right);
    }

    bool isSymmetry(TreeNode* p, TreeNode* q){
        if(p == NULL && q == NULL) return true;
        if(p==NULL || q==NULL) return false;

        if(p->val != q->val) return false;

        return isSymmetry(p->left,q->right) && isSymmetry(q->left,p->right);
    }
};

// BFS TC:O(n) SC:O(w)
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;

        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        while(!q.empty()){
            TreeNode* leftNode = q.front();
            q.pop();
            TreeNode* rightNode = q.front();
            q.pop();

            if(leftNode==NULL && rightNode==NULL) continue;
            if(leftNode==NULL || rightNode==NULL || leftNode->val != rightNode->val) return false;
            q.push(leftNode->left);
            q.push(rightNode->right);
            q.push(leftNode->right);
            q.push(rightNode->left);
        }
        return true;
    }
};
