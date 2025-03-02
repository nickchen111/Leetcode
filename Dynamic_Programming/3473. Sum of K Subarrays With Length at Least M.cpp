// TC:O(n * k) SC:O(n)
class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        /*
        問說切割成k個 每一個至少要有ｍ長度 最大可以拿多少sum， m <= 3
        dp[i][j] 定義成走到i並且切割了j份 在滿足條件狀況下的最大值
        每個數字拿完該拿的以後會去考慮往前走到某個程度 如果該點之前還有可分組可能性 就取全部+他
        如何判定走到哪個程度就是本題難點 是否要去判斷每個點在之前的負數在哪
        f[i][j]= max(f[i][j−1],mx+presum[j])
        */
        int n = nums.size();
        vector<int> presum(n+1),dp(n+1);
        partial_sum(nums.begin(), nums.end(), presum.begin() + 1);
        for(int i = 1; i <= k; i++) {
            vector<int> ndp(n+1, INT_MIN/2);
            // 在這段區間的都是可以取的範圍
            int mx = INT_MIN;
            for(int j = i * m; j <= n - (k - i) * m; j++) {
                mx = max(mx, dp[j-m] - presum[j-m]);
                ndp[j] = max(ndp[j-1], mx + presum[j]); // 選 or 不選
            }
            dp = move(ndp);
        }
        
        return dp[n];
    }
};

