/*
3350. Adjacent Increasing Subarrays Detection II
*/

// 分組循環 TC:O(n) SC:O(1)
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size(), prev = 0, i = 0, ans = 0;
        while(i < n) {
            int start = i;
            while(i + 1 < n && nums[i] < nums[i+1]) i += 1;
            ans = max(ans, max( (i - start + 1) / 2, min(prev, i - start + 1)));
            prev = i - start + 1;
            i += 1;
        }
        return ans;
    }
};

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        // 每個位置的最長遞增數組
        vector<int> right(n,1);
        int prev = nums.back();
        int count = 1;
        for(int i = n-1; i >= 0; i--) {
            if(prev > nums[i]) {
                count += 1;
            }
            else {
                count = 1;
            }
            prev = nums[i];
            right[i] = count;
        }
        count = 0;
        int res = 0;
        prev = INT_MIN;
        for(int i = 0; i < n-1; i++) {
            if(prev < nums[i]) {
                count += 1;
            }
            else count = 1;
            prev = nums[i];
            res = max(res, min(count, right[i+1]));
        }
        
        return res;
    }
};
