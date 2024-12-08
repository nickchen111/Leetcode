/*
1799. Maximize Score After N Operations
*/

// TC:O(n^2 * 2^n + logC * 2^n)  SC:O(2^n)
class Solution {
public:
    int maxScore(vector<int>& nums) {
        auto gcd = [](auto &&gcd, int a, int b) -> int {
            return b == 0 ? a : gcd(gcd, b, a % b);
        };
        // 可以做n/2次操作 每次操作選兩個數字 然後 i次操作 * gcd(x,y) 求最大值 n = 7 可以窮舉
        int n = nums.size();
        vector<int> memo((1<<n), -1);
        auto dfs = [&](auto &&dfs, int status, int cnt) -> int {
            if(cnt == n/2+1) return 0;
            if(memo[status] != -1) return memo[status];
            int ret = 0;
            for(int i = 0; i < n; i++) {
                int num1 = 0;
                int num2 = 0;
                if(((status >> i) & 1) == 0) {
                    num1 = nums[i];
                    int new_status = status | (1 << i);
                    for(int j = 0; j < n; j++) {
                        if(((new_status >> j) & 1) == 0) {
                            num2 = nums[j];
                            ret = max(ret, dfs(dfs, new_status | (1<<j), cnt + 1) + gcd(gcd, num1, num2) * cnt);
                        }
                    }
                }
            }
            return memo[status] = ret;
        };
        return dfs(dfs, 0, 1);
    }
};
