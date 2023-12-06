/*
801. Minimum Swaps To Make Sequences Increasing
*/

// TC:O(n) SC:O(1) 
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int changed = 1;
        int unchanged = 0;
        for(int i = 1; i < nums2.size(); i++){
            int changed_prev = changed;
            int unchanged_prev = unchanged;
            changed = INT_MAX, unchanged = INT_MAX;

            //上次沒換這次不換
            if(nums1[i-1] < nums1[i] && nums2[i-1] < nums2[i]){
                unchanged = min(unchanged_prev, unchanged);
            }
            //上次有換這次不換
            if(nums1[i-1] < nums2[i] && nums2[i-1] < nums1[i]){
                unchanged = min(unchanged, changed_prev);
            }

            //這次換上次沒換
            if(nums1[i-1] < nums2[i] && nums2[i-1] < nums1[i]){
                changed = min(unchanged_prev+1, changed);
            }
            //上次有換這次也換
            if(nums1[i-1] < nums1[i] && nums2[i-1] < nums2[i]){
                changed = min(changed, changed_prev+1);
            }
        }

        return min(changed, unchanged);
    }
};

/*
此題說nums1 nums2 idx相同的點可以互相交換數字
問最少需交換幾次可以讓兩個數組都是嚴格單調遞增的
每次的狀態取決於上次有無交換 每次的狀態可以是要交換也可以是不交換
*/
