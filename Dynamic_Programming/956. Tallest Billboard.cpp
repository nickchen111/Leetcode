/*
956. Tallest Billboard
*/

// 遞歸 + 遞推
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        int sum = reduce(rods.begin(),rods.end(), 0);
        int offset = sum;
        vector<int> dp(sum*2+1, INT_MIN);
        dp[offset] = 0;
        // TC:O(sum*n) SC:O(sum)

        for(int i = 0; i < n; i++) {
            auto dp_tmp = dp;
            for(int j = sum*2; j >= 0; j--) {
                if(j - rods[i] >= 0 && dp_tmp[j - rods[i]] != INT_MIN) {
                    dp[j] = max(dp[j], dp_tmp[j-rods[i]]);
                }
                if(j + rods[i] <= sum*2 && dp_tmp[j + rods[i]] != INT_MIN) {
                    dp[j] = max(dp[j], dp_tmp[j + rods[i]] + rods[i]);
                }
            }
        }

        return dp[offset];
        /*
        遞推 TC:O(sum*n) SC:O(sum*n)
        vector<vector<int>> dp(n+1, vector<int>(sum*2+1, INT_MIN)); // 差值為i 得到的最大left是多少
        dp[0][offset] = 0;

        for(int i = 0; i < n; i++) {
            for(int j = sum*2; j >= 0; j--) {
                dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
                if(j - rods[i] >= 0 && dp[i][j - rods[i]] != INT_MIN) {
                    dp[i+1][j] = max(dp[i+1][j], dp[i][j-rods[i]]);
                }
                if(j + rods[i] <= sum*2 && dp[i][j + rods[i]] != INT_MIN) {
                    dp[i+1][j] = max(dp[i+1][j], dp[i][j + rods[i]] + rods[i]);
                }
            }
        }

        return dp[n][offset];
        */
        /*
        遞歸 TC:O(n*sum*sum/4) SC:O(n*sum*sum/4)
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(sum/2+1, vector<int>(sum/2+1, -1)));
        function<int(int i, int left, int right)> dfs = [&](int i, int left, int right) -> int {
            if(i < 0) {
                return left - right == 0 ? left : 0;
            }
            if(left > sum/2 || right > sum/2) return 0;

            if(memo[i][left][right] != -1 ) return memo[i][left][right];
            return memo[i][left][right] = max({dfs(i-1, left + rods[i], right), dfs(i-1, left, right + rods[i]), dfs(i-1, left, right)});
        };

        return dfs(n-1, 0, 0);
        */
    }
};
