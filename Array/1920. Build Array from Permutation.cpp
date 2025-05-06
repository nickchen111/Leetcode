// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        /*
        index sorting!? 他在將數字做位置的轉換
        也就是index = 0 該位置要放nums[nums[0]] 的數字
        */
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) ans.emplace_back(nums[nums[i]]);
        return ans;
    }
};
