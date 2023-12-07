/*
865. Smallest Subtree with all the Deepest Nodes
*/


// TC:O(n) SC:O(n)
class Solution {
    int maxDepth = 0;
    int maxCount = 0;
    unordered_map<int,int> map; // val -> depth
    TreeNode* res = NULL;
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
      //先找最小的點所以需要先紀錄深度
      queue<TreeNode*> q;
      q.push(root);
      int count = -1;
      while(!q.empty()){
          int sz =q.size();
          count++;
          maxDepth = max(maxDepth, count);
          while(sz--){
            TreeNode* cur = q.front();
            q.pop();
            map[cur->val] = count;
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
          }
      }
      for(auto p:map){
        if(p.second == maxDepth) maxCount+=1;
      }

      DFS(root);
      return res;
    }

    int DFS(TreeNode* node){
      if(node == NULL) return 0;
      int self = (map[node->val] == maxDepth);
      int left = DFS(node->left);
      int right = DFS(node->right);
      if(self + left + right == maxCount && res == NULL)
        res = node;
      return self + left + right;
    }

};


//資料結構比較冗余的寫法
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
      //先找最小的點所以需要先紀錄深度
      vector<vector<TreeNode*>> depth;
      queue<TreeNode*> q;
      q.push(root);
      int count = -1;
      while(!q.empty()){
          int sz =q.size();
          count++;
          while(depth.size() <= count) depth.push_back({});
          while(sz--){
            TreeNode* cur = q.front();
            q.pop();
            depth[count].push_back(cur);
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
          }
      }
      int n = depth.size();
      unordered_set<TreeNode*> set(depth[n-1].begin(), depth[n-1].end());
      if(depth[n-1].size() == 1) return depth[n-1][0];
      else {
        findParent(set,root);
        return res;
      }
    }
    TreeNode* res = NULL;
    int sum = 0;
    int findParent(unordered_set<TreeNode*> set, TreeNode* root){
      if(root == NULL) return 0;
      if(set.find(root) != set.end()){
        return 1;
      }

      sum = findParent(set, root->left) + findParent(set, root->right);
      if(sum == set.size() && res == NULL){
        res = root;
      }

      return sum;
    }
};
