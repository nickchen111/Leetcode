/*
1775. Equal Sum Arrays With Minimum Number of Operations
*/


// TC:O(n+m) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(),nums1.end(),0);
        int sum2 = accumulate(nums2.begin(),nums2.end(),0);
        if(sum1 < sum2) return minOperations(nums2,nums1);

        //nums1較大
        int i = nums1.size()-1; int j = 0;
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int diff = sum1-sum2;
        int count = 0;
        while(diff > 0){
            if(i < 0 && j == nums2.size()) return -1;
            else if(i < 0){
                diff-=(6-nums2[j]);
                j++;
            }
            else if (j == nums2.size()){
                diff-=(nums1[i]-1);
                i--;
            }
            else if(6-nums2[j] > nums1[i]-1){
                diff-=(6-nums2[j]);
                j++;
            }
            else { 
                diff-=(nums1[i]-1);
                i--;
            }
            count++;
        }

        return count;
    }
};
/*
最大幅度變動 把6改成1
所以在此數字以內的肯定都可以handle
*/
