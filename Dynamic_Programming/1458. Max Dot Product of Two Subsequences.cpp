/*
1458. Max Dot Product of Two Subsequences
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        nums1.insert(nums1.begin(), -1);
        nums2.insert(nums2.begin(), -1);

        vector<vector<int>> dp(m+1, vector<int>(n+1,INT_MIN/2));
        dp[0][0] = 0;
        int res = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                dp[i][j] = max(nums1[i]*nums2[j],dp[i-1][j-1] + nums1[i]*nums2[j]);
                dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]));
            }
        }
        return dp[m][n];
    }
};

/*
給你兩個數組從裡面挑出一樣長的subsequence 兩兩相乘在加總後最大值為多少
雙序列型DP
dp[i][j]...
dp[i][j] = max(dp[i][j], )
i -> j 兩個都選 or 兩個都不選 dp[i-1][j-1] or 一個不選 dp[i-1][j], dp[i][j-1]
這題另外要注意負數情況 如果dp[i-1][j-1]反而拖累我 直接選nums1[i]*nums2[j]
*/
