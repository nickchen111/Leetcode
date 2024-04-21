/*
3122. Minimum Number of Operations to Satisfy Conditions
*/

// TC:O(m*n) SC:O(10*n)
class Solution {
    int dp[1005][10]; // 走到某一column時 如果想將前面數字改成0-9最少需要多少操作次數
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < 1005; i++){
            for(int j = 0; j < 10; j++){
                dp[i][j] = INT_MAX/2;
            }
        }
        for(int j = 0; j < n; j++){
            vector<int> count(10);
            for(int i = 0; i < m; i++){
                count[grid[i][j]] += 1;
            }
            
            if(j == 0){
                for(int a = 0; a < 10; a++){
                    dp[j][a] = m - count[a];
                }
            }
            else {
                for(int a = 0; a < 10; a++){
                    for(int b = 0; b < 10; b++){
                        if(a != b){
                            dp[j][a] = min(dp[j][a], m - count[a] + (j-1 >= 0 ? dp[j-1][b] : 0));
                        }
                    }
                }
            }
            
        }
        
        int res = INT_MAX;
        for(int i = 0; i < 10; i++){
            res = min(res, dp[n-1][i]);
        }
        
        return res;
        
    }
};

/*
可任意改數字 變其他正數
目標
grid[i][j] == grid[i + 1][j] 相同
grid[i][j] != grid[i][j + 1] 不同
dp[1005][10]; // 走到某一column時 如果想將前面數字改成0-9最少需要多少操作次數
*/
