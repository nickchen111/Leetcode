/*
53. Maximum Subarray
*/

// 2025.03.11 DP 優化前
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> f(nums.size());
        f[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            f[i] = max(f[i - 1], 0) + nums[i];
        }
        return ranges::max(f);
    }
};

// 優化後DP Kadane
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int f = 0;
        for (int x : nums) {
            f = max(f, 0) + x;
            ans = max(ans, f);
        }
        return ans;
    }
};

// Prefix Sum 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int min_pre_sum = 0;
        int pre_sum = 0;
        for (int x : nums) {
            pre_sum += x; 
            ans = max(ans, pre_sum - min_pre_sum);
            min_pre_sum = min(min_pre_sum, pre_sum); 
        }
        return ans;
    }
};

// Divide and Conquer 線段樹分治思想雛形
class Solution {
public:
    struct Status {
        int iSum, rSum, lSum, mSum;
    };
    Status pushUp(Status l, Status r) {
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max({l.mSum, r.mSum, l.rSum + r.lSum});
        return (Status) {iSum, rSum, lSum, mSum};
    }
    Status get(vector<int>&a, int l, int r) {
        if (l == r) return (Status) {a[l], a[l], a[l], a[l]};
        int m = (l + r) / 2;
        Status lSum = get(a, l, m);
        Status rSum = get(a, m + 1, r);
        return pushUp(lSum, rSum);
    }
    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};
