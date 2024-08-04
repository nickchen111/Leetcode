/*
1508. Range Sum of Sorted Subarray Sums
*/

// TC:O(n^2) SC:O(n) 
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        vector<LL> arr;
        for(int i = 0; i < n; i++){
            LL sum = 0;
            for(int j = i; j < n; j++){
                sum += (LL)nums[j];
                arr.push_back(sum);
            }
        }

        left -= 1;
        right -= 1;
        sort(arr.begin(), arr.end());
        LL res = 0;
        for(int i = left; i <= right; i++){
            res += arr[i];
        }

        return res%M;
    }
};
