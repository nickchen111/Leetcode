/*
1855. Maximum Distance Between a Pair of Values
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        //two pointer + greedy
        int res = 0;
        int i = nums1.size()-1;
        int j = nums2.size()-1;
        while(i >= 0 && j >= 0){
            if(nums2[j] >= nums1[i]){
                res = max(res, j-i);
                i--;
            }
            else {
                j--;
            }
        }

        return res;
    }
};

/*
此題限制
i <= j and nums1[i] <= nums2[j]
j - i的最大值為？
如果沒有return 0
*/
