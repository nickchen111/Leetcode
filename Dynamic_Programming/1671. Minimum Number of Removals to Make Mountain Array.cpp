/*
1671. Minimum Number of Removals to Make Mountain Array
*/

// 2025.02.13
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> suffix(n,0);
        vector<int> arr;
        for(int i = n-1; i >= 0; i--) {
            auto iter = lower_bound(arr.begin(), arr.end(), nums[i]);
            if(iter == arr.end()) {
                arr.push_back(nums[i]);
                suffix[i] = arr.size();
            }
            else {
                *iter = nums[i];
                suffix[i] = iter - arr.begin() + 1;
            }
        }
        arr.clear();
        int ans = n;
        for(int i = 0; i < n; i++) {
            auto iter = lower_bound(arr.begin(), arr.end(), nums[i]);
            if(iter == arr.end()) {
                arr.push_back(nums[i]);
            }
            else {
                *iter = nums[i];
            }
            if(suffix[i] > 1 && arr.size() > 1) {
                ans = min(ans, n - (int)arr.size() - suffix[i] + 1);
            }
        }
        return ans;
    }
};

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        // 當下點往前往後最長遞減子序列
        vector<int> suffix(n);
        vector<int> arr;
        for(int i = n-1; i >= 0; i--){
            if(arr.empty() || arr.back() < nums[i]){
                arr.push_back(nums[i]);
                suffix[i] = (int) arr.size();
            }
            else {
                auto iter = lower_bound(arr.begin(), arr.end(), nums[i]);
                *iter = nums[i];
                suffix[i] = (int)(iter - arr.begin()) + 1;
            }
        }

        arr.clear();
        int res = n;
        arr.push_back(nums[0]);
        for(int i = 1; i < n-1; i++){
            if(arr.empty() || arr.back() < nums[i]){
                arr.push_back(nums[i]);
                if(suffix[i] > 1 && (int)arr.size() > 1)
                    res = min(res, n - (int)arr.size() - suffix[i] + 1);
            }
            else {
                auto iter = lower_bound(arr.begin(), arr.end(), nums[i]);
                *iter = nums[i];
                if((int)(iter - arr.begin()) > 1 && suffix[i] > 1) {
                    res = min(res, n - (int)(iter - arr.begin()) - suffix[i]);
                }
            }
        }

        return res;
    }
};
