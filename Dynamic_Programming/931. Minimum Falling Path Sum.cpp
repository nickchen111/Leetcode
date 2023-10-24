/*
931. Minimum Falling Path Sum
*/


//recusion+memo
class Solution {
    vector<vector<int>> memo;
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        memo = vector<vector<int>>(n, vector<int>(n,66666));
        

        int res = INT_MAX;
        for(int j = 0; j < n; j++){
            res = std::min(res, dp(matrix, n-1, j));
        }

        return res;
    }

    int dp(vector<vector<int>>& matrix, int i, int j){
        int n = matrix.size();
        if(i < 0 || j < 0 || i == n || j == n) return 99999;//一個不可能被選中的數字

        if(i == 0) return matrix[0][j]; //代表抵達起點 row上
        if(memo[i][j] != 66666) return memo[i][j];

        memo[i][j] = min(
            dp(matrix, i-1,j),//往上
            dp(matrix, i-1,j-1), //往左上
            dp(matrix, i-1,j+1) //往右上
        )+ matrix[i][j];
      

        return memo[i][j];
    }

    int min(int a, int b, int c){
        return std::min(a, std::min(b,c));
    }
};


class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        //iterative
        int n = matrix.size();
        //dp定義為目前走到這點所需的最短路徑
        vector<vector<int>> dp(n, vector<int>(n));
        
        //初始化
        for(int i = 0; i < n; i++){
            dp[0][i] = matrix[0][i];
        }

        for(int i = 1; i<n; i++){
            for(int j = 0; j < n; j++){
                dp[i][j] = dp[i-1][j]; //往上
                if(j-1 >= 0) dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
                if(j+1 < n) dp[i][j] = min(dp[i][j], dp[i-1][j+1]);
                dp[i][j] += matrix[i][j];
            }
        }

        int res = INT_MAX;
        for(int i = 0; i<n; i++){
            res = min(res, dp[n-1][i]);
        }

        return  res;
    }
};

/*
從第一row出發到最後一row 只能往下或是左下右下走
求最短路徑和
1. iterative
tc: O(n^2) sc:O(n^2)
注意邊界狀況 給他設下條件式判斷即可避免走出界
2.recursion從終點出發
tc: O(n^2) sc:O(n^2)
*/
