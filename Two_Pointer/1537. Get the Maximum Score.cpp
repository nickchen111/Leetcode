/*
1537. Get the Maximum Score
*/

// TC:O(m+n) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        LL sum1 = 0, sum2 = 0;
        int i = 0; int j = 0;
        while( i < nums1.size() && j < nums2.size()){
            if(nums1[i] < nums2[j]){
                sum1= sum1+nums1[i];
                i++;
            }
            else if(nums1[i] > nums2[j]){
                sum2= sum2+nums2[j];
                j++;
            }
            else if(nums1[i] == nums2[j]){
                sum1 = max(sum1,sum2)+nums1[i];
                sum2 = sum1;
                i++; j++;
            }
        }
        while(i < nums1.size()){
            sum1= sum1+nums1[i];
            i++;
        }
        while(j < nums2.size()){
            sum2= sum2+nums2[j];
            j++;
        }

        return (max(sum1,sum2))%M;
        
    }
};
