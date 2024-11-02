/*
1000. Minimum Cost to Merge Stones
*/

// TC:O(n^2*k) SC:O(n^2*k) 可在優化空間到n^2
class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) return -1;  // 檢查合併是否可能, 假設最後的數字不動，那n-1 個就要形成k-1推 所以可以除去
        vector<int> presum(n+1);
        for(int i = 0; i < n; i++) {
            presum[i+1] = presum[i] + stones[i];
        }
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(k+1,-1)));
        function<int(int, int, int)> dfs = [&](int l, int r, int p) -> int {
            // 只有一堆
            if(p == 1) {
                return l == r ? 0 : dfs(l,r,k) + presum[r+1] - presum[l];
            }
            if(memo[l][r][p] != -1) return memo[l][r][p];

            int res = INT_MAX/2;
            for(int i = l; i < r; i += (k-1)) {
                res = min(res, dfs(l,i, 1) + dfs(i+1,r, p-1));
            }

            return memo[l][r][p] = res;
        };

        

        return dfs(0, n - 1, 1);
    }
};
