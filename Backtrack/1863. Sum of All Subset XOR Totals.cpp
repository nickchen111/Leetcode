/*
1863. Sum of All Subset XOR Totals
*/

// TC:O(2^n) SC:O(n)
class Solution {
    int res = 0;
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
       
        Backtrack(nums, 0, 0);

        return res;
    }
    void Backtrack(vector<int>& nums, int cur, int idx){
        if(idx == nums.size()){
            res += cur;
            return;
        }
            
        Backtrack(nums, cur ^ nums[idx], idx+1);
        Backtrack(nums, cur, idx+1);
    }
};
