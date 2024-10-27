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


// Presum 做法 TC:O(min(m,n)*m*n) SC:O(m*n)
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(); 
        int n = matrix[0].size();
        vector<vector<int>> presum(m+1, vector<int>(n+1));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                presum[i+1][j+1] = presum[i][j+1] + presum[i+1][j] - presum[i][j] + matrix[i][j];
            }
        }

        int res = 0;
        for(int len = 1; len <= min(m,n); len++) {
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(i+1-len >= 0 && j+1-len >= 0) {
                        if(presum[i+1][j+1] - presum[i+1][j+1-len] - presum[i+1-len][j+1] + presum[i+1-len][j+1-len] == len*len) res += 1;
                    }
                }
            }
        }
        

        return res;
    }
};

/*
此題問一個matrix中 包含了多少個正方形
0 1 0
0 1 0
1 1 1
1 1 0
*/
