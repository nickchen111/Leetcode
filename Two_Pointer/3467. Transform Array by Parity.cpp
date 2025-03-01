// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        int n = nums.size();
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(nums[i] % 2) {
                nums[i] = 1;
            }
            else {
                nums[i] = 0;
                swap(nums[i], nums[k++]);
            }
        }
        
        return nums;
    }
};
