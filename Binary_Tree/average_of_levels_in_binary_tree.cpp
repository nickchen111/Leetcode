/*
637. Average of Levels in Binary Tree
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. 
Answers within 10-5 of the actual answer will be accepted.
 
Example 1:有binary tree的架構 圖貼不上來
Input: root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
Hence return [3, 14.5, 11].

Example 2:
Input: root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]

Constraints:
The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
*/

//此題要去計算每一層的總和平均值
//人生好難
//binary tree 題型 可用bfs or dfs

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


 // Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 

//用bfs用queue
class Solution1 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(root == nullptr) return {};
        vector<double> result;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int n = q.size();
            long long sum = 0;
            for(int i = 0; i < n; i++){
            TreeNode* node = q.front();
            q.pop();
            sum += node->val;

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
            }
            result.push_back(sum*1.0/n);
        }
        return result;
    }
};


//第二種使用bfs的寫法 不用queue
class Solution2 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(root == nullptr) return {};
        vector<TreeNode*> cur, next;  //用queue就不分兩個 直接往一個塞 不過在算答案前要把這一層有幾個node先記錄起來
        cur.push_back(root);
        vector<double> result;

        while(!cur.empty()){//是否還有下一層
            long long sum = 0;
            for(auto &node:cur){ //一個一個node處理
            sum += node->val;
            if(node->left) next.push_back(node->left);
            if(node->right) next.push_back(node->right);
            }
            result.push_back(static_cast<double>(sum)/ cur.size());//這裡的cur數量還是維持在root 而不是left 跟right層
            
            cur.swap(next); //就只是兩個指標交換指
            next.clear();
        }
        return result;
    }
};


//用dfs   sum_count的index就是他的深度 儲存一個pair 一項是這一層的sum 一項是這一層總共幾個node
//概念即去用深度的方式搜尋然後用pair技術去儲存看到的每個node 根據depth去算sum跟有幾個node
class Solution3 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(root == nullptr) return {};
        vector<pair<long long, int>> sum_count;
        int depth;
        vector<double> result;
        preorder(root, 0, sum_count);

        for(const auto& p:sum_count){
            result.push_back(static_cast<double>(p.first)/p.second);
        }

        return result;



    }
    void preorder(TreeNode* root, int depth, vector<pair<long long, int>>& sum_count){
        if(root == nullptr) return;
        if(depth >= sum_count.size()) sum_count.push_back({0,0}); //因為要對他做初始化  在做post or 中間的order時要改成while
        sum_count[depth].first += root->val;
        ++sum_count[depth].second;
        preorder(root->left, depth+1, sum_count);
        preorder(root->right, depth+1, sum_count);
    }
};



