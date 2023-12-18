/*
1913. Maximum Product Difference Between Two Pairs
*/


// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxProductDifference(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        long long a = nums[n-1];
        long long b = nums[n-2];
        long long c = nums[0];
        long long d = nums[1];
        
       

        return a*b - c*d;
    }
};


/*
要從數組中選四個數字 讓 (a * b) - (c * d) maximum
a b盡量大   c d盡量小 四個數字都只能選正數
*/
