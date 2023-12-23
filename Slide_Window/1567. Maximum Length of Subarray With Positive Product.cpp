/*
1567. Maximum Length of Subarray With Positive Product
*/

// Greedy + Slide Wnidow: TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] == 0) continue;
            int j = i;
            int count = 0;
            int k = -1;
            while(j < n && nums[j] != 0){
                if(nums[j] < 0) count++;
                if(count % 2 == 0) res = max(res, j - i + 1);
                else if(k != -1){
                    res = max(res, j - k);
                }
                if(k == -1 && nums[j] < 0) k = j;
                
                j++;
            }

            if(j == n) break;
            i = j;
        }

        return res;
    }
};

// DP  TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> positive(n,0);
        vector<int> negative(n,0);
        positive[0] = nums[0] > 0 ? 1 : 0;
        negative[0] = nums[0] < 0 ? 1 : 0;
        int res = positive[0];
        for(int i = 1; i < n; i++){
            if(nums[i] == 0){
                positive[i] = 0;
                negative[i] = 0;
                continue;
            }
            else if(nums[i] > 0){
                positive[i] = positive[i-1] + 1;
                negative[i]= negative[i-1] > 0 ? negative[i-1] + 1:0;
            }
            else {
                positive[i] = negative[i-1] > 0 ? negative[i-1] + 1 : 0;
                negative[i] = positive[i-1] + 1;
            }
            res = max(res, positive[i]);
        }
        return res;
    }
};

/*
找到最長的subarray所有相乘會是正數
一個數組紀錄正數 一個紀錄負數
dp[i][0] 截至i為止他所能獲擁有的最長正數 or 負數長度 
1 -1  2 -1 3 3 -2 -3 2 2
*/


