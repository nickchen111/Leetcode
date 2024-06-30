/*
3202. Find the Maximum Length of Valid Subsequence II
*/

// TC:O(n^2) SC:O(k*n)
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        nums.insert(nums.begin(), -1);
        vector<vector<int>> dp(n+1, vector<int>(k,1));//走到i mod是 k最長序列為多少
        
        
        int res = 1;

        for(int i = 2; i <= n; i++){
            for(int j = i-1; j >= 1; j--){
                int mod = (nums[i] + nums[j]) % k;
                dp[i][mod] = max(dp[i][mod], dp[j][mod] + 1);
                res = max(res, dp[i][mod]);
            }
        }

        return res;

    }
};

/*
x x x x x x 
[1,2,3,10,2] -> 3
*/
