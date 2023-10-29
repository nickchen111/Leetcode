/*
2918. Minimum Equal Sum of Two Arrays After Replacing Zeros
*/


// TC:O(m+n) SC:O(m+n)
class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long num1 = 0;
        long long num2 = 0;
        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i<nums1.size(); i++){
            if(nums1[i] == 0){
                count1+=1;
                num1+=1;
            }
            num1+=nums1[i];
        }
        for(int i = 0; i<nums2.size(); i++){
            if(nums2[i] == 0){
                count2+=1;
                num2+=1;
            }
            num2+=nums2[i];
        }
        
        if(num1 == num2) return num1;
        else {
            if(num1 > num2){
                if(count2 > 0) return num1;
                else return -1;
            }
            else if(num1 < num2){
                if(count1 > 0) return num2;
                else return -1;
            }
        }
        
        return -1;
    }
};
