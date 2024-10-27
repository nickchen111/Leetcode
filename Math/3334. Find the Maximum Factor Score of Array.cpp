/*
3334. Find the Maximum Factor Score of Array
*/

// TC:O(n^2) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size();
        LL g = nums[0];
        LL l = nums[0];
        for(int i = 1; i < n; i++) {
            g = gcd(g, nums[i]);
            l = (nums[i]*l) / gcd(l,nums[i]);
        }
       
        LL res = l*g;
        for(int i = 0; i < n; i++) {
            LL g1 = -1;
            LL l1 = -1;
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                if(g1 == -1) {
                    g1 = nums[j];
                    l1 = nums[j];
                }
                else {
                    g1 = gcd(g1, nums[j]);
                    l1 = (nums[j]*l1) / gcd(l1,nums[j]);
                }
            }
            res = max(res, l1*g1);
        }
        
        return res;
    }
};
