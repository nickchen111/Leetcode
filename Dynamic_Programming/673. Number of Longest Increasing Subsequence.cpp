/*
673. Number of Longest Increasing Subsequence
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        vector<int> freq(n,1);


        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[j] >= nums[i]) continue;
                if(dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1;
                    freq[i] = freq[j];
                }
                else if(dp[j] + 1 == dp[i]){
                    freq[i] += freq[j];
                }
            }
        }

        int maxLen = 0;
        int res;
        for(int i = 0; i < n; i++){
            if(maxLen < dp[i]){
                maxLen = dp[i];
                res = freq[i];
            }
            else if(maxLen == dp[i]){
                res += freq[i];
            }
        }

        return res;
    }
};

/*
此題是LIS的延伸題 問你LIS會有幾種組合 
一個數組紀錄LIS長度 一個紀錄該長度在ith element之前總共有多少個
不算太難的LIS延伸 要想到用另一個數組紀錄長度即可
*/
