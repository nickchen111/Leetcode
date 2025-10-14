class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 2) return true;
        vector<int> suf(n, 1);
        int cnt = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) cnt += 1;
            else cnt = 1;
            suf[i] = cnt;
        }

        cnt = 1;
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] > nums[i - 1]) cnt += 1;
            else cnt = 1;
            if (cnt >= k && suf[i + 1] >= k) return true;
        }
        return false;
    }
};