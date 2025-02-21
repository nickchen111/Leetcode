// SLinding Window TC:O(n) SC:O(1)
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size(), ans = 0, cnt = 0, i = 0;
        for(int j = 0; j < n; j++) {
            cnt += (nums[j] == 0);
            while(cnt == 2) {
                cnt -= (nums[i] == 0);
                i += 1;
            }
            ans = max(ans, j - i + 1 - cnt);
        }
        return min(n-1, ans);
    }
};

// DP TC:O(n) SC:O(n)
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> suffix(n);
        int cnt = 0;
        for(int i = n -1; i >= 0; i--) {
            suffix[i] = cnt;
            if(nums[i]) cnt += 1;
            else cnt = 0;
        }
        cnt = 0;
        for(int i = 0; i < n; i++) {
            ans = max(ans, cnt + suffix[i]);
            if(nums[i]) cnt += 1;
            else cnt = 0;
        }
        return ans;
    }
};
