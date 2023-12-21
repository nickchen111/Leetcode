/*
1289. Minimum Falling Path Sum II
*/

// Greedy + DP  TC:O(m*n*2) SC:O(n)
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n);
        //一開始的最小值是第一row各個col本身 
        for(int i = 0; i < n; i++){
            dp[i] = grid[0][i];
        }

        //各種回合
        for(int i = 1; i < m; i++){
            //也可以用排列 或者像這樣寫時間total就會是 m*(2n)
            int firstMin = INT_MAX;
            int secondMin = INT_MAX;
            int firstIdx = -1;
            int secondIdx = -1;
            for(int k = 0; k < n; k++){
                if(dp[k] <= firstMin){
                    secondMin = firstMin;
                    secondIdx = firstIdx;
                    firstMin = dp[k];
                    firstIdx = k;
                    
                }
                else if(dp[k] < secondMin){
                    secondMin = dp[k];
                    secondIdx = k;
                }
            }
            auto dp_tmp = dp;
            for(int j = 0; j < n; j++){
                if(j != firstIdx){
                    dp[j] = dp_tmp[firstIdx] + grid[i][j];
                }
                else dp[j] = dp_tmp[secondIdx] + grid[i][j];
            }
        }

        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            res = min(res, dp[i]);
        }

        return res;

    }
};

// 走迷宮型 TC:O(m*n*n) SC:O(n)
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n);
        //一開始的最小值是第一row各個col本身 
        for(int i = 0; i < n; i++){
            dp[i] = grid[0][i];
        }

        //各種回合
        for(int i = 1; i < m; i++){
            auto dp_old = dp;
            for(int j = 0; j < n; j++){
                dp[j] = INT_MAX;
                for(int k = 0; k < n; k++){
                    if(j != k){
                        dp[j] = min(dp[j], dp_old[k] + grid[i][j]);
                    }
                }
            }
        }

        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            res = min(res, dp[i]);
        }

        return res;

    }
};

/*
此題就是延續一的考題 但是往下掉的時候不能跟前一個在一樣的column
*/
