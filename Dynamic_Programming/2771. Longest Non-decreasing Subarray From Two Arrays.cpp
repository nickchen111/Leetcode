// TC:O(n) SC:O(1)
class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int cnt1 = 1, cnt2 = 1, ans = 1;
        for(int i = 1; i < n; i++) {
            int prev1 = cnt1 , prev2 = cnt2;
            if(nums1[i] >= nums1[i-1]) cnt1 = prev1 + 1;
            else cnt1 = 1;
            if(nums2[i] >= nums2[i-1]) cnt2 = prev2 + 1;
            else cnt2 = 1;
            if(nums1[i] >= nums2[i-1]) cnt1 = max(cnt1, prev2 + 1);
            if(nums2[i] >= nums1[i-1]) cnt2 = max(cnt2, prev1 + 1);
            ans = max({ans,cnt1, cnt2});
        }
        return ans;
        /*
        遞歸
        vector memo(n, vector<int>(2, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> int {
            if(i == 0) return 1;
            int &ret = memo[i][j];
            if(ret != -1) return ret;
            ret = 1;
            if (j) {
                if (nums2[i] >= nums1[i - 1]) ret = max(ret, dfs(dfs, i - 1, 0) + 1);
                if (nums2[i] >= nums2[i - 1]) ret = max(ret, dfs(dfs, i - 1, 1) + 1);
            } else { 
                if (nums1[i] >= nums1[i - 1]) ret = max(ret, dfs(dfs, i - 1, 0) + 1);
                if (nums1[i] >= nums2[i - 1]) ret = max(ret, dfs(dfs, i - 1, 1) + 1);
            }
            return ret;
        };
        int ans = 1;
        for(int i = 0; i < n; i++) {
            ans = max({ans, dfs(dfs, i, 0), dfs(dfs, i, 1)});
        }
        return ans;
        */
        /*
        遞推
        vector dp(n, vector<int>(2, 1));
        for(int i = 1; i < n; i++) {
            if(nums1[i] >= nums1[i-1]) dp[i][0] = dp[i-1][0] + 1;
            if(nums2[i] >= nums2[i-1]) dp[i][1] = dp[i-1][1] + 1;
            if(nums1[i] >= nums2[i-1]) dp[i][0] = max(dp[i][0], dp[i-1][1] + 1);
            if(nums2[i] >= nums1[i-1]) dp[i][1] = max(dp[i][1], dp[i-1][0] + 1);
            ans = max({ans, dp[i][0], dp[i][1]});
        }
        return ans;
        */
    }
};

/*
可以選擇nums1, nums2任意一個
怎知選哪個，一般來說比較暴力的方法是先選一個往前去比較一下可以組多長 那也就是前一個選的可以組多長 + 1 如果當下那個 >= 他的話
所以我們可以定義狀態
dp[i][j]  走到i為止以nums j 打頭 可組成的最長長度
*/

/*
基本型I
要你從兩個數組中挑相同index上的兩個數字之一 組成的第三個數組要盡量是non decreasing
最長可以多長
dp[i][0]相等於 截至i為止 在i的時候選擇 nums1 or nums2最長的subarray為多長 
那麼每次都要回頭比較 有沒有比前面兩個的某一個大 取最長的狀況
*/
