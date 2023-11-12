/*
1261. Find Elements in a Contaminated Binary Tree
*/

// Hash set TC:O(n) SC:O(n)
class FindElements {
public:
    TreeNode* root;
    unordered_set<int> set;
    FindElements(TreeNode* root) {
        this->root = root;
        root->val = 0;
        traverse(root);
    }
    void traverse(TreeNode* root){
        if(root==NULL) return;
        set.insert(root->val);

        if(root->left){
            root->left->val = (root->val)*2+1;
        }
        if(root->right){
            root->right->val = (root->val)*2+2;
        }

        traverse(root->left);
        traverse(root->right);

    }
    
    bool find(int target) {
        if(set.find(target) != set.end()) return true;
        else return false;
    }
};

// 粗暴解
class FindElements {
public:
    TreeNode* root;
    FindElements(TreeNode* root) {
        this->root = root;
        traverse(root,-1);
    }
    void traverse(TreeNode* root,int cur){
        if(root==NULL) return;
        if(cur== -1){
            root->val = 0;
            cur = root->val;
        }
        else {
            root->val = cur;
        }

        int left = (cur)*2+1;
        int right = (cur)*2+2; 
        traverse(root->left,left);
        traverse(root->right,right);

    }
    
    bool find(int target) {
        return DFS(target,root);
    }
    bool DFS(int target, TreeNode* root){
        if(root == NULL) return false;
        if(root->val == target) return true;
        return DFS(target, root->left) || DFS(target,root->right);
    }
};
