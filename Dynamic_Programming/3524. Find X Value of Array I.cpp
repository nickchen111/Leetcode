// TC:O(n * k) SC:O(k)
class Solution {
    using ll = long long;
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        // 空間優化
        vector<ll> dp(k, 0);
        dp[nums[0] % k] = 1;
        vector<ll> ans(k, 0);
        ans[nums[0] % k] += 1;
        for (int i = 1; i < n; i++) {
            vector<ll> new_dp(k);
            new_dp[nums[i] % k] += 1;
            for (int j = 0; j < k; j++) {
                if (dp[j] > 0) {
                    int new_remainder = (j * (nums[i] % k)) % k;
                    new_dp[new_remainder] += dp[j];
                }
            }
            for (int j = 0; j < k; j++) {
                ans[j] += new_dp[j];
            }
            dp = new_dp;
        }
    
        return ans;
        /*
        vector dp(n, vector<ll>(k, 0));
        dp[0][nums[0] % k] = 1;
        vector<ll> ans(k, 0);
        ans[nums[0] % k] += 1;
        for (int i = 1; i < n; i++) {
            dp[i][nums[i] % k] += 1;
            for (int j = 0; j < k; j++) {
                if (dp[i-1][j] > 0) {
                    int new_remainder = (j * (nums[i] % k)) % k;
                    dp[i][new_remainder] += dp[i-1][j];
                }
            }
            for (int j = 0; j < k; j++) {
                ans[j] += dp[i][j];
            }
            
        }
        
        return ans;
        */
    }
};
