// TC:O(m * n * 3) SC:O(m * n * 3)
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, INT_MIN)));
        
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0) {
            dp[0][0][1] = 0;   
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 3; k++) {
                    if (dp[i][j][k] == INT_MIN) continue;
                    
                    vector<pair<int, int>> directions = {{0, 1}, {1, 0}};
                    for (auto [di, dj] : directions) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= m || nj >= n) continue;
                        
                        dp[ni][nj][k] = max(dp[ni][nj][k], 
                                          dp[i][j][k] + coins[ni][nj]);
                        
                        // 如果還能使用特殊能力且下一格是負數
                        if (k < 2 && coins[ni][nj] < 0) {
                            dp[ni][nj][k + 1] = max(dp[ni][nj][k + 1], 
                                                   dp[i][j][k]);
                        }
                    }
                }
            }
        }
        
        int res = INT_MIN;
        for (int k = 0; k < 3; k++) {
            res = max(res, dp[m-1][n-1][k]);
        }
        return res;
    }
};
