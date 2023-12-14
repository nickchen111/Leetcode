/*
1277. Count Square Submatrices with All Ones
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n,0));
        int res = 0;
        for(int i = 0; i < m; i++){
            if(matrix[i][0] == 1) dp[i][0] = 1;
            res += dp[i][0];
        }
        for(int j = 1; j < n; j++){
            if(matrix[0][j] == 1) dp[0][j] = 1;
            res += dp[0][j];
        }

        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                if(matrix[i][j] == 1){
                    dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
                    res += dp[i][j];
                }
            }
        }

        return res;
    }
};

/*
此題問一個matrix中 包含了多少個正方形
if(matrix[i][j] == 1){
    dp[i][j] += dp[i-1][j-1];
}
0 1 0
0 1 0
1 1 1
1 1 0
*/
