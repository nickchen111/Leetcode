/*
55. Jump Game
*/

//greedy TC:O(n) SC:O(1)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //貪心思想 遍歷整個數組 看最遠能走到哪
        //如果最遠走到的index跟不上遍歷過程就代表走不到
        //遍歷完後確認走到的點 >=終點
        int far = 0;
        for(int i = 0; i < nums.size(); i++){
            if(i > far) return false;
            far = max(far, i+ nums[i]);
        }

        return far >= nums.size()-1;
    }
};

//DP TC:O(n^2) SC:O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //dp 定義為 這個index能否走到取決於 前面是否有可走到的以及他可以走到的點是否超越或等於我
        int n = nums.size();
        vector<int> dp(n,0);
        dp[0] = true;
        for(int i = 1; i<n; i++){
            for(int j = i-1; j>=0; j--){
                if(dp[j] && j+nums[j]>= i) {
                    dp[i] = true; 
                    break;
                }
            }
        }

        return dp[n-1];
    }
};

//Diff TC:O(n) SC:O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //Diff 
        int n = nums.size();
        vector<int> diff(n+1,0);
        if(n == 1) return true;
        if(nums[0] == 0) return false;
        diff[1] +=1;
        if(nums[0]+1 <= n) diff[nums[0]+1] -=1;

        int reach = 0;
        for(int i = 1; i<n; i++){
            reach+=diff[i];
            if(reach == 0) continue;
            if(nums[i] != 0){
                if(i+1 <=n) diff[i+1]+=1;
                if(i+nums[i]+1 <=n) diff[i+nums[i]+1] -=1;
            }
        }
        

        return reach;
    }
};
