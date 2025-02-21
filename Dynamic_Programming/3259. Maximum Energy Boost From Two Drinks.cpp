// TC:O(n) SC:O(1) 
class Solution {
    using LL = long long;
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        LL e1 = 0, e2 = 0, prevvA = 0, prevA = 0, prevvB = 0, prevB = 0;
        for(int i = 0; i < n; i++) {
            if(i >= 1) {
                prevvA = prevA, prevA = e1;
                prevvB = prevB, prevB = e2;
            };
            e1 = max(e1, prevvB) + (LL)energyDrinkA[i];
            e2 = max(e2, prevvA) + (LL)energyDrinkB[i];
        }
        return max(e1,e2);
        /*
        遞推
        vector dp(n+1, vector<LL>(2, 0));
        for(int i = 0; i < n; i++) {
            dp[i+1][0] = max(dp[i][0], i - 1 >= 0 ? dp[i-1][1] : 0) + energyDrinkA[i];
            dp[i+1][1] = max(dp[i][1], i - 1 >= 0 ? dp[i-1][0] : 0) + energyDrinkB[i];
        }
        return max(dp[n][0], dp[n][1]);
        */
        /*
        vector memo(n, vector<LL>(2, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> LL {
            if(i < 0) return 0;
            LL &ret = memo[i][j];
            if(ret != -1) return memo[i][j];
            if(j == 0) return ret = max(dfs(dfs, i-1, j), dfs(dfs, i - 2, 1)) + (LL)energyDrinkA[i];
            return ret = max(dfs(dfs, i - 1, j), dfs(dfs, i - 2, 0)) + (LL)energyDrinkB[i];
        };
        return max(dfs(dfs, n-1, 0), dfs(dfs, n-1, 1));
        */
    }
};

/*
狀態機
正在喝 (想轉 不想轉)
暫停狀態 (到A or B) 可以直接跳到i-2即可
*/
