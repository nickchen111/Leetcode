/*
1027. Longest Arithmetic Subsequence
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        unordered_map<int, int> map;
        int offset = 500; // diff 負數 讓他變正數
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(1001,1));
        dp[0][0] = 1; // 只有一個數字 沒得選 差為0 len = 1
        
        int res = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                int diff = nums[i] - nums[j];
                dp[i][diff+offset] = dp[j][diff+offset] + 1;
                res = max(res, dp[i][diff+offset]);
               
            }
            
        }

        return res;
    }
};

/*
求等差的最長subsequeuce
n = 1000 可以接受n^2
每個點 i 跟他之前的人diff 以及其所能得到的最長長度 
dp[i][diff] = maxLen; 
*/
