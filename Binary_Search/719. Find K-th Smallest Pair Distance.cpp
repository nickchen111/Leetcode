/*
719. Find K-th Smallest Pair Distance
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int left = 0;  // 最小可能的距離
        int right = nums[n-1] - nums[0];  // 最大可能的距離

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (countPairs(nums, mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

    int countPairs(const vector<int>& nums, int distance) {
        int count = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > distance) {
                left++;
            }
            count += right - left;
        }
        return count;
    }
};
