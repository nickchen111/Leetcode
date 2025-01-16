// TC:O(m + n) SC:O(1)
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int res = 0;
        int m = nums1.size();
        int n = nums2.size();
        if(n % 2) {
            for(auto &num : nums1) res ^= num;
        }
        if(m % 2) {
            for(auto num : nums2) res ^= num;
        }
        return res;
    }
};
