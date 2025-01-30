// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int ie = 0;
        int io = 1;
        int n = nums.size();
        while(io < n && ie < n) {
            swap(nums[io], nums[ie]);
            if(nums[io] % 2) io += 2;
            if((nums[ie] % 2) == 0) ie += 2;
        }
        return nums;
    }
};
