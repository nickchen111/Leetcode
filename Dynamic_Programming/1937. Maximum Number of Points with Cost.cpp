/*
1937. Maximum Number of Points with Cost
*/

// TC:O(m*n) SC:O(n) 
class Solution {
    using LL = long long;
public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size();
        int n = points[0].size();
        vector<LL> dp(n);
        for(int i = 0; i < m; i++){
            vector<LL> nextDp(n);
            vector<LL> leftMax(n);
            vector<LL> rightMax(n);
            leftMax[0] = dp[0];
            rightMax[n-1] = dp[n-1];

            for(int j = 1; j < n; j++){
                leftMax[j] = max(leftMax[j-1] - 1, dp[j]);
            }
            for(int j = n-2; j >= 0; j--){
                rightMax[j] = max(rightMax[j+1]-1, dp[j]);
            }

            for(int j = 0; j < n; j++){
                nextDp[j] = points[i][j] + max(leftMax[j], rightMax[j]);
            }
            dp = nextDp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};

// Memo + DFS  TC:O(m*n^2) SC:O(n^2)
class Solution {
    using LL = long long;
    vector<vector<int>> points;
    int m, n;
    vector<vector<int>> memo;
    LL res = 0;
public:
    long long maxPoints(vector<vector<int>>& points) {
        this -> points = points;
        m = points.size();
        n = points[0].size();
        memo.resize(m, vector<int>(n,-1));

        for(int j = 0; j < n; j++){
            res = max(res, dp(0, j));
        }

        return res;
    }
    LL dp(int row, int col){
        if(row == m){
            return 0;
        }
        if(memo[row][col] != -1) return memo[row][col];
        
        LL maxVal = points[row][col];
        LL bestStrategy = 0;

        for(int j = 0; j < n; j++){
            bestStrategy = max(bestStrategy, dp(row+1, j) - abs(col-j));
        }

        return memo[row][col] = bestStrategy + maxVal;
    }
};
