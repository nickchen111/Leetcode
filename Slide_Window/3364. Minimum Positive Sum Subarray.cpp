/*
3364. Minimum Positive Sum Subarray
*/

// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int res = INT_MAX;
        for(int len = l; len <= r; len++) {
            int i = 0;
            int sum = 0;
            for(int j = 0; j < n; j++) {
                sum += nums[j];
                if(j-i+1 == len) {
                    if(sum > 0) {
                        res = min(res, sum);
                    }
                    sum -= nums[i];
                    i++;
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
