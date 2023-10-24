/*
377. Combination Sum IV
*/

//backtrack TC:O(2^target) SC:O(2^target)
class Solution {
    vector<vector<int>> res;
    vector<int> track;
    //可重複選 排列組合算多種 有目標總和
public:
    int combinationSum4(vector<int>& nums, int target) {
        backtrack(nums,target,0);

        return res.empty() ? 0:(int)res.size();
    }

     void backtrack(vector<int>& nums, int target, int sum){
         if(sum > target) return;
         if(sum == target){
            res.push_back(track);
            return;
         }

         for(int i = 0; i<nums.size(); i++){
            sum+=nums[i];
            track.push_back(nums[i]);
            backtrack(nums,target,sum);
            sum-=nums[i];
            track.pop_back();
         }
     }
};

//DP TC:O(n) SC:O(n)
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //dp定義為 可以滿足到達成target的組合有多少種 如果最後放入的是某個數字為突破口
        vector<unsigned int> dp(target+1,0);
        dp[0] = 1;
        for(int sum=1; sum<=target; sum++){
            for(int x:nums)
                if(sum-x>=0) dp[sum] +=dp[sum-x];
        }

        return dp[target];
    }
};
/*
處理溢出的方式有兩種
1.取% 1e9+7
2.用unsigned int 溢出時會自動循環
*/
