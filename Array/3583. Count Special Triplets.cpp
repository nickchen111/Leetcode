// TC:O(n) SC:O(n)
class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        int MOD = 1e9 + 7;
        int n = nums.size();
        long long ans = 0;
        unordered_map<int, int> rightCount, leftCount;
        for (int i = 2; i < n; i++) {
            rightCount[nums[i]]++;
        }
        for (int j = 1; j < n - 1; j++) {
            leftCount[nums[j - 1]] ++;
            int target = nums[j] * 2;
            if (leftCount.count(target) && rightCount.count(target)) {
                ans = (ans + (long long) leftCount[target] * rightCount[target]) % MOD;
            }

            if (j + 1 < n) {
                rightCount[nums[j + 1]] --;
                if (rightCount[nums[j + 1]] == 0) {
                    rightCount.erase(nums[j + 1]);
                }
            }
        }
        return ans;
    }
};
