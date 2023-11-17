/*
1877. Minimize Maximum Pair Sum in Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        //將每個數字頭跟尾配對
        int res = INT_MIN;
        int i = 0; int j = nums.size()-1;
        while(i<j){
            int sum = nums[i]+nums[j];
            res = max(res,sum);
            i++;j--;
        }

        return res;
    }
};
