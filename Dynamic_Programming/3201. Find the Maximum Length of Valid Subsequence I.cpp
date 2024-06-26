/*
3201. Find the Maximum Length of Valid Subsequence I
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr;
        int res = 0;
        int count0 = 0;
        int count1 = 0;
        for(auto x : nums){
            if((x%2) == 0) count0 ++;
            else count1 ++;
            arr.push_back(x%2);
        }
        
        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][arr[0]] = 1;
        for(int i = 1; i < n; i++){
            if(arr[i]){
                dp[i][0] = dp[i-1][0];
                dp[i][1] = max(dp[i][1], dp[i-1][0] + 1);
            }
            else {
                dp[i][1] = dp[i-1][1];
                dp[i][0] = max(dp[i][0], dp[i-1][1] + 1);
            }
            
            res = max(res, max(dp[i][0], dp[i][1]));
        }
        
        res = max(res, max(count0, count1));
        
        return res;
    }
};


// TC:O(n) SC:O(1)
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(2+1, vector<int>(2+1,0));
        
        int res = 1;
        for(int i = 0; i < n; i++){
            int mod = (nums[i] % 2);
            for(int j = 0; j < 2; j++){
                dp[j][mod] = dp[mod][j] + 1;
                res = max(res, dp[j][mod]);
            }
        }
        

        return res;
    }
};
