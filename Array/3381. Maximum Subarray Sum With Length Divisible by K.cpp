/*
3381. Maximum Subarray Sum With Length Divisible by K
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<LL> prefix(n + 1);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        LL res = LLONG_MIN;
        for(int i = 0; i < k; i++) {
            multiset<LL> set;
            set.insert(prefix[i]);
            for(int j = i + k; j < prefix.size(); j += k) {
                res = max(res, prefix[j] - *set.begin());
                set.insert(prefix[j]);
            }
        }
        
        return res;
        
    }
};

// 可以被k整除的subarray長度的和最大多少,數字有正有負

