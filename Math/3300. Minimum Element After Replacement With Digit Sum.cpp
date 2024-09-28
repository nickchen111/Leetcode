/*
3300. Minimum Element After Replacement With Digit Sum
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minElement(vector<int>& nums) {
        int n = nums.size();
        int res = INT_MAX/2;
        for(int i = 0; i < n; i++){
            int sum = 0;
            int cur = nums[i];
            while(cur != 0){
                sum += cur % 10;
                cur /= 10;
            }
            res = min(res, sum);
        }
        
        return res;
    }
};
