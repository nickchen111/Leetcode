/*
3364. Minimum Positive Sum Subarray
*/

// 最佳解 Binary Search + Presum + Slide Window TC:O(n-l * lg(r-l)) SC:O(r-l)
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int res = INT_MAX;
        multiset<int> set;
        vector<int> arr(n+1);
        for(int j = 0; j < n; j++) {
            arr[j+1] = arr[j] + nums[j];
            if(j+1 < l) continue;
            set.insert(arr[j-l+1]);
            auto iter = set.lower_bound(arr[j+1]);
            if(iter != set.begin()) {
                res = min(res, arr[j+1] - *--iter);
            }
            if(j+1 >= r) {
                set.erase(set.find(arr[j+1-r]));
            }
        }
        
        
        return res == INT_MAX ? -1 : res;
    }
};

/*
multiset 可以做O(n)
l <= j-i+1 <= r
j-r+1 <= i <= j-l+1

*/


// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int res = INT_MAX;
        for(int len = l; len <= r; len++) {
            int i = 0;
            int sum = 0;
            for(int j = 0; j < n; j++) {
                sum += nums[j];
                if(j-i+1 == len) {
                    if(sum > 0) {
                        res = min(res, sum);
                    }
                    sum -= nums[i];
                    i++;
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};
