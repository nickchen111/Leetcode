class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();
        int suf = reduce(nums.begin(), nums.end(), 0);
        int pre = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                if(pre == suf) res += 2;
                else if(abs(pre-suf) == 1) res += 1;
            }
            pre += nums[i];
            suf -= nums[i];
        }

        return res;
    }
};