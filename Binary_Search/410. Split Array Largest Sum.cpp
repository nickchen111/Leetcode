/*
410. Split Array Largest Sum
*/

// 2025.03.15  DP & 二分 TC:O(n*n*k) SC:O(n*k) & TC:O(nlgU) SC:O(1)
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        // 二分
        int left = *max_element(nums.begin(), nums.end());
        int right = reduce(nums.begin(), nums.end(), 0);
        auto check = [&](int mid) -> bool {
            int cnt = 0, i = 0;
            while (i < n) {
                int j = i, sum = 0;
                while(j < n && sum + nums[j] <= mid) {
                    sum += nums[j++];
                }
                cnt += 1;
                i = j;
            }
            return cnt <= k;
        };
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) right = mid;
            else left = mid + 1;
        }
        return left;
        /*
        遞推
        vector<int> presum(n+1);
        for(int i = 1; i <= n; i++) presum[i] = presum[i-1] + nums[i-1];
        vector dp(n+1, vector<int>(k+1, INT_MAX/2));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= min(i+1, k); j++) {
                for(int t = i; t >= 0; t--) {
                    dp[i+1][j] = min(dp[i+1][j], max(dp[t][j-1], presum[i+1] - presum[t]));
                }
            }
        }
        return dp[n][k];
        */
        /*
        遞歸 TC:O(n*n*k)
        vector memo(n, vector<int>(k+1, INT_MAX/2));
        auto dfs = [&](auto &&dfs, int i, int cnt) -> int {
            if(i < 0) return 0;
            if(cnt == 1) {
                return presum[i+1];
            }
            int &ret = memo[i][cnt];
            if(ret != INT_MAX/2) return ret;
            for(int j = i; j >= 0; j--) {
                ret = min(ret, max(dfs(dfs, j-1, cnt - 1), presum[i+1] - presum[j]));
            }
            return ret;
        };
        return dfs(dfs, n-1, k);
        */
    }
};



/*
此題跟 1011相同概念
不過這題是subarray 必須是連續的 但殊途同歸 一樣用貪心法一個一個裝進去 必定會得到解

dp解法：著眼於當前的點i 思考他跟其他人可以怎麼處理
dp[i][k] 0~i這些數字分成k個組 此組可以怎麼組有最小的subarray和
= dp[j][k-1] +  sum[j+1:i] ->跟其他某一派群聚
dp[i][k] = max(dp[i-1][k-1],nums[i]) -> 自成一派
*/
