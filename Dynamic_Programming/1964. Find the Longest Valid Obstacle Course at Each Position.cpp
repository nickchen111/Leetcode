// TC:O(nlgn) SC:O(1)
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& nums) {
        int n = nums.size(), ng = 0;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            int j = upper_bound(nums.begin(), nums.begin() + ng, nums[i]) - nums.begin();
            if(j == ng) {
                nums[ng] = nums[i];
                ng += 1;
                ans[i] = ng;
            }
            else {
                nums[j] = nums[i];
                ans[i] = j+1;
            }
        }
        return ans;
    }
};
