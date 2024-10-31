/*
1770. Maximum Score from Performing Multiplication Operations
*/

// TC:O(n^2) SC:O(n^2) 遞推遞歸 
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size();
        int m = multipliers.size();

        // vector<vector<int>> memo(m+1, vector<int>(m+1, INT_MIN)); // l -> r : k  -> val
        // function<int(int l, int r, int k)> dfs = [&](int l, int r, int k) -> int{
        //     if(k == m) return 0;
        //     if(k == m-1) return max(multipliers[k] * nums[l], multipliers[k] * nums[r]);
        //     if(memo[l][n-r] != INT_MIN) return memo[l][n-r];
        //     int res = INT_MIN;
        //     res = max(dfs(l+1,r, k+1) + nums[l]*multipliers[k], dfs(l,r-1,k+1) + nums[r] * multipliers[k]);

        //     return memo[l][n-r] = res;
        // };

        // return dfs(0, n-1, 0);
        vector<vector<int>> dp(m+1, vector<int>(m+1, INT_MIN));
        dp[0][0] = 0;

        for(int j = 1; j <= m; j++) {
            dp[0][j] = dp[0][j-1] + multipliers[j-1] * nums[n-j];
            dp[j][0] = dp[j-1][0] + multipliers[j-1] * nums[j-1];
        }
        for(int i = 1; i <= m; i++) {
            for(int j = 1; i + j <= m; j++) {
                dp[i][j] = max(dp[i-1][j] + nums[i-1] * multipliers[i+j-1], dp[i][j-1] + nums[n-j] * multipliers[i+j-1]);
            }
        }

        int res = INT_MIN;
        for(int i = 0; i <= m; i++) {
            res = max(res, dp[i][m-i]);
        }

        return res;
    }
};

/*
dp[i][j] 走到i為止 用了m個最大值
可以判斷說 j用了幾個 跟目前的位置做減法，得知後面用了幾個
假設 j = 10 , 前面用了兩個, 後面就是用了7個
目前這個可以用在後面or用在前面 dp[i][j] 
*/
