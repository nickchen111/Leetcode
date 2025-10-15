class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> suf(n, 1);
        int cnt = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) cnt += 1;
            else cnt = 1;
            suf[i] = cnt;
        }

        cnt = 1;
        int ans = 1;
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] > nums[i - 1]) cnt += 1;
            else cnt = 1;
            ans = max(ans, min(cnt, suf[i + 1]));
        }
        return ans;
    }
};