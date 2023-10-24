/*
35. Search Insert Position
*/


//TC:O(lgn) SC:O(1)
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right-left)/2;
            if(nums[mid] >= target){
                right = mid;
            }
            else left = mid+1;
        }
        if(nums[left] < target){
            return left+1;
        } 

        return left;
    }
};
