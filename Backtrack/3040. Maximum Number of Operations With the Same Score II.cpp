/*
3040. Maximum Number of Operations With the Same Score II
*/

// TC:On^2) n = 2000 SC:O(n^2) 因為有記憶化所以可以說每次的選擇假設都走到最後那麼每一圈大致上都只會走n 所以會是n^2
class Solution {
    int res = 1;
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        int a = nums[0] + nums[1];
        int b = nums[0] + nums[n-1];
        int c = nums[n-1] + nums[n-2];
        bool flag1 = 1, flag2 = 1, flag3 = 1;
        
        while(true){
            vector<vector<bool>> memo(2001,vector<bool>(2001));
            if(flag1) {
                backtrack(nums, 2,n-1,a,1, memo);
                flag1 = 0;
            }
            
            else if(flag2){
                 backtrack(nums, 1,n-2,b,1, memo);
                 flag2 = 0;
            }
            else if(flag3){
                backtrack(nums, 0,n-3,c,1, memo);
                flag3 = 0;
            }
            if(flag1 == 0 && flag2 == 0 && flag3 == 0) break;
        }
        
        return res;
    }
    
    void backtrack(vector<int>& nums, int start, int end, int target, int count, vector<vector<bool>>& memo){
        if(start >= end){
            res = max(res, count);
            return;
        }
        
        if(memo[start][end]) return;
        
        res = max(res, count);
        if(start + 1 <= end){
            if(nums[start] + nums[start+1] == target){
                backtrack(nums, start+2, end, target, count+1, memo);
            }
        }
        if(nums[start] + nums[end] == target){
            backtrack(nums, start+1, end-1, target, count+1, memo);
        }
        if(end-1 > start && nums[end] + nums[end-1] == target){
            backtrack(nums, start, end-2, target, count+1, memo);
        }
        
        memo[start][end] = 1;
    }
};

/*
這題跟3038差別在改為 可以前面選兩個 or 後面選兩 or 前後各選一個 問說怎麼選可以選最多次 讓每次選擇的兩個數字總和相同
n = 2000
nums[i] <= 1000
4*10^6 n^2是可以的
有點像區間型dp
dp[i][j][?] 區間 i~j 分數段是nums[i] + nums[j] 為主的可能性可以拼湊出的狀態
 x x x x x x 
 [1,9,7,3,2,7,4,12,2,6]
 有點像遞歸 給三種選項 然後再從剩下的可能性最多的可能
*/
