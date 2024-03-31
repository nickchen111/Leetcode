/*
3101. Count Alternating Subarrays
*/


// TC:O(n) SC:O(n)-> O(1)
class Solution {
    using LL = long long;
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<vector<LL>> dp(n, vector<LL>(2));
        LL res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] == 0){
                dp[i][0] = 1;
                if(i-1 >= 0 && nums[i] != nums[i-1]){
                    dp[i][0] += dp[i-1][1];
                }
                res += dp[i][0];
            }
            else if(nums[i] == 1){
                dp[i][1] = 1;
                if(i-1 >= 0 && nums[i] != nums[i-1]){
                    dp[i][1] += dp[i-1][0];
                }
                res += dp[i][1];
            }
        }
        
        return res;
    }
};

/*
如果subarray旁邊數字都跟他不同 就可以是合法 問有多少這種subarray
dp ?!
裡面只會有0or1
[1,0,1,0] -> 1, 1+1, 1+2, 1+3 =. 1 +2 + 3 +4
*/
