/*
222. Count Complete Tree Nodes
*/

 //滿二叉樹算法 TC:(lgn*lgn) SC:O(lgn)
class Solution {
public:
    int countNodes(TreeNode* root) {
        TreeNode* l = root, *r = root;

        // 沿最左侧和最右侧分别计算高度
        int hl = 0, hr = 0;

        while(l != nullptr){
            l = l->left;
            hl++;
        }
       while(r != nullptr){
            r = r->right;
            hr++;
        }

        // 如果左右侧计算的高度相同，则是一棵满二叉树
        if(hl == hr){
            return pow(2, hl)-1;
        }

        // 如果左右侧的高度不同，则按照普通二叉树的逻辑计算
        return 1+ countNodes(root->left) + countNodes(root->right);
    }
};

/*
此題是結合普通二叉樹算法跟滿二叉樹節點數量算法的綜合體 當然也是可以用普通二叉樹方式來計算 但時間複雜度就是比較高
所以時間複雜度為o(lgn *lgn) sc: o(lgn)
算法的递归深度就是树的高度 O(logN)，每次递归所花费的时间就是 while 循环，需要 O(logN)，所以总体的时间复杂度是 O(logN*logN)。

普通算法：
if(root == nullptr) return 0;

return 1+ counNodes(root->left) + counNodes(root->right)

滿二叉樹算法：
if(root == nulltpr) return 0;
int h = 0;
whil(root->left != nullptr){
    root = root->left;
    h++;
}

return pow(2, h)-1;
*/
