/*
398. Random Pick Index
*/

//TC:O(n) SC:O(1)
class Solution {
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int k = 0;
        int x;

        for(int i = 0; i<nums.size(); i++){
            if(nums[i] != target) continue;
            k++;
            if(rand()%k == 0) x = i;
        }
        
        return x;
    }
};
