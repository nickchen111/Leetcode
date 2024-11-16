/*
2458. Height of Binary Tree After Subtree Removal Queries
*/

// DFN序號 TC:O(n) SC:O(n)
const int MAXN = 100010;
// 下標示節點的值
int dfn[MAXN];
// 下標是dfn序號
int deep[MAXN]; // 每個序號的深度
int siz[MAXN]; //每個序號的子樹包含自己的數量
int maxl[MAXN]; // 根據deep數組從序號0開始到i有多少的深度
int maxr[MAXN]; // 根據deep數組從序號MAX+1到i有多少深度
int dfnCnt;
class Solution {
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        dfnCnt = 0;
        traverse(root, 0);
        
        // 左側最大深度
        for (int i = 1; i <= dfnCnt; i++) {
            maxl[i] = max(maxl[i - 1], deep[i]);
        }
        
        // 右側最大深度
        maxr[dfnCnt + 1] = 0;
        for (int i = dfnCnt; i >= 1; i--) {
            maxr[i] = max(maxr[i + 1], deep[i]);
        }
        
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int queryVal = queries[i];
            int leftMax = maxl[dfn[queryVal] - 1];
            int rightMax = maxr[dfn[queryVal] + siz[dfn[queryVal]]];
            ans[i] = max(leftMax, rightMax);
        }
        return ans;
    }
    // 遍歷樹，記錄 dfn, deep, size
    void traverse(TreeNode* node, int depth) {
        if (!node) return;
        int currentIndex = ++dfnCnt;
        dfn[node->val] = currentIndex;
        deep[currentIndex] = depth;
        siz[currentIndex] = 1;
        
        if (node->left) {
            traverse(node->left, depth + 1);
            siz[currentIndex] += siz[dfn[node->left->val]];
        }
        if (node->right) {
            traverse(node->right, depth + 1);
            siz[currentIndex] += siz[dfn[node->right->val]];
        }
    }
};


// TC:O(n) SC:O(n)
class Solution {
    unordered_map<int, int> node2depth; // 目前節點的層數
    unordered_map<int, int> node2CurDepth; // 當前點之後的最大子樹深度
    unordered_map<int, int> depth2node;  // 這個深度有多少節點
    unordered_map<int, vector<int>> node2max; // 當下層來說的節點可以往下的第一大深度與第二大深度紀錄
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        DFS(root, 0);
        int n = queries.size();
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            int cur = queries[i];
            int curDepth = node2depth[cur]; // 當前點層數
            int depth = node2CurDepth[cur]; // 當前點的最大深度
            // cout << curDepth << ' ' << node2max[curDepth][0] << ' ' << node2max[curDepth][1] << endl;
            if(node2max[curDepth][0] == depth && node2max[curDepth][1] != 0) res[i] = node2max[curDepth][1] + curDepth;
            else if(node2max[curDepth][0] == depth && node2max[curDepth][1] == 0) {
                if(depth2node[curDepth] > 1) res[i] = curDepth;
                else res[i] = curDepth - 1;
            }
            else res[i] = node2max[curDepth][0] + curDepth;
        }

        return res;
    }
    int DFS(TreeNode* node, int depth) {
        if(node == NULL) return 0;
        node2depth[node->val] = depth; // 紀錄當前點的深度
        depth2node[depth] += 1;
        int left = DFS(node->left, depth+1); // left tree depth
        int right = DFS(node->right, depth+1); // right tree depth

        if(node2max[depth].size() == 0) {
            if(left && right) {
                node2max[depth].push_back(max(left, right));
                node2max[depth].push_back(0);
            }
            else {
                node2max[depth].push_back(max(left, right));
                node2max[depth].push_back(0);
            }
        }
        else {
            if(max(left, right) > node2max[depth][0]) {
                node2max[depth][1] = node2max[depth][0];
                node2max[depth][0] = max(left, right);
            } 
            else if(max(left, right) == node2max[depth][0]) {
                node2max[depth][1] = max(left, right);
            }
            else {
                node2max[depth][1] = max(node2max[depth][1], max(left, right));
            }
        }
        node2CurDepth[node->val] = max(left, right); // 當前點之後的最大子樹深度

        return max(left, right) + 1; 
    }
};

/*
DFS 可以紀錄 目前節點深度， 這節點往下最多多深 還可以紀錄 跟我同層的節點有哪些
去對應到當下層數的第一大跟第二大去紀錄
*/
