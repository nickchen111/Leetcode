// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int io = 0;
        for(int &x : nums) {
            if(x % 2 == 0) {
                swap(x, nums[io]);
                io += 1;
            }
        }
        return nums;
    }
};
