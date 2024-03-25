/*
442. Find All Duplicates in an Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> res;
        nums.insert(nums.begin(),-1);

        for(int i = 1; i <= n; i++){
            while(nums[i] != nums[nums[i]] && nums[i] != i){
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i <= n; i++){
            if(i != nums[i]) res.push_back(nums[i]);
        }

        return res;
    }
};
