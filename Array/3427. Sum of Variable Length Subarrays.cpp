// TC:O(n) SC:O(n)
class Solution {
public:
    int subarraySum(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        vector<int> presum(n+1);
        for(int i = 0; i < n; i++) {
            presum[i+1] = presum[i] + nums[i];
        }
        for(int i = 0; i < n; i++) {
            int start = max(0, i - nums[i]);
            if(start <= i) sum += presum[i+1] - presum[start];
        }
        
        return sum;
    }
};
