/*
283. Move Zeroes
*/

// 2025.01.30
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i0 = 0;
        for (int& x : nums) {
            if (x) {
                swap(x, nums[i0]);
                i0++;
            }
        }
    }
};

//TC:O(n) SC:O(1)
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        while(fast < nums.size()){
            if(nums[fast] != 0){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        for(; slow<nums.size(); slow++){
            nums[slow] = 0;
        }
    }
};
