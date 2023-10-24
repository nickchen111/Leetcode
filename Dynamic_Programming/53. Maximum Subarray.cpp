/*
53. Maximum Subarray
*/

//這題也可以用slide window & presum
//iterative TC:O(n)  SC:O(n)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        vector<int> dp(n);
        //初始化
        dp[0] = nums[0]; //dp數組的index就是nums的index

        int res = dp[0];
        for(int i = 1; i<n; i++){
            dp[i] = nums[i];
            dp[i] = max(dp[i], dp[i-1]+ nums[i]);
            res = max(res, dp[i]);
        }

        return res;



    }
};

//SC:O(1)
class Solution {
    //優化空間iterative
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        int dp_0 = nums[0];
        int dp_1 = 0;
        int res = nums[0];
        for(int i = 1; i<n; i++){
            dp_1 = max(dp_0+nums[i], nums[i]);
            res = max(res, dp_1);
            dp_0 = dp_1;
            dp_1 = 0;
        }

        return res;
    }
};

//recursion+memo TC:O(n)  SC:O(n)
class Solution {
    //recursion
    vector<int> memo;
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
       
        memo = vector<int> (n, INT_MIN);
        int res = nums[0];

        dp(nums, n-1);
        for(int i = 0; i<n; i++){
            res = max(res, memo[i]);
        }
        
        
        return res;
    }

    int dp(vector<int>& nums,  int index){
        int n = nums.size();
        if(index == 0) return nums[0];
        if(index < 0) return 0;
        
        if(memo[index] != INT_MIN) return memo[index];

        memo[index] = max(dp(nums, index-1)+nums[index], nums[index]);

  
        return memo[index];
    }
};

/*
此題有點類似LCS的含義 可以不斷加上前面數(必須是連續的) 來看有沒有比較大or 自己才是更大的
dp[i] = max(nums[i], dp[i-1]+nums[i])
*/
