/*
919. Complete Binary Tree Inserter
*/

// TC:O(1) SC:O(n)
class CBTInserter {
    TreeNode* root;
    queue<TreeNode*> q;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        q.push(root);
        
        bool flag = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                TreeNode* node = q.front();
                
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);

                if(!node->left || !node->right){
                    flag = 1;
                    break;
                }
                else q.pop();
            }
            if(flag) break;
        }
    }
    
    int insert(int val) {
       
        TreeNode* node = q.front();
        if(node -> left == NULL){
            node->left = new TreeNode(val);
            q.push(node->left);
            return node->val;
        }
        else if(node->right == NULL){
            node->right = new TreeNode(val);
            q.push(node->right);
            q.pop();
            return node->val;
        }

        return -1;
    }
    
    TreeNode* get_root() {
        return root;
    }
};

/*
設計一個可以馬上找到要插入哪一點的完全二叉樹資料結構 並且可以立刻回傳他的root 
直接每次都用BFS 較花時間 乾脆在constructor就先找好要插入的點 並且如果他左右節點某點為空 就先不要pop他
之後insert時再考慮要不要pop
*/
