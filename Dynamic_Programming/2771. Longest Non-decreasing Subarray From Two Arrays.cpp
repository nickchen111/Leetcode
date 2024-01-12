/*
2771. Longest Non-decreasing Subarray From Two Arrays
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int res = 1;
        int n = nums1.size();
        int dp_1 = 1, dp_2 = 1;
        
        for(int i = 1; i < n; i++){
            auto dp_tmp_1 = dp_1, dp_tmp_2 = dp_2;
            dp_1 = 1, dp_2 = 1;
            if(nums1[i] >= nums2[i-1]){
                dp_1 = dp_tmp_2 + 1;
            }
            if(nums1[i] >= nums1[i-1]){
                dp_1 = max(dp_1, dp_tmp_1 + 1);
            }
            if(nums2[i] >= nums2[i-1]){
                dp_2 = dp_tmp_2 + 1;
            }
            if(nums2[i] >= nums1[i-1]){
                dp_2 = max(dp_2, dp_tmp_1 + 1);
            }
            res = max(res, max(dp_1,dp_2));
        }

        return res;
    }
};

// 未優化 TC:O(n) SC:O(n)
class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int res = 1;
        int n = nums1.size();
        vector<vector<int>> dp(n, vector<int>(2,1));
        dp[0][0] = 1;
        dp[0][1] = 1;

        for(int i = 1; i < n; i++){
            if(nums1[i] >= nums2[i-1]){
                dp[i][0] = dp[i-1][1] + 1;
            }
            if(nums1[i] >= nums1[i-1]){
                dp[i][0] = max(dp[i][0], dp[i-1][0] + 1);
            }
            if(nums2[i] >= nums2[i-1]){
                dp[i][1] = dp[i-1][1] + 1;
            }
            if(nums2[i] >= nums1[i-1]){
                dp[i][1] = max(dp[i][1], dp[i-1][0] + 1);
            }
            res = max(res, max(dp[i][0],dp[i][1]));
        }

        return res;
    }
};


/*
基本型I
要你從兩個數組中挑相同index上的兩個數字之一 組成的第三個數組要盡量是non decreasing
最長可以多長
dp[i][0]相等於 截至i為止 在i的時候選擇 nums1 or nums2最長的subarray為多長 
那麼每次都要回頭比較 有沒有比前面兩個的某一個大 取最長的狀況
*/
