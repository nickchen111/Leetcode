/*
105. Construct Binary Tree from Preorder and Inorder Traversal
*/


// 10/13
class Solution {
public:
    unordered_map<int,int> map;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i<inorder.size(); i++){
            map.insert({inorder[i],i});
        }
        //主要是要遍歷preorder 每一次遍歷都可以確定每顆子樹的根節點
        return traverse(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
    TreeNode* traverse(vector<int>& preorder,int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd){
        if(preStart > preEnd) return nullptr;

        int root_val = preorder[preStart];
        int idx = map[root_val];//在inorder中的idx在哪
        int leftsize = idx - inStart;
        TreeNode* root = new TreeNode(root_val);
        root->left = traverse(preorder, preStart+1, preStart+leftsize, inorder, inStart, inStart+idx-1);
        root->right = traverse(preorder, preStart+1+leftsize,preEnd,inorder,inStart+1+leftsize, inEnd);

        return root;

    }
};

/*
[3,9,20,15,7] root left right
[9,3,15,20,7] left root right
*/

//
class Solution {
public:
    unordered_map<int, int> valtoindex;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i =0; i < inorder.size(); i++){
            valtoindex[inorder[i]] = i;//將inorder的索引直接用hash表存起來 方便快速找到index 不用for loop 每次都重新找
        }
        return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
    TreeNode* build(vector<int>& preorder, int prestart, int preend, vector<int>& inorder, int instart, int ineend){
        if(prestart > preend) return nullptr;

        int rootval = preorder[prestart];//根是誰
        int index = valtoindex[rootval]; //根在哪個index上

        int leftsize = index - instart; //每次的traverse左邊數組的長度為多長
        TreeNode* root = new TreeNode(rootval); //開始記錄每次build的節點
        root-> left = build(preorder, prestart+1, prestart+leftsize, inorder, instart, index-1);
        root->right = build(preorder, prestart+leftsize+1, preend,inorder, index+1, ineend);

        return root;

    }

};

/*
解題思路
要構造一個樹 通常是用分解問題的方法 去定義一個可以建立樹的函式 此函式需要一個return data type
找出節點 利用preprde第一項必為root特性 去利用每一項找出inoder內相對應的左跟右


这段代码的时间和空间复杂度如下：
时间复杂度：
在预处理阶段，需要遍历一遍中序遍历数组并将每个元素的值和索引存入 valtoindex 哈希表中，时间复杂度为 O(N)，其中 N 是节点数量。
在递归构建二叉树的过程中，每个节点都只会在递归调用中处理一次，每次递归调用都需要常数时间。因此，递归构建的时间复杂度为 O(N)，其中 N 是节点数量。
综上所述，总的时间复杂度为 O(N)。

空间复杂度：
valtoindex 哈希表用来存储中序遍历数组元素的值和索引，空间复杂度为 O(N)，其中 N 是节点数量。
递归调用栈的深度取决于二叉树的高度。在最坏情况下，二叉树是一个链式结构，高度为 N，因此递归调用栈的空间复杂度为 O(N)。
综上所述，总的空间复杂度为 O(N)。
*/
