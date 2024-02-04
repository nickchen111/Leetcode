/*
3028. Ant on the Boundary
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int n = nums.size();
        //這題就是問說有多少次會加回0
        int sum = 0;
        int count = 0;
        for(int i = 0; i < n; i++){
            sum += nums[i];
            if(sum == 0) count += 1;
        }
        
        return count;
    }
};
