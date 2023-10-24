/*
53. Maximum Subarray
*/

//可用前綴和 slide window dp來解
// tc: O(2*n) sc: O(n)
class Solution {
    //前綴和
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> presum(n+1);

        //創建presum數組
        presum[0] = 0;
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+ nums[i-1];
        }

        //最大子數組就會是某段的差值的最大
        int minval =INT_MAX;
        int res = INT_MIN;
        for(int i = 0; i < n; i++){
            minval = min(minval, presum[i]);
            res = max(res, presum[i+1]- minval);
        }
        return res;
    }
};
