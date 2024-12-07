/*
1879. Minimum XOR Sum of Two Arrays
*/

// TC : (n*2^n) SC:O(2^n)
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> memo((1<<n), -1);
        auto dfs = [&](auto &dfs, int status, int idx) -> int{
            if(idx == n) return 0;
            if(memo[status] != -1) return memo[status];
            int ret = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(((status >> i) & 1) == 0) {
                    ret = min(ret, dfs(dfs, status | (1 << i), idx+1) + (nums1[idx]^nums2[i]));
                }
            }

            return memo[status] = ret;
        };
        return dfs(dfs, 0, 0);
    }
};
/*
可以重新排列nums2 讓兩者之間XOR sum最小
n = 14 代表可以暴力 並且如果某個狀態的status 已經走過了那麼後續應該不用走?! 直接取最小
*/
