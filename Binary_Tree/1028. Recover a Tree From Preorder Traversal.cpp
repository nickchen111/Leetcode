/*
1028. Recover a Tree From Preorder Traversal
*/

// Stack iterate 
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        int n = traversal.size();
        vector<TreeNode*> stack;
        for(int i = 0; i < n; i++) {
            int j = i;
            while(j < n && traversal[j] == '-') j += 1;
            int depth = j - i;
            int val = 0;
            while(j < n && isdigit(traversal[j])) val = val*10 + (traversal[j++] - '0');
            while(stack.size() > depth) stack.pop_back();
            TreeNode* node = new TreeNode(val);
            if(!stack.empty()) {
                if(!stack.back()->left) stack.back()->left = node;
                else stack.back()->right = node;
            }
            stack.push_back(node);
            i = j - 1;
        }
        return stack[0];
    }
};

// queue TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        queue<pair<int,int>> q;
        int n = traversal.size();
        for(int i = 0; i < n; i++) {
            int j = i;
            while(j < n && traversal[j] == '-') j += 1;
            int depth = j - i;
            int val = 0;
            while(j < n && isdigit(traversal[j])) val = val*10 + (traversal[j++] - '0');
            q.push({val, depth});
            i = j - 1;
        }

        auto dfs = [&](auto &&dfs, queue<pair<int,int>>& q) -> TreeNode* {
            int depth = q.front().second, val = q.front().first;
            q.pop();
            TreeNode* node = new TreeNode(val);
            if(!q.empty() && q.front().second == depth + 1) {
                node -> left = dfs(dfs, q);
            }
            if(!q.empty() && q.front().second == depth + 1) {
                node -> right = dfs(dfs, q);
            }
            return node;
        };
        return dfs(dfs, q);
    }
};

// TC:O(n) SC:O(n) DFS計算子數節點個數
class Solution {
    vector<pair<int,int>> nodes;
public:
    TreeNode* recoverFromPreorder(string traversal) {
        //先做字符串處理 將深度取出
        for(int i = 0; i < traversal.size(); i++){
            int j = i;
            while(j < traversal.size() && traversal[j] == '-'){
                j++;
            }  
            int depth = j-i;
            i = j;
            while(j < traversal.size() && isdigit(traversal[j])){
                j++;
            }
            int val = stoi(traversal.substr(i,j-i));
            i = j - 1;
            nodes.push_back({val, depth});
        }
        int num = 0; // 計算每一層的節點數量不包含自己 下面有多少個 可以讓我去避開這些節點找到右子樹的位置
        return DFS(0, num);
    }
    TreeNode* DFS(int cur, int& num){
        
        TreeNode* root = new TreeNode(nodes[cur].first);
        int leftNum = 0, rightNum = 0;
        if(cur+1 < nodes.size() && nodes[cur].second + 1 == nodes[cur+1].second){
            root->left = DFS(cur+1, leftNum);
        }
        if(cur + leftNum + 1 < nodes.size() && nodes[cur].second + 1 == nodes[cur + leftNum + 1].second){
            root->right = DFS(cur+leftNum+1, rightNum);
        }
        
        num = leftNum + rightNum + 1;
        return root;
    }
};

/*
此題給你一串字串 按照先敘方式排好並且 用---數量表示某個數字所在深度 並且這題說每個節點如果有child必定從左邊開始
所以可以確定唯一樹結構
要你重構出樹 
1 2 3 4 5 6 7
*/
