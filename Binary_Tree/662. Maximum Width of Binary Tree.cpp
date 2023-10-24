/*
662. Maximum Width of Binary Tree
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    struct dataNode{
        TreeNode* node;
        unsigned long long index;
        dataNode(TreeNode* node, int index){
            this->node = node;
            this->index = index;
        }
    };
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr) return 0;

        queue<dataNode> q;
        q.push(dataNode(root, 0));
        unsigned long long maxwidth = 0;
        unsigned long long headIndex = -1;
        unsigned long long tailIndex = -1;

        while(!q.empty()){
            int size = q.size();

            for(int i = 0; i < size; i++){
                dataNode datanode = q.front(); q.pop();
                TreeNode* node = datanode.node;
                long index = datanode.index;

                if(i == 0){
                    headIndex = index;
                }

                tailIndex = index;//每次都會變 總有一次是最大的那項
                if(node ->left != nullptr){
                    q.push(dataNode(node->left, 2*index));
                }
                if(node->right != nullptr){
                    q.push(dataNode(node->right, 2*index+1));
                }

                maxwidth = max(maxwidth, tailIndex-headIndex+1);
            }
        }

        return maxwidth;        
    }
};

/*
解題思路：
看起來很適合bfs 但這題其實有給一個提示full binary tree --> complete binary tree有個觀念 heap i->2i, 2i+1
可以給元素編號 那只要在每一層去編號左邊跟右邊元素 兩個相減就是這層的最大值
tc: o(n) sc:o(n)
*/
