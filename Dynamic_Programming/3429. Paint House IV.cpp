// TC:O(4^2 * n * k^2) k = 3 SC:O(n * k^2)
class Solution {
    using LL = long long;
public:
    long long minCost(int n, vector<vector<int>>& cost) {
        // 必須跟隔壁不同色 並且我equidistant位置也不同
        vector<vector<vector<LL>>> memo(n/2+1, vector<vector<LL>>(4, vector<LL>(4, -1))); // 走到n 他的對面選的顏色 與我選的顏色是多少
        auto dfs = [&](auto &&dfs, int i, int j, int k) -> LL {
            if(i == n/2) return 0;
            if(memo[i][j][k] != -1) return memo[i][j][k];
            LL ret = LLONG_MAX;
            for(int t = 0; t < 3; t++) {
                if(t == j) continue;
                for(int v = 0; v < 3; v++) {
                    if(v == t || v == k) continue;
                    ret = min(ret, dfs(dfs, i+1, t, v) + (LL)cost[i][t] + (LL)cost[n-i-1][v]);
                }
            }

            return memo[i][j][k] = ret;
        };

        return dfs(dfs, 0, 3, 3);
    }
};
