/*
106. Construct Binary Tree from Inorder and Postorder Traversal
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    unordered_map<int,int> map;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for(int i = 0; i<inorder.size(); i++){
            map.insert({inorder[i],i});
        }

        return traverse(inorder,0 ,inorder.size()-1, postorder, 0, postorder.size()-1);
    }
    TreeNode* traverse(vector<int>& inorder, int inStart , int inEnd, vector<int>& postorder, int poStart, int poEnd){
        if(poStart > poEnd) return NULL;

        int root_val = postorder[poEnd];
        int idx = map[root_val];//inorder root_index
        int leftsize = idx - inStart;
        TreeNode* root = new TreeNode(root_val);
        root->left = traverse(inorder, inStart, inStart+leftsize, postorder, poStart, poStart+leftsize-1);
        root->right = traverse(inorder, inStart+1+leftsize,inEnd, postorder, poStart+leftsize,poEnd-1);

        return root;
    }
};

/*
[9 3 15 20 7] left root right inorder
[9 15 7 20 3] left right root postorder
*/

/*
此題也是一個構造出tree的經典題
tree = 根+左子樹+ 右子樹 採用分解問題的recursion去做
定義一個遞歸函式 子問題的解答可以去推導出母題的解答
此題有給inorder 跟 postorder 分別是 root->left, root, root->right 以及 root->left, root->right, root
所以根節點必定在postorder最後面 

tc: o(n) sc: o(n)
*/
