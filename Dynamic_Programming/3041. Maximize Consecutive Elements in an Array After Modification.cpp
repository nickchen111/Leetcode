/*
3041. Maximize Consecutive Elements in an Array After Modification
*/

// TC:O(n) SC:O(2*n)
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        int res = 1;
        sort(nums.begin(), nums.end());
        vector<vector<int>> dp(n,vector<int>(2,1));

        for(int i = 1; i < n; i++){
            if(nums[i] - nums[i-1] == 2){
                dp[i][0] = dp[i-1][1] + 1;
            }
            else if(nums[i] - nums[i-1] == 1){
                dp[i][1] = dp[i-1][1] + 1;
                dp[i][0] = dp[i-1][0] + 1;
            } 
            else if(nums[i] == nums[i-1]){
                dp[i][1] = dp[i-1][0] + 1;
                dp[i][0] = dp[i-1][0];
            }

            res = max(res, max(dp[i][0], dp[i][1]));
        }

        return res;
    }
};

/*
每項元素只能加一 問說最多可以有連續多長的數組
1. sort
2. 這題的突破點在於要看出 這是一道dp題 因為 我走到i的長度取決於我跟先前數字的關係
x x x x a b
dp[i][0 or 1]. 0代表沒有自增1 1 代表有
b-a == 2 
dp[i][0] = dp[i-1][1] + 1;
b-a == 1
dp[i][1] = dp[i-1][1] + 1;
dp[i][0] = dp[i-1][0] + 1;

b-a == 0
dp[i][1] = dp[i-1][0] + 1;
dp[i][0] = dp[i-1][0];
*/
