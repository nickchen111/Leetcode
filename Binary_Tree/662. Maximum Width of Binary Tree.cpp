/*
662. Maximum Width of Binary Tree
*/

// TC:O(n) SC:O(w) 11/12
class Solution {
    using LL = long long;
public:
    int widthOfBinaryTree(TreeNode* root) {
        //找出每層最左邊最右邊元素 並且給他標號
        // BFS
        if(root == NULL) return 0;

        root->val=0;
        vector<TreeNode*> q;
        q.push_back(root);

        int res = 0;
        while(!q.empty()){
            int sz= q.size();
            res = max(res,q.back()->val - q[0]->val +1);
            
            vector<TreeNode*> p;
            vector<LL> vals;
            for(int i =0; i<sz; i++){
                TreeNode* cur = q[i];
                if(cur->left) {
                    p.push_back(cur->left);
                    vals.push_back((LL)cur->val*2+1);
                }
                if(cur->right) {
                    p.push_back(cur->right);
                    vals.push_back((LL)cur->val*2+2);
                }
            }
            if(!q.empty()){
                for(int i = 0; i<p.size(); i++){
                    p[i]->val = (int)(vals[i]-vals[0]);
                }
            }
            q = p;
        }
        
        return res;
    }
};

//
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
