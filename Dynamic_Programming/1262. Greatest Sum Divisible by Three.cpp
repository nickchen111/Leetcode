/*
1262. Greatest Sum Divisible by Three
*/

//TC:O(n) SC:O(n) 可優化空間
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(3,INT_MIN));
        nums.insert(nums.begin(),0);

        dp[0][0] = 0;//什麼都沒取的時候最大值
        for(int i = 1; i <= n; i++){
          int k = nums[i]%3;
          for(int j = 0; j < 3; j++){
            //這樣就是沒取跟有取比較
            dp[i][j] = max(dp[i-1][j],dp[i-1][(j-k+3)%3] + nums[i]);
          }
        }

      
        return dp[n][0];
    }
};


/*
此題題意為從數組中隨意選元素 加總能被3整除的最大值為多少
[3,6,5,1,8] -> [1 3 5 6 8]
Greedy: 被三整除三種可能 0 1 2 -> 0的全取 然後解數學方程 1*x + 2*y = 0
or total % 3== 0 , 1, 2 看要刪除誰的討論
or dp
乘除麻 要想到餘數
dp[i][j] the maximum possible sum(i%3 == j) in the first i element 
走到i的時候之最大值 是否要取 以及取了要跟前面誰配對會最大
*/
