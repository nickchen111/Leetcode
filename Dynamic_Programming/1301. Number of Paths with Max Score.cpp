/*
1301. Number of Paths with Max Score
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> dp(m, vector<int>(n,-1));
        vector<vector<int>> way(m, vector<int>(n,0));
        
        board[0][0] = '0';
        for(int i = m-1; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                if(board[i][j] == 'X') continue;
                if(i == m-1 && j == n-1){
                    way[i][j] = 1;
                    dp[i][j] = 0;
                    continue;
                }
                int down = -1, right = -1, diag = -1;
                if(i + 1 < m) down = dp[i+1][j];
                if(j + 1 < n) right = dp[i][j+1];
                if(i + 1 < m && j + 1 < n) diag = dp[i+1][j+1];

                dp[i][j] = max(down, max(right, diag));
                if(i+1 < m && dp[i][j] == down && down != -1) way[i][j] = (way[i+1][j] + way[i][j]) % M;
                if(j+1 < n && dp[i][j] == right && right != -1) way[i][j] = (way[i][j+1] + way[i][j]) % M;
                if(j+1 < n && i+1 < m && dp[i][j] == diag && diag != -1) way[i][j] = (way[i+1][j+1] + way[i][j]) % M;
                if(dp[i][j] != -1) dp[i][j] = (dp[i][j] + board[i][j]-'0') % M;
            }
        }

        return {dp[0][0] == -1 ? 0 : dp[0][0], way[0][0]};
        
    }
};

/*
從右下角走到左上 可以選擇走 left, up , left-up前提是沒遇到障礙物
回傳兩個數字 1. 走到終點的最大sum 2. 走到終點符合最大sum的走法
基本的走迷宮dp
"E12"
"1X1"
"21S"

"E11"
"XXX"
"11S"
*/
