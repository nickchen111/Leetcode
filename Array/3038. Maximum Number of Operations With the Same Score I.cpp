/*
3038. Maximum Number of Operations With the Same Score I
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        int count = 1;
        int target = nums[0] + nums[1];
        for(int i = 2; i < n; i+=2){
            if(i+1 < n && nums[i] + nums[i+1] == target){
                count += 1;
            }
            else break;
            
        }
        
        return count;
    }
};

