/*
3131. Find the Integer Added to Array I
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        
        return nums2[0] - nums1[0];
    }
};
