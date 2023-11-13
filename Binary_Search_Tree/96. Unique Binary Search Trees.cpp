/*
96. Unique Binary Search Trees
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
