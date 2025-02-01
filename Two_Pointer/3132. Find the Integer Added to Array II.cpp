// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        ranges::sort(nums1);
        ranges::sort(nums2);
        int m = nums1.size(), n = nums2.size();
        for(int t = 2; t >= 0; t--) {
            int i = t, j = 0, diff = nums2[j] - nums1[i];
            while(i < m && j < n) {
                if(nums1[i] + diff == nums2[j]) {
                    i += 1;
                    j += 1;
                }
                else i += 1;
            }
            if(j == n) return diff;
        }
        return -1;
    }
};
