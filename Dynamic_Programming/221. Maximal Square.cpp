/*
221. Maximal Square
*/

class Solution {
    //迭代
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n));
        //可能會有些邊界條件 
        //要把char 轉成int 
        for(int i = 0; i<m; i++){
            dp[i][0] = matrix[i][0] - '0';
        }   

        for(int j = 0; j < n; j++){
            dp[0][j] = matrix[0][j] - '0';
        }      

        
        for(int i = 1; i<m ;i++){
            for(int j = 1; j<n; j++){
                if(matrix[i][j] == '1'){
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1],dp[i-1][j]))+1;
                }
                else dp[i][j] = 0;
            }
        }

        int res = INT_MIN;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                res = max(res, dp[i][j]);
            }
        }
        
        return res*res;
    }
};

/*
解題思路：
dp[i][j] 會從右下角開始 根據他的左邊 上面 左上取他的值 取決於min( dp[i-1][j] dp[i][j-1] dp[i-1][j-1]) 水桶效應 取三個中最小編長的才會確定是正方形
因為是求最大值所以要加一 加上自己 必須為1 最後算邊長的平方就是答案
tc: O(m*n) sc:O(m*n)
*/
