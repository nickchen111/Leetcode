/*
775. Global and Local Inversions
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return true;
        int cur_max = nums[0];
        for(int i = 0; i < n; i++){
            if(i >= 2) cur_max = max(cur_max, nums[i-2]);
            if(i >= 2 && nums[i] < cur_max){
                return false;
            }
        }

        return true;
    }
};


/*
此題題意
global j > i && nums[j] < nums[i] ->每次都Binary Search or n-1這個肯定有什麼用意
local strictly decreasing

[4 5 2 3 1 0] 5 + 3 
[0 1 2 3 4 5 6]
*/
