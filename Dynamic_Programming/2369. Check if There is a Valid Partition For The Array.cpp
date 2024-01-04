/*
2369. Check if There is a Valid Partition For The Array
*/

// TC:O(n) SC:O(12)
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), -1);
        int dp_prev0 = 1, dp_prev1 = 1, dp_prev2 = 1; // 0位
        int dp_0 = 0, dp_1 = 0, dp_2 = 0; // 1位
        int dp_p0 = (nums[1] == nums[2]), dp_p1 = 0, dp_p2 = 0; // 2位數字狀態
        if(n == 2) return dp_p0;
        int dp_cur0 =  -1, dp_cur1 = -1, dp_cur2 = -1; // cur
        for(int i = 3; i <= n; i++){
            dp_cur0 = 0, dp_cur1 = 0, dp_cur2 = 0;
            if(nums[i] == nums[i-1] && (dp_0 == 1 || dp_1 == 1 || dp_2 == 1)) dp_cur0 = 1;
            // 三位以前的狀態
            if((nums[i] == nums[i-1] && nums[i-1] == nums[i-2] && (dp_prev0 == 1 || dp_prev1 == 1 || dp_prev2 == 1))){
                dp_cur1 = 1;
            }
            if(nums[i]-1 == nums[i-1] && nums[i-1]-1 == nums[i-2] && (dp_prev0 == 1 || dp_prev1 == 1 || dp_prev2 == 1)){
                dp_cur2 = 1;
            } 
            
            dp_prev0 = dp_0;  dp_prev1 = dp_1;  dp_prev2 = dp_2;
            dp_0 = dp_p0; dp_1 = dp_p1; dp_2 = dp_p2;
            dp_p0 = dp_cur0; dp_p1 = dp_cur1; dp_p2 = dp_cur2;
        }

       
        return (dp_cur0 || dp_cur1 || dp_cur2);
    }
};

// 
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), -1);
        vector<vector<int>> dp(n+1, vector<int>(3,0));
        for(int j = 0; j < 3; j++){
            dp[0][j] = 1;
        }
        for(int i = 2; i <= n; i++){
            if(nums[i] == nums[i-1] && (dp[i-2][0] == 1 || dp[i-2][1] == 1 || dp[i-2][2] == 1)) dp[i][0] = 1;
            if(i >= 3){
                if((nums[i] == nums[i-1] && nums[i-1] == nums[i-2] &&(dp[i-3][0] == 1 || dp[i-3][1] == 1 || dp[i-3][2] == 1))){
                    dp[i][1] = 1;
                }
                if(nums[i]-1 == nums[i-1] && nums[i-1]-1 == nums[i-2] && (dp[i-3][0] == 1 || dp[i-3][1] == 1 || dp[i-3][2] == 1)){
                    dp[i][2] = 1;
                } 
            }
        }

        for(int i = 0; i < 3; i++){
            if(dp[n][i] == 1) return true;
        }
        return false;
    }
};

/*
切割array 
所有subarray符合以下其中條件    
1. 兩個相同元素
2. 三個相同元素
3.元素之間只差1 且長度至少3
dp[i]代表走到某段是否合法 [j] 0 : 之前是否符合2個相同元素 1 : 之前是否符合3個相同元素 2 : 前三個是否符合3個遞增1元素
走到2的時候會先判斷是否 nums[i] == nums[i-1] 走到三 (nums[i] == nums[i-1] && dp[i-2][0 or 1 or 2] = 1) dp[i][1] = 1;
走到三的遞增 
    if(nums[i]-1 == nums[i-1] && nums[i-1]-1 == nums[i-2] && dp[i-2][0 or 1 or 2] = 1){
        dp[i][2] = 1;
    } 

*/

