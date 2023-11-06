/*
88. Merge Sorted Array
*/

// TC:O(m+n) SC:O(1)
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int left = m-1;
        int right = n-1;
        int p = nums1.size()-1;
        while( left >=0 && right >= 0){
            if(nums1[left] <= nums2[right]){
                nums1[p] = nums2[right];
                right--;
            }
            else {
                nums1[p] = nums1[left];
                left--;
            }
            p--;
        }

        //考慮nums2元素還沒用完情況
        while(right >= 0){
            nums1[p] = nums2[right];
            right--;
            p--;
        }
    }
};
