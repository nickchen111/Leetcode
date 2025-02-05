// TC:O(n) SC:O(1)
class Solution {
public:
    int longestMountain(vector<int>& nums) {
        int n = nums.size(), i = 0 , ans = 0, cnt = 0;
        if(n <= 2) return 0;
        while(i < n) {
            // 找左側山谷
            while(i + 1 < n && nums[i+1] <= nums[i]) i += 1;
            if(i == n - 1) return ans;
            int j = i;
            while(j + 1 < n && nums[j+1] > nums[j]) j += 1;
            if(j == n - 1) return ans;
            int k = j;
            while(k + 1 < n && nums[k] > nums[k+1]) k += 1;
            if(k > j) ans = max(ans, k - i + 1);
            i = k; 
        }
        return ans;
    }
};
