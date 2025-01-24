// TC:O(n) SC:O(1)
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0, left = 0;
        int n = nums.size();
        int cnt = 0;
        int mx = *max_element(nums.begin(), nums.end());
        for(long long j = 0; j < n; j++) {
            cnt += (nums[j] == mx);
            while(cnt == k) {
                cnt -= (nums[left] == mx);
                left += 1;
            }
            ans = ans + left;
        }
        return ans;
    }
};
