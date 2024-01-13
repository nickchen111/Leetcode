/*
1028. Recover a Tree From Preorder Traversal
*/

// queue TC:O(n) SC:O(n)
class Solution {
    
public:
    TreeNode* recoverFromPreorder(string traversal) {
        //先做字符串處理 將深度取出
        queue<pair<int,int>> q;
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
            q.push({val, depth});
        }
        // 計算每一層的節點數量不包含自己 下面有多少個 可以讓我去避開這些節點找到右子樹的位置
        return DFS(q);
    }
    TreeNode* DFS(queue<pair<int,int>>& q){
        int cur  = q.front().first;
        int depth = q.front().second;
        q.pop();
        
        TreeNode* root = new TreeNode(cur);
        
        if(depth +1 == q.front().second){
            root->left = DFS(q);
        }
        if(depth +1 == q.front().second){
            root->right = DFS(q);
        }
        
        return root;
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
