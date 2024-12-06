/*
526. Beautiful Arrangement
*/

// TC : (n*2^n) SC:O(2^n)
class Solution {
public:
    int countArrangement(int n) {
        int res = 0;
        vector<int> memo(1 << (n+1), -1);
        auto dfs = [&](auto &&dfs, int status, int pos) -> int {
            if(pos == n+1) return 1;
            if(memo[status] != -1) return memo[status];
            int ret = 0;
            for(int i = 1; i <= n; i++) {
                if(((status >> i) & 1) == 0) {
                    if(i % pos == 0 || pos % i == 0) {
                        ret += dfs(dfs, status | (1 << i), pos + 1);
                    }
                }
            }

            return memo[status] = ret;
        };
        

        return dfs(dfs, 0, 1);
    }
};
