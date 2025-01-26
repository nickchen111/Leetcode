// TC:O(n) SC:O(1)
class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int n = nums.size();
        int total = reduce(nums.begin(), nums.end(), 0);
        return total % 2 ? 0 : n-1;
    }
};

class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int n = nums.size();
        int suffix = reduce(nums.begin(), nums.end(), 0);
        int prefix = 0, ans = 0;
        for(int i = 0; i < n-1; i++) {
            prefix += nums[i];
            suffix -= nums[i];
            if((suffix - prefix) % 2 == 0) ans += 1;
        }
        return ans;
    }
};
