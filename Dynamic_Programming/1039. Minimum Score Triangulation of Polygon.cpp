/*
1039. Minimum Score Triangulation of Polygon
*/

// 遞歸 + 遞推 TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        // vector<vector<int>> memo(n, vector<int>(n,-1));
        // function<int(int l, int r)> dfs = [&](int l, int r) -> int {
        //     if(l == r || l + 1 == r) return 0;
        //     if(memo[l][r] != -1) return memo[l][r];

        //     int res = INT_MAX;
        //     for(int i = l+1; i < r; i++) {
        //         res = min(res, dfs(l,i) + dfs(i,r) + values[i] * values[l] * values[r]);
        //     }

        //     return memo[l][r] = res;

        // };
        // return dfs(0, n-1);

        vector<vector<int>> dp(n, vector<int>(n,0));
        for(int i = n-3; i >= 0; i--) {
            for(int j = i + 2; j < n; j++) {
                dp[i][j] = INT_MAX;
                for(int k = i+1; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + values[i] * values[k] * values[j]);
                }
            }
        }

        return dp[0][n-1];

    }
};

/*
n個頂點，一定拆出n-2個三角形
3 7 
4 5
*/
