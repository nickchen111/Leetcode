/*
2444. Count Subarrays With Fixed Bounds
*/

// 2025.02.04
class Solution {
    using LL = long long;
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int min_i = -1, max_i = -1, i0 = -1, n = nums.size();
        LL ans = 0;
        for(int i = 0; i < n; i++) {
            if(nums[i] == minK) min_i = i;
            if(nums[i] == maxK) max_i = i;
            if(nums[i] > maxK || nums[i] < minK) i0 = i;
            ans += (LL)max(0, min(min_i, max_i) - i0);
        }
        return ans;
    }
};

//TC:O(n) SC:O(1)
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();
        int premin = -1; int premax = -1; int boundary = -1;
        
        long long res = 0;
        for(int i = 0; i<n; i++){
            if(nums[i] > maxK || nums[i] < minK){
                boundary = i;
                continue;
            }

            if(nums[i] == minK) premin = i;
            if(nums[i] == maxK) premax = i;

            res+= max(0,min(premin,premax)-boundary);
        }

        return res;
    }
};
