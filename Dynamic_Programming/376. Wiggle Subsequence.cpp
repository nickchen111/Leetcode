/*
376. Wiggle Subsequence
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        //now 狀態取決於上個狀態
        int n = nums.size();
        if(n == 0) return 0;
     

        int p = 1; int q = 1;
        for(int i = 1; i<n; i++){
            //往上趨勢 q的元素肯定比較小
            if(nums[i] > nums[i-1]){
                q = p + 1;
            }
            else if(nums[i] < nums[i-1]){
                p = q + 1;
            }
        }

        return max(p,q);
    }
};
