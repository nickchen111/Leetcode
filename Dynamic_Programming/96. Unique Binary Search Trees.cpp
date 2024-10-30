/*
96. Unique Binary Search Trees
*/

// 區間DP TC:O(n^3) SC:O(n^2) 遞推 + 遞歸
class Solution {
public:
    int numTrees(int n) { 
        int res = 0;
        vector<vector<int>> dp(n+2, vector<int>(n+2,1)); // 以某點當作中心 需要先知道 左邊小區間以及右邊小區間
        for(int i = n; i >= 1; i--) {
            for(int j = i; j <= n; j++) {
                dp[i][j] = 0;
                for(int k = i; k <= j; k++) {
                    dp[i][j] += dp[i][k-1]*dp[k+1][j];
                }
            }
        }

        return dp[1][n];
        // vector<vector<int>> memo(n+1, vector<int>(n+1));
        // function<int(int l, int r)> dfs = [&](int l, int r) -> int {
        //     if(l >= r) return 1;
        //     if(memo[l][r]) return memo[l][r];
        //     int ret = 0;
        //     for(int i = l; i <= r; i++) {
        //         ret += dfs(l,i-1) * dfs(i+1,r);
        //     }

        //     return memo[l][r] = ret;
        // };

        // for(int i = 1; i <= n; i++) {
        //     res += dfs(1,i-1)*dfs(i+1,n);
        // }

        return res;
    }
};

/*
1 - n 去湊出的BST 有多少種獨特的 BST
一個一個去看 左邊的點 左邊肯定只能放 x-1 他會有多少種放法? 比上 右邊有多少種放法 兩者相乘
*/


// DP
class Solution {
public:
    int numTrees(int n) {
        //DP
        vector<int> dp(n+1,0);
        dp[0] = 1;
        //計算出有n個節點狀態時可以有多少種組合 所以由小到大
        for(int i=1; i<=n; i++){
            for(int k=1; k<=i; k++){
                dp[i]+= dp[k-1]*dp[i-k];
            }
        }

        return dp[n];
    }
};

// Backtrack
class Solution {
public:
    int memo[20][20] = {0};
    int numTrees(int n) {
        
        return count(1, n);
    }
    int count(int lo, int hi){
        if(lo > hi) return 1; //代表為nullptr

        if(memo[lo][hi] != 0){
            return memo[lo][hi];
        }
        int ans = 0;
        for(int mid = lo; mid <= hi; mid++){// mid為root
            int left = count(lo, mid-1);
            int right = count(mid+1, hi);
            ans += left*right;
        }
        memo[lo][hi] = ans; //代表某lo 到hi 的排列可能性

        return ans;
    }
};

/*
解題思路：
此題為二叉搜索樹的構造 可利用bst特性以及構造的操作來解題
此題的核心為假設我設個數字為root 他左邊的可能性呈上右邊的可能性極為此root的答案
這裡就有一點遍歷的味道了 讓所有樹都可能成為root然後去探討左邊右邊的可能性
因為可能會有重複項 所以可以用備忘錄來記取答案 
1.定義備忘錄數組的大小
2.建立一個函式來數數 開始遍歷
*/
