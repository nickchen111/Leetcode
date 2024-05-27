/*
1608. Special Array With X Elements Greater Than or Equal X
*/


// TC:O(nlgm) SC:O(1)
class Solution {
public:
    int specialArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i <= nums.back(); i++){
            auto iter = lower_bound(nums.begin(), nums.end(), i);
            int count = nums.end() - iter;
            if(count == i) return count;
        }

        return -1;
    }
};
