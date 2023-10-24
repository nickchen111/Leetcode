/*
889. Construct Binary Tree from Preorder and Postorder Traversal
*/

class Solution {
public:
    unordered_map<int, int> valtoindex;
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        for(int i = 0; i < postorder.size(); i++){
            valtoindex[postorder[i]] = i;
        }
        return build(preorder, 0, preorder.size()-1, postorder, 0, postorder.size()-1);
    }
    TreeNode* build(vector<int>& preorder, int prestart, int preend, vector<int>& postorder, int postart, int poend){
        if(prestart > preend) return nullptr;

        if(prestart == preend)  return new TreeNode(preorder[prestart]);//下面有解釋原因

        int rootval = preorder[prestart];
        //不能用此index :int index = valtoindex[rootval];

        int leftrootval = preorder[prestart+1];
        int index = valtoindex[leftrootval];
        int leftsize = index - postart+1;

        //開始構建root
        TreeNode* root = new TreeNode(rootval);
        root->left = build(preorder, prestart+1, prestart+leftsize, postorder, postart, index);
        root->right = build(preorder, prestart+leftsize+1, preend, postorder, index+1, poend-1);

        return root;
    }

};

/*
解題思路
這題是二叉樹的構造問題 
一樣是用分解問題的形式去解 只不過特別的是這題是給前序跟後序 所以答案會不只一種

因为这前序和后序构造二叉树这个算法中，我们使用了int leftRootVal = preorder[preStart + 1];来记录左子树的根节点。
如果只有一个节点的时候也就是preStart==preEnd的时候就直接返回了，如果不加这个判断的话，
我们在执行int leftRootVal = preorder[preStart + 1];的时候会出现数组越界问题。
*/
